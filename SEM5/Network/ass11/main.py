import sys

class TrieNode:
    def __init__(self):
        self.children = [None, None]
        self.interface = None

class PrefixTrie:
    def __init__(self):
        self.root = TrieNode()

    def _ip_to_binary(self, ip_str):
        octets = ip_str.split('.')
        binary_str = ""
        for octet in octets:
            binary_str += bin(int(octet))[2:].zfill(8)
        return binary_str

    def insert(self, prefix_str, interface):
        try:
            ip, mask_len_str = prefix_str.split('/')
            mask_len = int(mask_len_str)
        except ValueError:
            print(f"Error: Invalid prefix format '{prefix_str}'. Skipping.")
            return

        binary_ip = self._ip_to_binary(ip)
        node = self.root
        
        for i in range(mask_len):
            bit = int(binary_ip[i])
            if node.children[bit] is None:
                node.children[bit] = TrieNode()
            node = node.children[bit]
        
        node.interface = interface
        print(f"Inserted route: {prefix_str} -> {interface}")

    def lookup_lpm(self, dest_ip_str):
        binary_ip = self._ip_to_binary(dest_ip_str)
        node = self.root
    
        longest_match_interface = node.interface 
        
        for bit in binary_ip:
            bit = int(bit)
            if node.children[bit] is not None:
                node = node.children[bit]
        
                if node.interface is not None:
                    longest_match_interface = node.interface
            else:
                break
                
        return longest_match_interface

if __name__ == "__main__":
    router_table = PrefixTrie()
    
    router_table.insert("0.0.0.0/0", "Internet (Default)")
    
    router_table.insert("128.208.0.0/18", "EE")
    router_table.insert("128.208.128.0/17", "CS")
    router_table.insert("128.208.96.0/19", "Art")
    
    router_table.insert("128.208.0.0/16", "Internet (Campus Block)")

    print("\n--- Testing Destination IPs ---")
    
    test_ips = [
        "128.208.22.45",   
        "128.208.150.9",   
        "128.208.97.200",  
        "128.208.200.10",  
        "128.208.120.1",   
        "10.0.14.22",       
    ]
    
    for ip in test_ips:
        interface = router_table.lookup_lpm(ip)
        print(f"Destination: {ip:<16} -> Outgoing Interface: {interface}")