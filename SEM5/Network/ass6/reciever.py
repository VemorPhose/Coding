import socket
import pickle
import filecmp

# --- Configuration ---
HOST = '127.0.0.1'
PORT = 8080
OUTPUT_FILE = 'output.txt'
FRAMES_TO_DROP_ACK_FOR = [1, 0]

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print(f"Receiver connected to {HOST}:{PORT}")
        
        expected_seq = 0
        
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

                        if recv_seq in FRAMES_TO_DROP_ACK_FOR:
                            print(f"Receiver: (Simulating lost ACK for Frame {recv_seq})")
                            FRAMES_TO_DROP_ACK_FOR.remove(recv_seq) # Remove only the first matching occurrence
                            continue

                        # Send the ACK
                        ack_frame = {'ack': ack_to_send}
                        s.sendall(pickle.dumps(ack_frame))
                        print(f"Receiver: Sent ACK {ack_to_send}.")

                    else:
                        # Logic for duplicates
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