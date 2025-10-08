import socket
import pickle

# --- Configuration ---
HOST = '127.0.0.1'
PORT = 8080
PACKET_SIZE = 50 
TIMEOUT_SEC = 3
INPUT_FILE = 'input.txt'

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print(f"Sender listening on {HOST}:{PORT}")
        conn, addr = s.accept()
        conn.settimeout(TIMEOUT_SEC) 

        with conn:
            print(f"Receiver connected from {addr}")
            
            with open(INPUT_FILE, 'rb') as f:
                seq_to_send = 0
                while True:
                    data_chunk = f.read(PACKET_SIZE)
                    if not data_chunk:
                        # Signal End-of-File to the receiver
                        frame = {'type': 'eof'}
                        conn.sendall(pickle.dumps(frame))
                        print("Sender: EOF frame sent.")
                        break

                    frame = {'seq': seq_to_send, 'data': data_chunk}
                    
                    while True:
                        try:
                            conn.sendall(pickle.dumps(frame))
                            print(f"Sender: Sent Frame {seq_to_send}...", end="", flush=True)
                            
                            # Wait for the corresponding ACK
                            ack_data = conn.recv(1024)
                            ack_frame = pickle.loads(ack_data)
                            
                            if ack_frame.get('ack') == (1 - seq_to_send):
                                print(f" Received ACK {ack_frame.get('ack')}.")
                                break 
                            else:
                                print(f" Received wrong ACK {ack_frame.get('ack')}. Ignoring.")

                        except socket.timeout:
                            print(f"\nSender: TIMEOUT. Resending Frame {seq_to_send}.")
            
                    # Toggle sequence number 
                    seq_to_send = 1 - seq_to_send
                    
    print("Sender: Connection closed.")

if __name__ == "__main__":
    main()