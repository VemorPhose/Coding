import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class test {
    
    static boolean mark_imp(int cur, int parent, Set<Integer> imp, 
                           List<List<Integer>> tree, Set<Pair<Integer, Integer>> need_edges) {
        boolean posb = imp.contains(cur);
        
        for (int nxt : tree.get(cur)) {
            if (nxt != parent) {
                if (mark_imp(nxt, cur, imp, tree, need_edges)) {
                    need_edges.add(new Pair<>(Math.min(cur, nxt), Math.max(cur, nxt)));
                    posb = true;
                }
            }
        }
        return posb;
    }
    
    static int bfs(int start, int target, List<List<Integer>> tree) {
        int[] dist = new int[tree.size()];
        Arrays.fill(dist, -1);
        Queue<Integer> q = new LinkedList<>();
        q.add(start);
        dist[start] = 0;
        
        while (!q.isEmpty()) {
            int v = q.poll();
            if (v == target) return dist[v];
            for (int u : tree.get(v)) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.add(u);
                }
            }
        }
        return -1;
    }
    
    static int getMinimumTime(int tree_nodes, int[] tree_from, int[] tree_to, 
                             int start_node, int end_node, int[] task_nodes) {
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i <= tree_nodes; i++) {
            tree.add(new ArrayList<>());
        }
        
        for (int i = 0; i < tree_from.length; i++) {
            int u = tree_from[i], v = tree_to[i];
            tree.get(u).add(v);
            tree.get(v).add(u);
        }
        
        Set<Integer> imp = new HashSet<>();
        for (int x : task_nodes) {
            imp.add(x);
        }
        imp.add(start_node);
        imp.add(end_node);
        
        Set<Pair<Integer, Integer>> need_edges = new HashSet<>();
        mark_imp(start_node, -1, imp, tree, need_edges);
        
        int direct_dist = bfs(start_node, end_node, tree);
        return need_edges.size() * 2 - direct_dist;
    }
    
    static class Pair<T, U> {
        T first;
        U second;
        
        Pair(T first, U second) {
            this.first = first;
            this.second = second;
        }
        
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Pair)) return false;
            Pair<?, ?> pair = (Pair<?, ?>) o;
            return Objects.equals(first, pair.first) && Objects.equals(second, pair.second);
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(first, second);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // Read tree_nodes and number of edges
        String[] firstLine = br.readLine().trim().split(" ");
        int tree_nodes = Integer.parseInt(firstLine[0]);
        int edges = Integer.parseInt(firstLine[1]);
        
        // Read edges
        int[] tree_from = new int[edges];
        int[] tree_to = new int[edges];
        
        for (int i = 0; i < edges; i++) {
            String[] edge = br.readLine().trim().split(" ");
            tree_from[i] = Integer.parseInt(edge[0]);
            tree_to[i] = Integer.parseInt(edge[1]);
        }
        
        // Read number of task nodes
        int task_count = Integer.parseInt(br.readLine().trim());
        
        // Read task nodes
        int[] task_nodes = new int[task_count];
        for (int i = 0; i < task_count; i++) {
            task_nodes[i] = Integer.parseInt(br.readLine().trim());
        }
        
        // Read start node
        int start_node = Integer.parseInt(br.readLine().trim());
        
        // Read end node
        int end_node = Integer.parseInt(br.readLine().trim());
        
        // Calculate and print result
        int result = getMinimumTime(tree_nodes, tree_from, tree_to, start_node, end_node, task_nodes);
        System.out.println(result);
        
        br.close();
    }
}