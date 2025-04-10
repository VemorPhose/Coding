import heapq

def get_successors(node, graph):
	n = len(graph)
	successors = []
	for j in range(n):
		if graph[node][j] != -1:
			successors.append(j)
	return successors

def heuristic(node):
	if node == 0:
		return 35
	elif node == 1:
		return 25
	elif node == 2:
		return 30
	elif node == 3:
		return 20
	elif node == 4:
		return 18
	elif node == 5:
		return 16
	elif node == 6:
		return 10
	elif node == 7:
		return 8
	elif node == 8:
		return 5
	else:
		return 0

def node_map(node):
	if node == 0:
		return 'A'
	elif node == 1:
		return 'B'
	elif node == 2:
		return 'C'
	elif node == 3:
		return 'D'
	elif node == 4:
		return 'E'
	elif node == 5:
		return 'F'
	elif node == 6:
		return 'G'
	elif node == 7:
		return 'H'
	elif node == 8:
		return 'I'
	else:
		return 'J'


graph = [[-1, ] * 10 for _ in range(10)]
graph[0][1] = 8
graph[0][2] = 12
graph[1][3] = 10
graph[1][4] = 15
graph[2][4] = 6
graph[2][5] = 14
graph[3][6] = 9
graph[4][6] = 13
graph[4][7] = 11
graph[5][7] = 7
graph[5][8] = 10
graph[6][9] = 18
graph[7][9] = 15
graph[8][9] = 9

# using a* algorithm
vis = set()
initial_node = 0
goal_node = 9
frontier = [(heuristic(initial_node), initial_node, [initial_node, ], 0)]
heapq.heapify(frontier)

iter_no = 0
print("For travelling from A to J:")

while frontier:
	print("Priority queue at iteration", iter_no, ":\n", frontier)
	print("Explored set at iteration", iter_no, ":", vis)
	print()
	iter_no += 1

	_, cur, path, cost = heapq.heappop(frontier)
	vis.add(cur)
	if cur == goal_node:
		actual_path = [node_map(n) for n in path]
		print("\nPath:", actual_path)
		print("Total travel time:", cost)
		break

	successors = get_successors(cur, graph)
	# print(successors)
	for suc in successors:
		new_cost = cost + graph[cur][suc]
		heapq.heappush(frontier, (new_cost + heuristic(suc), suc, path + [suc, ], new_cost))

print("\n")
print("Now for going from A to F then J:")
# using a* in two steps
total_path = []
total_cost = 0

vis = set()
initial_node = 0
goal_node = 5
frontier = [(heuristic(initial_node), initial_node, [initial_node, ], 0)]
heapq.heapify(frontier)

iter_no = 0
print("For travelling from A to F:")

while frontier:
	print("Priority queue at iteration", iter_no, ":\n", frontier)
	print("Explored set at iteration", iter_no, ":", vis)
	print()
	iter_no += 1

	_, cur, path, cost = heapq.heappop(frontier)
	vis.add(cur)
	if cur == goal_node:
		total_path = total_path + path
		total_cost = total_cost + cost
		actual_path = [node_map(n) for n in path]
		print("\nPath:", actual_path)
		print("Total travel time:", cost)
		break

	successors = get_successors(cur, graph)
	# print(successors)
	for suc in successors:
		new_cost = cost + graph[cur][suc]
		heapq.heappush(frontier, (new_cost + heuristic(suc), suc, path + [suc, ], new_cost))

total_path.pop()
vis = set()
initial_node = 5
goal_node = 9
frontier = [(heuristic(initial_node), initial_node, [initial_node, ], 0)]
heapq.heapify(frontier)

iter_no = 0
print("\nFor travelling from F to J:")

while frontier:
	print("Priority queue at iteration", iter_no, ":\n", frontier)
	print("Explored set at iteration", iter_no, ":", vis)
	print()
	iter_no += 1

	_, cur, path, cost = heapq.heappop(frontier)
	vis.add(cur)
	if cur == goal_node:
		total_path = total_path + path
		total_cost = total_cost + cost
		break

	successors = get_successors(cur, graph)
	# print(successors)
	for suc in successors:
		new_cost = cost + graph[cur][suc]
		heapq.heappush(frontier, (new_cost + heuristic(suc), suc, path + [suc, ], new_cost))

print("\nPath from A to F then J:")
actual_path = [node_map(node) for node in total_path]
print(actual_path)
print("Total travel time:", total_cost)
if total_cost <= 60:
	print("Total travel time is within battery constraint of 60 minutes.")
else:
	print("Total travel time is not within battery constraint of 60 minutes.")
print('\n')