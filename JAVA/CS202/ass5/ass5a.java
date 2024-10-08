import java.util.*;

public class ass5a {
    public static class Faculty {
        String name;
        int empID;

        Faculty () {}

        String toStr () {
            return "name: " + name + ", empID: " + empID;
        }
    }

    public static class Student {
        String name, branch;
        int rollNo;
        double cgpa;
        Faculty facultyAdvisor;
        static String collegeID;

        static {
            collegeID = "iiitg";
        }

        Student () {}
        Student (Faculty facad) {
            facultyAdvisor = facad;
        }

        void updateStudentRecord (double cg, Faculty facad, String br) {
            cgpa = cg;
            facultyAdvisor = facad;
            branch = br;
        }

        void getStudentDetails () {
            System.out.println("name: " + name);
            System.out.println("rollNo: " + rollNo);
            System.out.println("cgpa: " + cgpa);
            System.out.println("advisor: " + (facultyAdvisor == null ? null : facultyAdvisor.toStr()));
            System.out.println("branch: " + branch);
            System.out.println("college: " + collegeID);
        }

        Faculty getAdvisor () {
            return facultyAdvisor;
        }
    }

    static void addStudent (Student[] starr, int ind, String n, int roll, double cg, Faculty facad, String br) {
        starr[ind] = new Student(facad);
        starr[ind].name = n;
        starr[ind].rollNo = roll;
        starr[ind].cgpa = cg;
        starr[ind].branch = br;
    }

    static void deleteStudent (Student[] starr, int ind) {
        starr[ind] = null;
    }

    static void addFaculty (Faculty[] facarr, int ind, String n, int id) {
        facarr[ind] = new Faculty();
        facarr[ind].name = n;
        facarr[ind].empID = id;
    }

    static void deleteFaculty (Faculty[] facarr, int ind) {
        facarr[ind] = null;
    }

    static void sort (Student[] starr) {
        for (int i = 4; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (starr[j] == null) {
                    Student temp = starr[j];
                    starr[j] = starr[j+1];
                    starr[j+1] = temp;
                }
                else if ((starr[j] != null && starr[j+1] != null) && starr[j].rollNo > starr[j+1].rollNo) {
                    Student temp = starr[j];
                    starr[j] = starr[j+1];
                    starr[j+1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int loopflag = 0;
        int numStu = 0, numFac = 0;
        Student[] starr = new Student[5];
        Faculty[] facarr = new Faculty[2];

        String name, branch;
        int rollNo, empID;
        double cgpa;
        Faculty facultyAdvisor = null;
        int tempind = -1;

        do {
            System.out.println("1. Add Student");
            System.out.println("2. Delete Student");
            System.out.println("3. Add Faculty");
            System.out.println("4. Delete Faculty");
            System.out.println("5. Update Student Record");
            System.out.println("6. Get Student Details");
            System.out.println("7. Get Advisor Details");
            System.out.println("0. Exit");
            System.out.println("");
            System.out.print("Enter choice: ");
            loopflag = sc.nextInt();
            System.out.println("");

            switch (loopflag) {
                case 1:
                    if (numStu >= 5) {
                        System.out.println("max students reached");
                        break;
                    }
                    if (numFac <= 0) {
                        System.out.println("assign faculty first");
                        break;
                    }
                    System.out.print("advisor empID: ");
                    empID = sc.nextInt();
                    facultyAdvisor = null;
                    for (int i = 0; i < 2; i++) {
                        if (facarr[i] != null && facarr[i].empID == empID) {
                            facultyAdvisor = facarr[i];
                            break;
                        }
                    }
                    if (facultyAdvisor == null) {
                        System.out.println("invalid faculty advisor");
                        break;
                    }
                    numStu++;
                    System.out.print("name: ");
                    name = sc.next();
                    System.out.print("rollNo: ");
                    rollNo = sc.nextInt();
                    System.out.print("cgpa: ");
                    cgpa = sc.nextDouble();
                    System.out.print("branch: ");
                    branch = sc.next();
                    for (int i = 0; i < 5; i++) {
                        if (starr[i] == null) {
                            addStudent(starr, i, name, rollNo, cgpa, facultyAdvisor, branch);
                            break;
                        }
                    }
                    sort(starr);
                    break;
                case 2:
                    if (numStu <= 0) {
                        System.err.println("no students");
                        break;
                    }
                    System.out.print("rollNo: ");
                    rollNo = sc.nextInt();
                    tempind = -1;
                    for (int i = 0; i < 5; i++) {
                        if (starr[i] != null && starr[i].rollNo == rollNo) {
                            tempind = i;
                            break;
                        }
                    }
                    if (tempind == -1) {
                        System.out.println("student not found");
                        break;
                    }
                    numStu--;
                    deleteStudent(starr, tempind);
                    sort(starr);
                    break;
                case 3:
                    if (numFac >= 2) {
                        System.out.println("max faculty reached");
                        break;
                    }
                    numFac++;
                    System.out.print("name: ");
                    name = sc.next();
                    System.out.print("empID: ");
                    empID = sc.nextInt();
                    for (int i = 0; i < 2; i++) {
                        if (facarr[i] == null) {
                            addFaculty(facarr, i, name, empID);
                            break;
                        }
                    }
                    break;
                case 4:
                    if (numFac <= 0) {
                        System.err.println("no faculty");
                        break;
                    }
                    System.out.print("empID: ");
                    empID = sc.nextInt();
                    tempind = -1;
                    for (int i = 0; i < 2; i++) {
                        if (facarr[i] != null && facarr[i].empID == empID) {
                            tempind = i;
                            break;
                        }
                    }
                    if (tempind == -1) {
                        System.out.println("faculty not found");
                        break;
                    }
                    numFac--;
                    for (int i = 0; i < 5; i++) {
                        if (starr[i] != null && starr[i].facultyAdvisor.empID == empID) {
                            starr[i].facultyAdvisor = null;
                        }
                    }
                    deleteFaculty(facarr, tempind);
                    break;
                case 5:
                    if (numStu <= 0) {
                        System.err.println("no students");
                        break;
                    }
                    System.out.print("rollNo: ");
                    rollNo = sc.nextInt();
                    tempind = -1;
                    for (int i = 0; i < 5; i++) {
                        if (starr[i] != null && starr[i].rollNo == rollNo) {
                            tempind = i;
                            break;
                        }
                    }
                    if (tempind == -1) {
                        System.out.println("student not found");
                        break;
                    }
                    System.out.print("advisor empID: ");
                    empID = sc.nextInt();
                    facultyAdvisor = null;
                    for (int i = 0; i < 2; i++) {
                        if (facarr[i] != null && facarr[i].empID == empID) {
                            facultyAdvisor = facarr[i];
                            break;
                        }
                    }
                    if (facultyAdvisor == null) {
                        System.out.println("invalid faculty advisor");
                        break;
                    }
                    System.out.print("cgpa: ");
                    cgpa = sc.nextDouble();
                    System.out.print("branch: ");
                    branch = sc.next();
                    starr[tempind].updateStudentRecord(cgpa, facultyAdvisor, branch);
                    break;
                case 6:
                    if (numStu <= 0) {
                        System.err.println("no students");
                        break;
                    }
                    System.out.print("rollNo: ");
                    rollNo = sc.nextInt();
                    tempind = -1;
                    for (int i = 0; i < 5; i++) {
                        if (starr[i] != null && starr[i].rollNo == rollNo) {
                            tempind = i;
                            break;
                        }
                    }
                    if (tempind == -1) {
                        System.out.println("student not found");
                        break;
                    }
                    starr[tempind].getStudentDetails();
                    break;
                case 7:
                    if (numFac <= 0) {
                        System.err.println("no faculty");
                        break;
                    }
                    System.out.print("empID: ");
                    empID = sc.nextInt();
                    tempind = -1;
                    for (int i = 0; i < 2; i++) {
                        if (facarr[i] != null && facarr[i].empID == empID) {
                            tempind = i;
                            break;
                        }
                    }
                    if (tempind == -1) {
                        System.out.println("faculty not found");
                        break;
                    }
                    System.out.println(facarr[tempind].toStr());
                    break;
                default:
                    break;
            }

        } while (loopflag != 0);

        sc.close();
    }
}