# sender.py
import socket
import time
import pickle

# --- Configuration ---
HOST = 'localhost'
PORT = 8080
FILENAME = 'source.txt'
CHUNK_SIZE = 100  # Size of data in each frame (in bytes)
TIMEOUT = 3       # Seconds to wait for an ACK before re-transmitting

def main():
    print("--- Sender (Server) ---")

    # Create a TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(1)
    print(f"Sender listening on {HOST}:{PORT}")

    conn, addr = server_socket.accept()
    print(f"Receiver connected from {addr}")

    # Read the file and split it into chunks (frames)
    try:
        with open(FILENAME, 'rb') as f:
            data = f.read()
        chunks = [data[i:i + CHUNK_SIZE] for i in range(0, len(data), CHUNK_SIZE)]
        print(f"File '{FILENAME}' split into {len(chunks)} chunks.")
    except FileNotFoundError:
        print(f"Error: {FILENAME} not found.")
        conn.close()
        server_socket.close()
        return

    seq_num = 0
    # Loop through all the chunks of the file
    while seq_num < len(chunks):
        # Frame format: {'seq': sequence_number, 'data': data_chunk}
        frame = {'seq': seq_num, 'data': chunks[seq_num]}
        
        retransmitting = False
        while True: # Loop for handling re-transmission
            try:
                if retransmitting:
                    print(f"Re-sending FRAME {seq_num}...")
                else:
                    print(f"Sending FRAME {seq_num}...")
                
                # Serialize and send the frame
                conn.sendall(pickle.dumps(frame))
                
                # --- Start Timer ---
                # Set a timeout for the blocking recv() call
                conn.settimeout(TIMEOUT)

                # --- Wait for ACK ---
                ack_data = conn.recv(1024)
                if not ack_data:
                    # Connection might be lost
                    print("Receiver disconnected.")
                    return
                
                ack_frame = pickle.loads(ack_data)
                
                # Check if the ACK is for the frame we just sent
                if ack_frame.get('ack') == seq_num:
                    print(f"Received ACK {seq_num}. Moving to next frame.")
                    conn.settimeout(None) # Disable timeout
                    break # Exit the re-transmission loop
                else:
                    print(f"Received wrong ACK {ack_frame.get('ack')}. Expected {seq_num}. Ignoring.")
                    # Let the timeout handle re-transmission

            except socket.timeout:
                print(f"TIMEOUT occurred. No ACK received for FRAME {seq_num}.")
                retransmitting = True
                # The loop will continue, causing a re-transmission
            except (ConnectionResetError, BrokenPipeError):
                print("Receiver has disconnected.")
                seq_num = len(chunks) # End the outer loop
                break
            except Exception as e:
                print(f"An error occurred: {e}")
                break
    
    # Send a special "end" frame to signal completion
    print("All chunks sent. Sending end signal.")
    end_frame = {'seq': -1, 'data': b''}
    conn.sendall(pickle.dumps(end_frame))

    print("Closing connection.")
    conn.close()
    server_socket.close()

if __name__ == "__main__":
    main()