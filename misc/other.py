from collections import deque

def getMinPath(coins_count, coins, tree_nodes, tree_edges, tree_from, tree_to):
    adj = [[] for _ in range(tree_nodes)]
    deg = [0] * tree_nodes

    for i in range(tree_edges):
        u = tree_from[i]
        v = tree_to[i]
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1

    q = deque()
    removed = [False] * tree_nodes

    # Step 1: Prune all leaves with no coin (once)
    for i in range(tree_nodes):
        if deg[i] == 1 and coins[i] == 0:
            q.append(i)

    while q:
        u = q.popleft()
        removed[u] = True
        for v in adj[u]:
            if removed[v]:
                continue
            deg[v] -= 1
            if deg[v] == 1 and coins[v] == 0:
                q.append(v)

    # Step 2: Prune all remaining leaves two more times
    for _ in range(2):
        leaves = []
        for i in range(tree_nodes):
            if not removed[i] and deg[i] == 1:
                leaves.append(i)

        for u in leaves:
            removed[u] = True
            for v in adj[u]:
                if not removed[v]:
                    deg[v] -= 1

    # Count remaining edges
    cnt = 0
    for u in range(tree_nodes):
        if removed[u]:
            continue
        for v in adj[u]:
            if not removed[v] and u < v:
                cnt += 1

    return cnt * 2

def main():
    tree_nodes = int(input())
    coins = [int(input()) for _ in range(tree_nodes)]

    tree_edges = tree_nodes - 1
    tree_from = []
    tree_to = []
    for _ in range(tree_edges):
        u, v = map(int, input().split())
        tree_from.append(u)
        tree_to.append(v)

    result = getMinPath(sum(coins), coins, tree_nodes, tree_edges, tree_from, tree_to)
    print(result)

if __name__ == "__main__":
    main()
