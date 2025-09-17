import sys

def physical_layer(message, size):
    print(f"  (Physical Layer received size: {size})")
    print(f"  (Physical Layer does not add a header, only transmits the message)")
    new_message = message
    print(f"Layer 1 (Physical)    : {new_message}")
    print("\n--- Message sent over the physical medium ---")

def data_link_layer(message, size):
    print(f"  (Data Link Layer received size: {size})")
    header = "DL_Hdr|"
    if len(header) > 64: sys.exit(f"Error: Layer 2 header exceeds 64 characters.")
    new_message = header + message
    print(f"Layer 2 (Data Link)   : {new_message}")
    physical_layer(new_message, len(new_message))

def network_layer(message, size):
    print(f"  (Network Layer received size: {size})")
    header = "Ntwrk_Hdr|"
    if len(header) > 64: sys.exit(f"Error: Layer 3 header exceeds 64 characters.")
    new_message = header + message
    print(f"Layer 3 (Network)     : {new_message}")
    data_link_layer(new_message, len(new_message))

def transport_layer(message, size):
    print(f"  (Transport Layer received size: {size})")
    header = "Trans_Hdr|"
    if len(header) > 64: sys.exit(f"Error: Layer 4 header exceeds 64 characters.")
    new_message = header + message
    print(f"Layer 4 (Transport)   : {new_message}")
    network_layer(new_message, len(new_message))

def session_layer(message, size):
    print(f"  (Session Layer received size: {size})")
    header = "Sess_Hdr|"
    if len(header) > 64: sys.exit(f"Error: Layer 5 header exceeds 64 characters.")
    new_message = header + message
    print(f"Layer 5 (Session)     : {new_message}")
    transport_layer(new_message, len(new_message))

def presentation_layer(message, size):
    print(f"  (Presentation Layer received size: {size})")
    header = "Pres_Hdr|"
    if len(header) > 64: sys.exit(f"Error: Layer 6 header exceeds 64 characters.")
    new_message = header + message
    print(f"Layer 6 (Presentation): {new_message}")
    session_layer(new_message, len(new_message))

def application_layer(message, size):
    header = "Appl_Hdr|"
    if len(header) > 64: sys.exit(f"Error: Layer 7 header exceeds 64 characters.")
    new_message = header + message
    print(f"Layer 7 (Application) : {new_message}")
    presentation_layer(new_message, len(new_message))

def main():
    app_message = input("Enter the application message: ")
    
    print("\n--- Sending process starting (Top-Down) ---")
    print(f"Original Message: '{app_message}' (Size: {len(app_message)})\n")
    
    application_layer(app_message, len(app_message))

if __name__ == "__main__":
    main()