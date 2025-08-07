import socket
import sys

def main():
    """
    A simple TCP server that listens for incoming connections on a specified port.
    """

    port = 12345  # Default port number
    if len(sys.argv) > 1:
        try:
            port = int(sys.argv[1])
        except ValueError:
            print("Invalid port number. Using default port 12345.")
    # TCP server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Set socket options to reuse the address to avoid TIME_WAIT, CLOSE_WAIT
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        server_socket.bind(('localhost', port))

        server_socket.listen(1)
        print(f"Server listening on port {port}...")
        
        while True:
            client_socket, addr = server_socket.accept()
            print(f"Connection from {addr} has been established.")

            try:
                while True:
                    msg = client_socket.recv(1024).decode('utf-8')
                    if not msg:
                        print("Client disconnected.")
                        break
                    print(f"Received msg: {msg}")

                    reversed_msg = msg[::-1]
                    print(f"Sending reply: {reversed_msg}")

                    client_socket.sendall(reversed_msg.encode('utf-8'))
            except ConnectionResetError as e:
                print(f"Client disconnected unexpectedly: {e}")
            finally:
                client_socket.close()

    except socket.error as e:
        print(f"Error binding socket: {e}")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nServer shutting down.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
    finally:
        server_socket.close()
        print("Server socket closed.")

if __name__ == "__main__":
    main()
