import java.io.*;
import java.util.*;

class Result {
    public static int getMinPath(List<Integer> coins, int treeNodes, List<Integer> treeFrom, List<Integer> treeTo) {
        // Build adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < treeNodes; i++) {
            adj.add(new ArrayList<>());
        }
        
        for (int i = 0; i < treeFrom.size(); i++) {
            int u = treeFrom.get(i);
            int v = treeTo.get(i);
            adj.get(u).add(v);
            adj.get(v).add(u);
        }
        
        // Find all coin positions
        Set<Integer> coinPositions = new HashSet<>();
        for (int i = 0; i < coins.size(); i++) {
            if (coins.get(i) == 1) {
                coinPositions.add(i);
            }
        }
        
        if (coinPositions.isEmpty()) return 0;
        
        // For each node, find all nodes within distance 2
        List<Set<Integer>> reachable = new ArrayList<>();
        for (int i = 0; i < treeNodes; i++) {
            reachable.add(new HashSet<>());
            // BFS to find nodes within distance 2
            Queue<Integer> queue = new LinkedList<>();
            boolean[] visited = new boolean[treeNodes];
            int[] dist = new int[treeNodes];
            
            queue.offer(i);
            visited[i] = true;
            dist[i] = 0;
            reachable.get(i).add(i);
            
            while (!queue.isEmpty()) {
                int curr = queue.poll();
                if (dist[curr] < 2) {
                    for (int next : adj.get(curr)) {
                        if (!visited[next]) {
                            visited[next] = true;
                            dist[next] = dist[curr] + 1;
                            reachable.get(i).add(next);
                            queue.offer(next);
                        }
                    }
                }
            }
        }
        
        // Find which coins can be collected from each node
        List<Set<Integer>> coinsFromNode = new ArrayList<>();
        for (int i = 0; i < treeNodes; i++) {
            coinsFromNode.add(new HashSet<>());
            for (int coin : coinPositions) {
                if (reachable.get(i).contains(coin)) {
                    coinsFromNode.get(i).add(coin);
                }
            }
        }
        
        // Convert coin positions to indices for bitmask
        List<Integer> coinList = new ArrayList<>(coinPositions);
        int n = coinList.size();
        
        // For each node, create bitmask of coins it can collect
        int[] nodeCoinMask = new int[treeNodes];
        for (int i = 0; i < treeNodes; i++) {
            for (int j = 0; j < n; j++) {
                if (coinsFromNode.get(i).contains(coinList.get(j))) {
                    nodeCoinMask[i] |= (1 << j);
                }
            }
        }
        
        // Precompute distances between all nodes
        int[][] dist = new int[treeNodes][treeNodes];
        for (int start = 0; start < treeNodes; start++) {
            Arrays.fill(dist[start], -1);
            Queue<Integer> queue = new LinkedList<>();
            queue.offer(start);
            dist[start][start] = 0;
            
            while (!queue.isEmpty()) {
                int curr = queue.poll();
                for (int next : adj.get(curr)) {
                    if (dist[start][next] == -1) {
                        dist[start][next] = dist[start][curr] + 1;
                        queue.offer(next);
                    }
                }
            }
        }
        
        int allCoinsMask = (1 << n) - 1;
        int minPath = Integer.MAX_VALUE;
        
        // Try starting from each node
        for (int start = 0; start < treeNodes; start++) {
            // DP: dp[mask][node] = minimum distance to collect coins in mask and be at node
            int[][] dp = new int[1 << n][treeNodes];
            for (int i = 0; i < (1 << n); i++) {
                Arrays.fill(dp[i], Integer.MAX_VALUE);
            }
            
            // Initialize: start at 'start' node and collect coins reachable from there
            dp[nodeCoinMask[start]][start] = 0;
            
            // Fill DP table
            for (int mask = 0; mask < (1 << n); mask++) {
                for (int curr = 0; curr < treeNodes; curr++) {
                    if (dp[mask][curr] == Integer.MAX_VALUE) continue;
                    
                    // Try moving to each other node
                    for (int next = 0; next < treeNodes; next++) {
                        if (next == curr) continue;
                        
                        int newMask = mask | nodeCoinMask[next];
                        int newDist = dp[mask][curr] + dist[curr][next];
                        dp[newMask][next] = Math.min(dp[newMask][next], newDist);
                    }
                }
            }
            
            // Check if we can collect all coins and return to start
            if (dp[allCoinsMask][start] != Integer.MAX_VALUE) {
                minPath = Math.min(minPath, dp[allCoinsMask][start]);
            }
            
            // Also check paths that end at other nodes but can return to start
            for (int end = 0; end < treeNodes; end++) {
                if (dp[allCoinsMask][end] != Integer.MAX_VALUE) {
                    int totalPath = dp[allCoinsMask][end] + dist[end][start];
                    minPath = Math.min(minPath, totalPath);
                }
            }
        }
        
        return minPath == Integer.MAX_VALUE ? -1 : minPath;
    }
}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        
        int treeNodes = Integer.parseInt(bufferedReader.readLine().trim());
        
        List<Integer> coins = new ArrayList<>();
        for (int i = 0; i < treeNodes; i++) {
            coins.add(Integer.parseInt(bufferedReader.readLine().trim()));
        }
        
        String[] treeNodesEdges = bufferedReader.readLine().trim().split(" ");
        int treeNodesCount = Integer.parseInt(treeNodesEdges[0]);
        int treeEdges = Integer.parseInt(treeNodesEdges[1]);
        
        List<Integer> treeFrom = new ArrayList<>();
        List<Integer> treeTo = new ArrayList<>();
        
        for (int i = 0; i < treeEdges; i++) {
            String[] treeFromTo = bufferedReader.readLine().trim().split(" ");
            treeFrom.add(Integer.parseInt(treeFromTo[0]));
            treeTo.add(Integer.parseInt(treeFromTo[1]));
        }
        
        int result = Result.getMinPath(coins, treeNodes, treeFrom, treeTo);
        System.out.println(result);
        
        bufferedReader.close();
    }
}