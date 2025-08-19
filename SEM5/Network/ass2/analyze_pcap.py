from scapy.all import rdpcap, IP, IPv6, TCP, UDP, ICMP, ICMPv6Unknown, DNS

# Load packets
packets = rdpcap("ass2.pcap")

# Stats
total_packets = len(packets)
ipv4_packets = 0
ipv6_packets = 0
unique_ips = set()
dst_ports = set()
total_bytes = 0
ping_count = dns_count = ssh_count = curl_count = 0
example_headers = {"ping": [], "dns": [], "ssh": [], "curl": []}

# Header extractor
def headers(pkt):
    layers = []
    current = pkt
    while current:
        layers.append(current.__class__.__name__)
        current = current.payload
        if current is None or current.__class__.__name__ == "NoPayload":
            break
    return " | ".join(layers)

for pkt in packets:
    total_bytes += len(pkt)

    if pkt.haslayer(IP):
        ipv4_packets += 1
        unique_ips.update([pkt[IP].src, pkt[IP].dst])
    elif pkt.haslayer(IPv6):
        ipv6_packets += 1
        unique_ips.update([pkt[IPv6].src, pkt[IPv6].dst])

    if pkt.haslayer(TCP):
        dst_ports.add(pkt[TCP].dport)
    if pkt.haslayer(UDP):
        dst_ports.add(pkt[UDP].dport)

    if pkt.haslayer(ICMP) or pkt.haslayer(ICMPv6Unknown):
        ping_count += 1
        if len(example_headers["ping"]) < 3:
            example_headers["ping"].append(headers(pkt))

    if pkt.haslayer(DNS) or (pkt.haslayer(UDP) and 53 in [pkt[UDP].sport, pkt[UDP].dport]):
        dns_count += 1
        if len(example_headers["dns"]) < 3:
            example_headers["dns"].append(headers(pkt))

    if pkt.haslayer(TCP) and 22 in [pkt[TCP].sport, pkt[TCP].dport]:
        ssh_count += 1
        if len(example_headers["ssh"]) < 3:
            example_headers["ssh"].append(headers(pkt))

    if pkt.haslayer(TCP) and any(p in [80, 443] for p in [pkt[TCP].sport, pkt[TCP].dport]):
        curl_count += 1
        if len(example_headers["curl"]) < 3:
            example_headers["curl"].append(headers(pkt))

# Output
print("\n===== Analysis Results =====")
print(f"1. Total packets observed: {total_packets}")
print(f"2. Ping packets: {ping_count} | Headers: {example_headers['ping']}")
print(f"3. DNS packets: {dns_count} | Headers: {example_headers['dns']}")
print(f"4. SSH packets: {ssh_count} | Headers: {example_headers['ssh']}")
print(f"5. Curl/HTTP(S) packets: {curl_count} | Headers: {example_headers['curl']}")
print(f"6. Unique IP addresses: {len(unique_ips)}")
print(f"7. Total bytes observed: {total_bytes}")
print(f"8. IPv4 vs IPv6 packets: {ipv4_packets} / {ipv6_packets}")
print(f"9. Unique destination ports: {sorted(dst_ports)}")
