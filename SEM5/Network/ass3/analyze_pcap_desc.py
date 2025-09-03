from scapy.all import rdpcap, IP, TCP, Ether, DNS, Raw

pkts = rdpcap("ass3.pcap")

# 1. List protocols
protocols = set()
# 2. Foreign hosts & MAC
foreign_hosts, macs = set(), {}
# 3. HTTP GET→OK timing
http_times = []
# 4. Addresses (local & iiitg.ac.in lookup)
my_ip, iiitg_ip = None, None
# 5. Captured HTTP messages
http_msgs = []

for p in pkts:
    # --- Protocols ---
    layer = p
    while layer:
        protocols.add(layer.__class__.__name__)
        layer = layer.payload if layer.payload.__class__.__name__ != "NoPayload" else None

    # --- IPs & MACs ---
    if p.haslayer(IP):
        ip = p[IP]
        if not my_ip: my_ip = ip.src
        foreign_hosts.update([ip.dst, ip.src])
        if p.haslayer(Ether):
            macs[ip.src] = p[Ether].src
            macs[ip.dst] = p[Ether].dst

    # --- HTTP GET -> OK ---
    if p.haslayer(TCP) and p.haslayer(Raw):
        data = p[Raw].load.decode(errors="ignore")
        if "GET" in data: start = p.time
        if "200 OK" in data and 'start' in locals():
            http_times.append(p.time - start); del start
        if "HTTP" in data and len(http_msgs) < 5:
            http_msgs.append(data.split("\r\n")[0])

    # --- DNS lookup for iiitg.ac.in ---
    if p.haslayer(DNS) and p[DNS].an:
        for i in range(p[DNS].ancount):
            ans = p[DNS].an[i]
            if b"iiitg.ac.in" in ans.rrname:
                iiitg_ip = ans.rdata

print("\n===== Assignment Output =====")
print("1. Protocols seen:", protocols)
print("2. Foreign hosts:", foreign_hosts)
print("   MAC addresses (if same LAN):", macs if macs else "Not visible (beyond LAN)")
print("3. HTTP GET->200 OK times:", http_times)
print("4. My IP:", my_ip, "| iiitg.ac.in IP:", iiitg_ip)
print("5. Sample HTTP messages:", http_msgs)
