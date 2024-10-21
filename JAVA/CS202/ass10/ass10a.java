import java.util.*;

public class ass10a {
    public static class Person {
        int age;
        public void eat () {
            System.out.println("Eating...");
        }
        public void sleep () {
            System.out.println("Sleeping...");
        }
        public Person () {}
        public Person (int age) {
            this.age = age;
        }
    }

    interface Driver {
        public int driveCar ();
        public int driveBike ();
    }

    interface Singer {
        public void riyaz ();
        public int sing ();
    }

    public static class Employee extends Person implements Driver, Singer {
        public int driveCar () {
            return this.age < 40 ? 10 : 0;
        }
        public int driveBike () {
            return this.age < 40 ? 5 : 0;
        }
        public void riyaz () {
            System.out.println("Doing Riyaz...");
        }
        public int sing () {
            return this.age < 20 ? 15 : 0;
        }
        public int officeWork () {
            return this.age < 40? 20 : 10;
        }
        public Employee () {}
        public Employee (int age) {
            super(age);
        }
    }

    public static void bubbleSort(Employee[] employees, int[] EIFs) {
        int n = 5;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (EIFs[j] > EIFs[j+1]) {
                    Employee temp = employees[j];
                    employees[j] = employees[j+1];
                    employees[j+1] = temp;
                }
            }
        }
    }

    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter employee's age: ");
        int age = sc.nextInt();
        Employee e = new Employee(age);
        
        Driver d = (Driver) e;
        System.out.println("Drive Car: " + d.driveCar());
        // System.out.println("Sing: " + d.sing()); // doesn't work

        Singer s = (Singer) e;
        System.out.println("Sing: " + s.sing());
        // System.out.println("Drive Car: " + s.driveCar()); // doesn't work

        Employee[] employees = new Employee[5];
        int[] EIFs = new int[5];
        for (int i = 0; i < 5; i++) {
            System.out.print("Enter employee's age: ");
            age = sc.nextInt();
            employees[i] = new Employee(age);
            EIFs[i] = employees[i].driveCar() + employees[i].driveBike() + employees[i].sing() + employees[i].officeWork();
        }
        bubbleSort(employees, EIFs);
        for (Employee employee : employees) {
            System.out.print(employee.age + " ");
        }
        System.out.println();
    }
}