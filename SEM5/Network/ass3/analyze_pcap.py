from scapy.all import rdpcap, IP, TCP, Ether, DNS, Raw
from collections import Counter

pkts = rdpcap("ass3.pcap")

protocols = set()
foreign_hosts, macs = set(), {}
http_times = []
src_ips = Counter(p[IP].src for p in pkts if p.haslayer(IP))
my_ip = src_ips.most_common(1)[0][0] if src_ips else None
iiitg_ip = None
http_msgs = []

for p in pkts:
    layer = p
    while layer:
        protocols.add(layer.__class__.__name__)
        layer = layer.payload if layer.payload.__class__.__name__ != "NoPayload" else None

    if p.haslayer(IP):
        ip = p[IP]
        foreign_hosts.update([ip.dst, ip.src])
        if p.haslayer(Ether):
            macs[ip.src] = p[Ether].src
            macs[ip.dst] = p[Ether].dst

    if p.haslayer(TCP) and p.haslayer(Raw):
        data = p[Raw].load.decode(errors="ignore")
        if "GET" in data: start = p.time
        if "200 OK" in data and 'start' in locals():
            http_times.append(p.time - start); del start
        if "HTTP" in data and len(http_msgs) < 5:
            http_msgs.append(data.split("\r\n")[0])

    if p.haslayer(DNS) and p[DNS].an:
        for i in range(p[DNS].ancount):
            ans = p[DNS].an[i]
            if b"iiitg.ac.in" in ans.rrname:
                iiitg_ip = ans.rdata

print("\n1. Protocols seen:", protocols)
print("\n2. Foreign hosts:", foreign_hosts)
print("\n   MAC addresses (if same LAN):", macs if macs else "Not visible (beyond LAN)")
print("\n3. HTTP GET->200 OK times:", http_times)
print("\n4. My IP:", my_ip, "| iiitg.ac.in IP:", iiitg_ip)
print("\n5. Sample HTTP messages:", http_msgs)
