import java.util.*;

public class ass9a {
    public static class Student {
        String name;
        int roll;
        String birthyear;

        Student (String name, int roll, String birthyear) {
            this.name = name;
            this.roll = roll;
            this.birthyear = birthyear;
        }

        public String getFirstName() {
            return name.split(" ")[0];
        }
     
        public String getTitle() {
            return name.split(" ").length > 1 ? name.split(" ")[1] : "";
        }
    }

    public static void sortyear(ArrayList<Student> students) {
        int n = students.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (students.get(j).birthyear.compareTo(students.get(j + 1).birthyear) > 0) {
                    Student temp = students.get(j);
                    students.set(j, students.get(j + 1));
                    students.set(j + 1, temp);
                }
            }
        }
    }
 
    public static void sortrollreverse(ArrayList<Student> students) {
        int n = students.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (students.get(j).roll < students.get(j + 1).roll) {
                    Student temp = students.get(j);
                    students.set(j, students.get(j + 1));
                    students.set(j + 1, temp);
                }
            }
        }
    }
 
    public static void sorttitle(ArrayList<Student> students) {
        int n = students.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (students.get(j).getTitle().compareTo(students.get(j + 1).getTitle()) > 0) {
                    Student temp = students.get(j);
                    students.set(j, students.get(j + 1));
                    students.set(j + 1, temp);
                }
            }
        }
    }
 
    public static void sortfname(ArrayList<Student> students) {
        int n = students.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (students.get(j).getFirstName().compareTo(students.get(j + 1).getFirstName()) > 0) {
                    Student temp = students.get(j);
                    students.set(j, students.get(j + 1));
                    students.set(j + 1, temp);
                }
            }
        }
    }
    
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Student> students = new ArrayList<>();

        int n = 5;
        students.add(new Student("ram sharma", 10, "101"));
        students.add(new Student("karan verma", 30, "501"));
        students.add(new Student("diljit", 50, "401"));
        students.add(new Student("sunny reddy", 40, "201"));
        students.add(new Student("honey singh", 20, "301"));

        sortfname(students);
        System.out.println("\nStudents sorted by first name: ");
        for (Student student : students) {
            System.out.println(student.name + ", " + student.roll + ", " + student.birthyear);
        }
        sorttitle(students);
        System.out.println("\nStudents sorted by title: ");
        for (Student student : students) {
            System.out.println(student.name + ", " + student.roll + ", " + student.birthyear);
        }
        sortrollreverse(students);
        System.out.println("\nStudents sorted by roll number descending: ");
        for (Student student : students) {
            System.out.println(student.name + ", " + student.roll + ", " + student.birthyear);
        }
        sortyear(students);
        System.out.println("\nStudents sorted by birth year: ");
        for (Student student : students) {
            System.out.println(student.name + ", " + student.roll + ", " + student.birthyear);
        }

        sc.close();
    }
}