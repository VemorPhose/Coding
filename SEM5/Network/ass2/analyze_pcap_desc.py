#!/usr/bin/env python3
import argparse
from collections import Counter
from scapy.all import (
    PcapReader, Ether, IP, IPv6, TCP, UDP, ICMP, ICMPv6Unknown, DNS
)

def iter_layers(pkt):
    """Yield scapy layer objects from outermost to innermost."""
    layer = pkt
    while layer:
        yield layer
        # scapy uses .payload; stop at NoPayload
        layer = getattr(layer, "payload", None)
        if not layer or layer.__class__.__name__ == "NoPayload":
            break

def layer_names(pkt):
    """Return a list of layer names in this packet."""
    return [l.__class__.__name__ for l in iter_layers(pkt)]

def is_ping(pkt):
    # ICMP (IPv4) or ICMPv6
    return pkt.haslayer(ICMP) or pkt.haslayer(ICMPv6Unknown)

def is_dns(pkt):
    # DNS typically over UDP/TCP port 53; also check DNS layer
    if pkt.haslayer(DNS):
        return True
    if pkt.haslayer(UDP):
        u = pkt[UDP]
        return u.sport == 53 or u.dport == 53
    if pkt.haslayer(TCP):
        t = pkt[TCP]
        return t.sport == 53 or t.dport == 53
    return False

def is_ssh(pkt):
    if not pkt.haslayer(TCP):
        return False
    t = pkt[TCP]
    return t.sport == 22 or t.dport == 22

def is_httpish(pkt):
    # Treat curl as HTTP/HTTPS by ports 80 or 443 (not parsing HTTP payload)
    if not pkt.haslayer(TCP):
        return False
    t = pkt[TCP]
    return any(p in (80, 443) for p in (t.sport, t.dport))

def pkt_len_bytes(pkt):
    # len(pkt) is fine for pcap-level size (incl. L2+ headers).
    # The assignment’s guideline also suggests using len(packet).
    try:
        return len(pkt)
    except Exception:
        return 0

def ip_src_dst(pkt):
    """Return (src, dst) IP strings if IP/IPv6 exists, else (None, None)."""
    if pkt.haslayer(IP):
        return pkt[IP].src, pkt[IP].dst
    if pkt.haslayer(IPv6):
        return pkt[IPv6].src, pkt[IPv6].dst
    return None, None

def main():
    parser = argparse.ArgumentParser(description="PCAP analyzer")
    parser.add_argument("pcap", help="Path to pcap file (e.g., capture.pcap)")
    parser.add_argument(
        "--local", nargs="+", default=[],
        help="Local IP address(es) to split bytes into sent vs received (optional)"
    )
    parser.add_argument(
        "--examples-per-type", type=int, default=5,
        help="Max number of example packets to print per traffic type"
    )
    args = parser.parse_args()

    # Stats
    total_packets = 0
    ipv4_packets = 0
    ipv6_packets = 0

    unique_ips = set()
    dst_ports = set()

    total_bytes = 0
    bytes_sent = 0
    bytes_received = 0

    counts = {
        "ping": 0,
        "dns": 0,
        "ssh": 0,
        "httpish": 0,  # curl-ish
    }

    # Store a handful of example header stacks for each category
    examples = {
        "ping": [],
        "dns": [],
        "ssh": [],
        "httpish": [],
    }

    # Count transport destination ports across TCP/UDP
    with PcapReader(args.pcap) as pcap:
        for pkt in pcap:
            total_packets += 1
            total_bytes += pkt_len_bytes(pkt)

            # L3 classification
            if pkt.haslayer(IP):
                ipv4_packets += 1
                src, dst = pkt[IP].src, pkt[IP].dst
                unique_ips.update([src, dst])
            elif pkt.haslayer(IPv6):
                ipv6_packets += 1
                src, dst = pkt[IPv6].src, pkt[IPv6].dst
                unique_ips.update([src, dst])
            else:
                src = dst = None  # non-IP packet (e.g., ARP)
            
            # Sent vs Received if local IPs provided
            if args.local and (src or dst):
                pkt_bytes = pkt_len_bytes(pkt)
                if src in args.local:
                    bytes_sent += pkt_bytes
                elif dst in args.local:
                    bytes_received += pkt_bytes
                # else: outside-to-outside, ignore for S/R split

            # Destination port collection
            if pkt.haslayer(TCP):
                dst_ports.add(pkt[TCP].dport)
            if pkt.haslayer(UDP):
                dst_ports.add(pkt[UDP].dport)

            # Classification for (ping, dns, ssh, curl-ish)
            # and store limited examples of header stacks.
            def maybe_store(kind):
                if len(examples[kind]) < args.examples_per_type:
                    examples[kind].append(layer_names(pkt))

            if is_ping(pkt):
                counts["ping"] += 1
                maybe_store("ping")

            if is_dns(pkt):
                counts["dns"] += 1
                maybe_store("dns")

            if is_ssh(pkt):
                counts["ssh"] += 1
                maybe_store("ssh")

            if is_httpish(pkt):
                counts["httpish"] += 1
                maybe_store("httpish")

    # Output
    print("\nAnalysis Results")
    print(f"1) Total number of packets observed: {total_packets}")

    print(f"2) Packets for ping identified: {counts['ping']}")
    if examples["ping"]:
        print("   Example headers (a few):")
        for i, layers in enumerate(examples["ping"], 1):
            print(f"     {i}. " + " | ".join(layers))

    print(f"3) Packets for nslookup (DNS) identified: {counts['dns']}")
    if examples["dns"]:
        print("   Example headers (a few):")
        for i, layers in enumerate(examples["dns"], 1):
            print(f"     {i}. " + " | ".join(layers))

    print(f"4) Packets for ssh identified: {counts['ssh']}")
    if examples["ssh"]:
        print("   Example headers (a few):")
        for i, layers in enumerate(examples["ssh"], 1):
            print(f"     {i}. " + " | ".join(layers))

    print(f"5) Packets for curl/HTTP(S) identified: {counts['httpish']}")
    if examples["httpish"]:
        print("   Example headers (a few):")
        for i, layers in enumerate(examples["httpish"], 1):
            print(f"     {i}. " + " | ".join(layers))

    print(f"6) Total number of unique IP addresses: {len(unique_ips)}")

    if args.local:
        print(f"7) Total bytes sent vs received (from local {args.local}): "
              f"{bytes_sent} / {bytes_received}")
    else:
        print(f"7) Total bytes observed (no local IP provided to split): {total_bytes}")

    print(f"8) Total IPv4 vs IPv6 packets: {ipv4_packets} / {ipv6_packets}")

    # Sort ports for stable output
    sorted_ports = sorted(dst_ports)
    print(f"9) Unique destination ports observed ({len(sorted_ports)}):")
    if sorted_ports:
        # Print in compact rows
        row = []
        for p in sorted_ports:
            row.append(str(p))
            if len(row) == 20:
                print("   " + " ".join(row))
                row = []
        if row:
            print("   " + " ".join(row))
    else:
        print("   (none)")

if __name__ == "__main__":
    main()
