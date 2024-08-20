import java.util.*;

public class ass3a {
    public static int Even=0,Odd=0;
    
    void count(int size,int A[]){
        int odd=0,even=0;
        for (int i=0;i<size;i++){
            if(A[i]%2==0){
                even++;
                Even++;
            }
            else{
                odd++;
                Odd++;
            }
        }
        System.out.println("number of even elements: " + even);
        System.out.println("number of odd elements: " + odd);
    }

    public static void main(String[] args) {
        int n;
        Scanner sc= new Scanner(System.in);
        System.out.println("Enter n:");
        n = sc.nextInt();
        ass3a methods= new ass3a();
        int A[][];
        A = new int[n][];
        int SizeArray[] = new int[n];
        System.out.println("Enter the size of " + n + " arrays: ");
        for (int i = 0; i < n; i++) {
            int temp = sc.nextInt();
            SizeArray[i] = temp;
        }
        System.out.println("Enter the elements of " + n + " arrays: ");
        for (int x = 0; x < n; x++) {
            int size = SizeArray[x];
            A[x] = new int[size];
            for (int j = 0; j < size; j++) {
                int element = sc.nextInt();
                A[x][j] = element;
            }
        }
        System.out.println("The arrays are: ");
        for (int y[]: A){
            for(int z: y){
                System.out.print(z + " ");
            }
            System.out.println();
            methods.count(y.length, y);
            System.out.println();
        }

        System.out.println("total odd elements: " + Odd);
        System.out.println("total even elements: " + Even);

        sc.close();
    }
}