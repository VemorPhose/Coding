import socket
import sys

def main():
    """
    A simple TCP client that connects to a specified server and port,
    sends a message, and prints the server's response.
    """

    server_ip = 'localhost'  # Default server IP
    port = 12345  # Default server port

    if len(sys.argv) > 2:
        try:
            server_ip = sys.argv[1]
            port = int(sys.argv[2])
        except ValueError:
            print("Invalid port number. Using default port 12345.")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        client_socket.connect((server_ip, port))
        print(f"Connected to server at {server_ip}:{port}...")

        while True:
            msg = input("Enter a message: ")

            client_socket.sendall(msg.encode('utf-8'))
            print(f"Sent msg: {msg}")

            response = client_socket.recv(1024).decode('utf-8')
            print(f"Received reply: {response}")

    except KeyboardInterrupt:
        print("\nClient shutting down.")
    except ConnectionRefusedError:
        print(f"Could not connect to server at {server_ip}:{port}. Is the server running?")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()
        print("Client socket closed.")

if __name__ == "__main__":
    main()
