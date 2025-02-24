import numpy as np
import time
import matplotlib.pyplot as plt
import heapq
import random

class PuzzleState:
    def __init__(self, state, parent=None, action=None, cost=0):
        self.state = state
        self.parent = parent
        self.action = action
        self.cost = cost
        self.size = len(state)
        
    def __str__(self):
        return '\n'.join([' '.join(map(str, row)) for row in self.state])
        
    def find_blank(self):
        return next((i, j) for i in range(self.size) 
                   for j in range(self.size) if self.state[i][j] == 0)

# [Keep all helper functions: generate_random_state, get_successors, 
# get_inversions, is_solvable]

# Heuristic functions
def misplaced_tiles(state, goal):
    count = 0
    for i in range(len(state)):
        for j in range(len(state)):
            if state[i][j] != 0 and state[i][j] != goal[i][j]:
                count += 1
    return count

def manhattan_distance(state, goal):
    n = len(state)
    distance = 0
    goal_pos = {}
    for i in range(n):
        for j in range(n):
            goal_pos[goal[i][j]] = (i, j)
    
    for i in range(n):
        for j in range(n):
            if state[i][j] != 0:
                gi, gj = goal_pos[state[i][j]]
                distance += abs(i - gi) + abs(j - gj)
    return distance

def linear_conflict(state, goal):
    n = len(state)
    conflict = manhattan_distance(state, goal)
    
    # Add linear conflict cost
    for i in range(n):
        for j in range(n):
            if state[i][j] == 0:
                continue
            goal_i, goal_j = None, None
            for x in range(n):
                for y in range(n):
                    if goal[x][y] == state[i][j]:
                        goal_i, goal_j = x, y
                        break
            
            # Check row and column conflicts
            if i == goal_i:
                for k in range(j + 1, n):
                    if state[i][k] != 0:
                        k_goal_i, k_goal_j = None, None
                        for x in range(n):
                            for y in range(n):
                                if goal[x][y] == state[i][k]:
                                    k_goal_i, k_goal_j = x, y
                                    break
                        if i == k_goal_i and goal_j > k_goal_j:
                            conflict += 2
    return conflict

def astar_solve(initial_state, goal_state, heuristic_func, timeout=60):
    if not is_solvable(initial_state):
        return None, 0, 0
        
    start_time = time.time()
    initial = PuzzleState(initial_state)
    frontier = [(0 + heuristic_func(initial_state, goal_state), 0, id(initial), initial)]
    heapq.heapify(frontier)
    visited = set()
    nodes_expanded = 0
    
    while frontier and (time.time() - start_time) < timeout:
        _, cost, _, current = heapq.heappop(frontier)
        state_tuple = tuple(map(tuple, current.state))
        
        if current.state == goal_state:
            path = []
            while current.parent:
                path.append(current.action)
                current = current.parent
            return path[::-1], time.time() - start_time, nodes_expanded
            
        if state_tuple not in visited:
            visited.add(state_tuple)
            nodes_expanded += 1
            for successor in get_successors(current):
                if tuple(map(tuple, successor.state)) not in visited:
                    h = heuristic_func(successor.state, goal_state)
                    f = successor.cost + h
                    heapq.heappush(frontier, (f, successor.cost, id(successor), successor))
    
    return None, time.time() - start_time, nodes_expanded

# [Keep run_experiment and plot_results functions]

def main():
    n_values = [2, 3]
    heuristics = {
        'Misplaced Tiles': misplaced_tiles,
        'Manhattan Distance': manhattan_distance,
        'Linear Conflict': linear_conflict
    }
    
    astar_results = {name: [] for name in heuristics}
    
    for n in n_values:
        print(f"\nTesting for n={n}")
        for heur_name, heur_func in heuristics.items():
            print(f"\nRunning A* with {heur_name}")
            avg_time, avg_nodes, _, _ = run_experiment(
                n, astar_solve, heur_func, f"A* - {heur_name}")
            if avg_time is not None:
                astar_results[heur_name].append((avg_time, avg_nodes))
    
    plot_results(n_values, "A* Search", astar_results)

if __name__ == "__main__":
    main()