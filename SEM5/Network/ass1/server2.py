import socket
import sys
import os
import signal

def handle_client(client_socket, client_address):
    """
    Handles the client connection in a separate process.
    """
    print(f"Process {os.getpid()}: Connected with client socket number {client_socket.fileno()}")
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                break  # Client disconnected
            print(f"Received from {client_address}: {message}")
            client_socket.sendall(message.encode('utf-8'))  # Echo back the message
        except Exception as e:
            print(f"Error handling client {client_address}: {e}")
            break
    client_socket.close()
    print(f"Connection from {client_address} has been closed.")

def signal_handler(signum, frame):
    """
    Handles termination signals to clean up child processes.
    """
    print(f"Received signal {signum}. Cleaning up child processes.")
    while True:
        try:
            pid, _ = os.waitpid(-1, os.WNOHANG)
            if pid == 0:
                break  # No more child processes
        except ChildProcessError:
            break  # No child processes

def main():
    """
    Multiple client supporting server implementation.
    """
    port = 12345  # Default port
    try:
        if len(sys.argv) > 1:
            port = int(sys.argv[1])
    except ValueError:
        print("Invalid port number. Using default port 12345.")

    # Handle SIGCHLD to clean up zombie processes
    signal.signal(signal.SIGCHLD, signal_handler)
    # Create a TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Allow the socket to be reused
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        server_socket.bind(('localhost', port))
        server_socket.listen(5)  # Listen for upto 5 incoming connections
        print(f"Server listening on port {port}...")

        while True:
            client_socket, client_address = server_socket.accept()
            print(f"Accepted connection from {client_address}")
            pid = os.fork()
            if pid == 0:  # Child process
                server_socket.close()  # Close the server socket in the child
                handle_client(client_socket, client_address)
                sys.exit(0)
            else:  # Parent process
                client_socket.close()  # Close the client socket in the parent
    
    except KeyboardInterrupt:
        print("Server shutting down.")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()