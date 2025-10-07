import socket
import pickle
import filecmp

# --- Configuration ---
HOST = '127.0.0.1'
PORT = 8080
OUTPUT_FILE = 'output.txt'
# CHANGED: Use a list to specify which ACKs to drop.
# This list will drop the first Frame 1 it sees, and the second Frame 0.
FRAMES_TO_DROP_ACK_FOR = [1, 0]

def main():
    # Create a default input file for verification if it doesn't exist
    if not filecmp.os.path.exists('input.txt'):
        with open('input.txt', 'w') as f:
            f.write("This is a test of the Stop-and-Wait ARQ protocol.\n")
            f.write("It uses alternating 0/1 sequence numbers to ensure\n")
            f.write("that data is transferred reliably even if packets\n")
            f.write("or their acknowledgements are lost in transit.\n")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print(f"Receiver connected to {HOST}:{PORT}")
        
        expected_seq = 0
        
        # Clear the output file before starting
        with open(OUTPUT_FILE, 'wb') as f:
            pass 

        with open(OUTPUT_FILE, 'ab') as f:
            while True:
                try:
                    data = s.recv(4096)
                    if not data: break
                    
                    recv_frame = pickle.loads(data)
                    
                    if recv_frame.get('type') == 'eof':
                        print("Receiver: Received EOF. Closing.")
                        break
                        
                    recv_seq = recv_frame['seq']
                    
                    # Check if the received frame is the one we are expecting
                    if recv_seq == expected_seq:
                        print(f"Receiver: Received expected Frame {recv_seq}.")
                        f.write(recv_frame['data'])
                        
                        ack_to_send = 1 - expected_seq
                        expected_seq = 1 - expected_seq

                        # CHANGED: Logic to handle a list of frames to drop
                        if recv_seq in FRAMES_TO_DROP_ACK_FOR:
                            print(f"Receiver: (Simulating lost ACK for Frame {recv_seq})")
                            FRAMES_TO_DROP_ACK_FOR.remove(recv_seq) # Drop only the first matching occurrence
                            continue

                        # Send the ACK
                        ack_frame = {'ack': ack_to_send}
                        s.sendall(pickle.dumps(ack_frame))
                        print(f"Receiver: Sent ACK {ack_to_send}.")

                    else:
                        # The logic for duplicates remains the same
                        ack_to_send = expected_seq
                        print(f"Receiver: Received duplicate Frame {recv_seq}. Discarding. Resending ACK {ack_to_send}.")
                        ack_frame = {'ack': ack_to_send}
                        s.sendall(pickle.dumps(ack_frame))

                except (ConnectionError, EOFError, pickle.UnpicklingError):
                    break
    
    print("\n--- Verification ---")
    if filecmp.cmp('input.txt', OUTPUT_FILE, shallow=False):
        print("File transfer successful: output.txt is identical to input.txt.")
    else:
        print("File transfer failed: files differ.")

if __name__ == "__main__":
    main()