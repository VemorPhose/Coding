def solution(centerCapacities, dailyLog):
    n = len(centerCapacities)
    processed = [0] * n
    capacity = centerCapacities[:]
    closed = [False] * n
    current = 0
    
    for log in dailyLog:
        if log == "PACKAGE":
            if all(closed):
                continue

            start_node = current
            while closed[current] or capacity[current] == 0:
                current = (current + 1) % n
                
                if current == start_node:
                    for i in range(n):
                        if not closed[i]:
                            capacity[i] = centerCapacities[i]
            
            processed[current] += 1
            capacity[current] -= 1
            
            if capacity[current] == 0:
                current = (current + 1) % n
        else:
            idx = int(log[8:])
            closed[idx] = True
            capacity[idx] = 0

    max_packages = -1
    result_idx = -1
    for i in range(n):
        if processed[i] >= max_packages:
            max_packages = processed[i]
            result_idx = i
            
    return result_idx

def main():
    # Read center capacities
    centerCapacities = list(map(int, input().split()))
    
    # Read daily log
    dailyLog = []
    try:
        while True:
            line = input().strip()
            if line:
                dailyLog.append(line)
    except EOFError:
        pass
    
    result = solution(centerCapacities, dailyLog)
    print(result)

if __name__ == "__main__":
    main()