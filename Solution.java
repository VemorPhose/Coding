import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Solution {

    public static int timeRequired(int N, int M, List<Integer> T, List<Integer> F) {
        if (M == 0) return 0;

        List<List<Long>> protime = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            List<Long> row = new ArrayList<>();
            for (int j = 0; j < M; j++) {
                row.add((long) T.get(i) * F.get(j));
            }
            protime.add(row);
        }

        long[] st = new long[M];
        for (int j = 1; j < M; j++) {
            long mst = st[j - 1];
            for (int i = 0; i < N; i++) {
                long wpf = st[j - 1];
                for (int k = 0; k <= i; k++) {
                    wpf += protime.get(k).get(j - 1);
                }
                long caa = 0;
                for (int k = 0; k < i; k++) {
                    caa += protime.get(k).get(j);
                }
                long rqw = wpf - caa;
                mst = Math.max(mst, rqw);
            }
            st[j] = mst;
        }

        long tt = st[M - 1];
        for (int i = 0; i < N; i++) {
            tt += protime.get(i).get(M - 1);
        }

        return (int) tt;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int M = scanner.nextInt();

        List<Integer> T = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            T.add(scanner.nextInt());
        }

        List<Integer> F = new ArrayList<>();
        for (int i = 0; i < M; i++) {
            F.add(scanner.nextInt());
        }

        int result = timeRequired(N, M, T, F);
        System.out.println(result);
        scanner.close();
    }
}