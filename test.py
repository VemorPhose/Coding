from collections import deque, defaultdict
import sys

def mark_important(cur, parent, imp, tree, need_edges):
    posb = cur in imp
    for nxt in tree[cur]:
        if nxt != parent:
            if mark_important(nxt, cur, imp, tree, need_edges):
                need_edges.add(tuple(sorted((cur, nxt))))
                posb = True
    return posb

def bfs(start, target, tree):
    dist = [-1] * len(tree)
    q = deque()
    q.append(start)
    dist[start] = 0

    while q:
        v = q.popleft()
        if v == target:
            return dist[v]
        for u in tree[v]:
            if dist[u] == -1:
                dist[u] = dist[v] + 1
                q.append(u)
    return -1

def get_minimum_time(tree_nodes, tree_from, tree_to, start_node, end_node, task_nodes):
    # Build adjacency list
    tree = [[] for _ in range(tree_nodes + 1)]
    for u, v in zip(tree_from, tree_to):
        tree[u].append(v)
        tree[v].append(u)

    # Insert important nodes
    imp = set(task_nodes)
    imp.add(start_node)
    imp.add(end_node)

    # Find all required edges in minimal subtree
    need_edges = set()
    mark_important(start_node, -1, imp, tree, need_edges)

    # Find direct distance between start and end
    direct_dist = bfs(start_node, end_node, tree)

    # Total time = 2 * (edges in minimal subtree) - direct path length
    return len(need_edges) * 2 - direct_dist

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    idx = 0

    n = int(data[idx]); idx += 1
    m = int(data[idx]); idx += 1

    tree_from = []
    tree_to = []
    for _ in range(m):
        u = int(data[idx]); idx += 1
        v = int(data[idx]); idx += 1
        tree_from.append(u)
        tree_to.append(v)

    start_node = int(data[idx]); idx += 1
    end_node = int(data[idx]); idx += 1

    t = int(data[idx]); idx += 1
    task_nodes = []
    for _ in range(t):
        task_nodes.append(int(data[idx])); idx += 1

    ans = get_minimum_time(n, tree_from, tree_to, start_node, end_node, task_nodes)
    print(ans)

if __name__ == "__main__":
    main()
