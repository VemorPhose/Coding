# receiver.py
import socket
import pickle
import hashlib

# --- Configuration ---
HOST = 'localhost'
PORT = 8080
OUTPUT_FILENAME = 'destination.txt'
SOURCE_FILENAME = 'source.txt' # For final comparison

def compare_files(file1, file2):
    """Compares two files and returns True if identical, False otherwise."""
    try:
        with open(file1, 'rb') as f1, open(file2, 'rb') as f2:
            return hashlib.md5(f1.read()).hexdigest() == hashlib.md5(f2.read()).hexdigest()
    except FileNotFoundError:
        print(f"Error: One of the files for comparison not found.")
        return False

def main():
    print("--- Receiver (Client) ---")
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        client_socket.connect((HOST, PORT))
        print(f"Connected to sender at {HOST}:{PORT}")
    except ConnectionRefusedError:
        print("Connection refused. Is the sender running?")
        return
    
    # --- User Input for Simulation Scenario ---
    lost_ack_num = -1 # Default to no lost ACKs
    mode = input("Choose scenario:\n1. Normal operation\n2. Simulate Lost ACK\nEnter choice (1 or 2): ")
    if mode == '2':
        try:
            lost_ack_num = int(input("Enter the sequence number of the ACK to 'lose': "))
        except ValueError:
            print("Invalid number. Proceeding with normal operation.")

    expected_seq_num = 0
    
    with open(OUTPUT_FILENAME, 'wb') as f:
        while True:
            try:
                frame_data = client_socket.recv(4096)
                if not frame_data:
                    break
                
                frame = pickle.loads(frame_data)
                
                # Check for the end signal
                if frame.get('seq') == -1:
                    print("End signal received. Transfer complete.")
                    break
                
                seq_num = frame.get('seq')
                data = frame.get('data')

                print(f"Received FRAME {seq_num}.")
                
                # If this is the frame we were expecting
                if seq_num == expected_seq_num:
                    # Write data to the file
                    f.write(data)
                    print(f"  -> Wrote data from FRAME {seq_num} to file.")
                    
                    # --- Lost ACK Simulation Logic ---
                    if seq_num == lost_ack_num:
                        print(f"  -> SIMULATING LOST ACK for FRAME {seq_num}. Not sending ACK.")
                        lost_ack_num = -1 # Only lose it once
                    else:
                        ack_frame = {'ack': seq_num}
                        client_socket.sendall(pickle.dumps(ack_frame))
                        print(f"  -> Sent ACK {seq_num}.")
                    
                    # Move to the next expected frame
                    expected_seq_num += 1
                
                # If this is a duplicate frame (because our previous ACK was lost)
                elif seq_num < expected_seq_num:
                    print(f"  -> Received DUPLICATE FRAME {seq_num}. Discarding data.")
                    # Re-send the ACK for this duplicate frame
                    ack_frame = {'ack': seq_num}
                    client_socket.sendall(pickle.dumps(ack_frame))
                    print(f"  -> Re-sent ACK {seq_num}.")
                    
            except (pickle.UnpicklingError, EOFError):
                print("Error receiving data or connection closed.")
                break
            except (ConnectionResetError, BrokenPipeError):
                print("Sender has disconnected.")
                break

    print("Closing connection.")
    client_socket.close()

    # --- Final Verification ---
    print("\n--- Verification ---")
    if compare_files(SOURCE_FILENAME, OUTPUT_FILENAME):
        print("SUCCESS: The sent and received files are identical.")
    else:
        print("FAILURE: The files are different.")

if __name__ == "__main__":
    main()