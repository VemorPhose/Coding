import socket
import threading

clients = []
clients_lock = threading.Lock()

def broadcast(message, sender_socket):
    """
    Sends a message to all clients except the sender.
    """
    with clients_lock:
        for client_socket in clients:
            # Don't send the message back to the sender
            if client_socket != sender_socket:
                try:
                    client_socket.sendall(message)
                except Exception as e:
                    print(f"Error broadcasting to a client: {e}")
                    # The client might have disconnected, remove it
                    clients.remove(client_socket)

def handle_client(client_socket, client_address):
    """
    Handles a single client connection.
    Receives a message and triggers a broadcast.
    """
    print(f"[NEW CONNECTION] {client_address} connected.")

    # Add the new client to list of clients
    with clients_lock:
        clients.append(client_socket)

    try:
        while True:
            # Receive message from the client
            message = client_socket.recv(1024)
            if not message:
                # Empty message means client disconnected
                break
            
            print(f"[RECEIVED from {client_address}] {message.decode('utf-8')}")
            # Broadcast the received message to other clients
            broadcast(message, client_socket)
            
    except Exception as e:
        print(f"[ERROR] Error with client {client_address}: {e}")
    finally:
        # Clean up when the client disconnects
        print(f"[DISCONNECTED] {client_address} disconnected.")
        with clients_lock:
            clients.remove(client_socket)
        client_socket.close()

def main():
    """
    Main function to start the hub server.
    """
    host = 'localhost'
    port = 12345
    
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        server_socket.bind((host, port))
        server_socket.listen(5)
        print(f"[LISTENING] Hub is listening on {host}:{port}")

        while True:
            client_socket, client_address = server_socket.accept()
            # Start a new thread to handle the client
            thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
            thread.daemon = True # Allows main thread to exit even if client threads are running
            thread.start()
            
    except KeyboardInterrupt:
        print("\n[SHUTTING DOWN] Hub is shutting down.")
    except Exception as e:
        print(f"[ERROR] {e}")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()