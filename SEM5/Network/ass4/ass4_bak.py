import random

# -------------------------------
# Part A: Bit Stuffing / De-stuffing
# -------------------------------

def bit_stuff(bits: str) -> str:
    """Insert a '0' after any run of five consecutive '1's."""
    out, count = [], 0
    for b in bits:
        if b not in "01":   # ignore non-bits
            continue
        out.append(b)
        if b == "1":
            count += 1
            if count == 5:
                out.append("0")  # stuffed 0
                count = 0
        else:
            count = 0
    return "".join(out)

def bit_destuff(stuffed: str) -> str:
    """Remove stuffed '0's after five consecutive '1's."""
    out, count, i = [], 0, 0
    while i < len(stuffed):
        b = stuffed[i]
        if b not in "01":
            i += 1
            continue
        out.append(b)
        if b == "1":
            count += 1
            if count == 5:
                i += 1  # skip stuffed 0
                if i < len(stuffed) and stuffed[i] == "0":
                    pass
                count = 0
        else:
            count = 0
        i += 1
    return "".join(out)

def measure_overhead(orig: str, stuffed: str) -> float:
    if not orig: return 0.0
    return (len(stuffed) - len(orig)) / len(orig)


# -------------------------------
# Part B: Character (Byte) Stuffing
# -------------------------------

DLE, STX, ETX = b"\x10", b"\x02", b"\x03"  # control chars

def char_stuff(payload: bytes) -> bytes:
    """Frame with DLE-STX ... DLE-ETX, doubling DLE inside payload."""
    stuffed = payload.replace(DLE, DLE + DLE)
    return DLE + STX + stuffed + DLE + ETX

def char_destuff(frame: bytes) -> bytes:
    """Recover payload by un-doubling DLE inside frame."""
    if not (frame.startswith(DLE + STX) and frame.endswith(DLE + ETX)):
        raise ValueError("Invalid frame")
    inner = frame[2:-2]
    return inner.replace(DLE + DLE, DLE)


# -------------------------------
# Demo & Verification
# -------------------------------
if __name__ == "__main__":
    # Part A tests
    tests = [
        "011111101111110111110",    # sample
        "111111111111",             # worst case (all ones)
        "",                         # empty
        "0000000",                  # all zeros
        "".join(random.choice("01") for _ in range(50))  # random
    ]

    print("=== Bit Stuffing ===")
    for t in tests:
        s = bit_stuff(t)
        d = bit_destuff(s)
        print(f"\nInput:   {t}")
        print(f"Stuffed: {s}")
        print(f"Destuff: {d}")
        print(f"Correct? {d == t}")
        print(f"Overhead: {measure_overhead(t, s):.2%}")

    # Part B test
    print("\n=== Character Stuffing ===")
    payload = b"HELLO" + DLE + b"WORLD"
    frame = char_stuff(payload)
    recovered = char_destuff(frame)
    print(f"Payload:   {payload}")
    print(f"Framed:    {frame}")
    print(f"Recovered: {recovered}")
    print(f"Correct?   {recovered == payload}")
