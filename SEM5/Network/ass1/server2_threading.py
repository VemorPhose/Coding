import socket
import sys
import multiprocessing

def handle_client(client_socket, client_address):
    """
    Handles the client connection in a separate process.
    """
    print(f"Process {multiprocessing.current_process().name}: Connected with client socket number {client_socket.fileno()}")
    
    try:
        while True:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                print(f"Process {multiprocessing.current_process().name}: Client {client_address} disconnected")
                break
            
            print(f"Process {multiprocessing.current_process().name}: Client socket {client_socket.fileno()} sent message: {message}")
            
            # Reverse the message
            reversed_message = message[::-1]
            print(f"Process {multiprocessing.current_process().name}: Sending reply: {reversed_message}")
            
            client_socket.send(reversed_message.encode('utf-8'))
            
    except Exception as e:
        print(f"Process {multiprocessing.current_process().name}: Error handling client {client_address}: {e}")
    finally:
        client_socket.close()

def main():
    if len(sys.argv) != 2:
        print("Usage: python server2_multiprocess.py <port>")
        sys.exit(1)
    
    try:
        port = int(sys.argv[1])
    except ValueError:
        print("Error: Port must be a number")
        sys.exit(1)

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        server_socket.bind(('', port))
        server_socket.listen(5)
        print(f"Server2 (multi-process) listening on port {port}...")

        while True:
            client_socket, client_address = server_socket.accept()
            print(f"Accepted connection from {client_address}")
            
            # Create a new process to handle the client
            process = multiprocessing.Process(
                target=handle_client,
                args=(client_socket, client_address),
                name=f"Client-{client_address[0]}:{client_address[1]}"
            )
            process.start()
            client_socket.close()  # Close socket in parent process
            
    except KeyboardInterrupt:
        print("\nServer shutting down...")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()