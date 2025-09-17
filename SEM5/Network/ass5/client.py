import socket
import sys
import threading

def receive_messages(client_socket, my_address):
    """
    Thread function to continuously listen for messages from the hub.
    """
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                print("\n[INFO] Disconnected from hub.")
                break

            try:
                dest_address, content = message.split(':', 1)
                
                # Check if the message is for this node
                if dest_address == my_address:
                    print(f"\n[ACCEPTED] Received message: '{content}'")
                else:
                    print(f"\n[DISCARDED] Received message for '{dest_address}', not for me.")
            
            except ValueError:
                print(f"\n[WARNING] Received malformed message: {message}")

        except Exception as e:
            print(f"\n[ERROR] An error occurred while receiving: {e}")
            break
    client_socket.close()


def main():
    """
    Main function to start the node client.
    """
    if len(sys.argv) != 2:
        print("Usage: python client.py <node_address>")
        print("Example: python client.py node1")
        sys.exit(1)

    my_address = sys.argv[1]
    server_ip = 'localhost'
    port = 12345
    
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        client_socket.connect((server_ip, port))
        print(f"Node '{my_address}' connected to the hub at {server_ip}:{port}.")
        
        # Start a thread to listen for incoming messages
        receiver_thread = threading.Thread(target=receive_messages, args=(client_socket, my_address))
        receiver_thread.daemon = True
        receiver_thread.start()

        print("You can now send messages. Format: <destination_address>:<message>")
        print("Example: node2:Hello there!")
        
        # Main thread handles sending messages
        while True:
            msg_to_send = input()
            if msg_to_send.lower() == 'exit':
                break
            client_socket.sendall(msg_to_send.encode('utf-8'))
            
    except KeyboardInterrupt:
        print(f"\n[SHUTTING DOWN] Node '{my_address}' is shutting down.")
    except ConnectionRefusedError:
        print(f"Connection refused. Is the hub server running at {server_ip}:{port}?")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()

if __name__ == "__main__":
    main()