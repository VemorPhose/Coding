import java.util.*;

public class ass2b {	
	public static class Students {
		
		public int roll_no;
		public String name;
		public String branch;
		public double CGPA;
		
		public Students () {
			// this.roll_no = 0;
			this.name = new String();
			this.branch = new String();
			// this.CGPA = 0.0f;
		}
		public void set () {
			System.out.println("enter roll no, cgpa, name, branch: ");
			Scanner sc = new Scanner(System.in);
			this.roll_no = sc.nextInt();
			this.CGPA = sc.nextFloat();
			this.name = sc.next();
			this.branch = sc.next();
			// sc.close();
		}
		public void branch_change () {
			if (CGPA > 9) {
				System.out.println("True");
				this.branch = "CSE";
			}
			else System.out.println("False");
		}
		public void print_student_details () {
			System.out.println("roll no: " + roll_no);
			System.out.println("name: " + name);
			System.out.println("branch: " + branch);
			System.out.println("CGPA: " + CGPA);
		}
	}

	public static void main (String[] args) {
		Students s1 = new Students();
		Students s2 = new Students();
		System.out.println("enter values for s1: ");
		s1.set();
		System.out.println("enter values for s2: ");
		s2.set();
		System.out.println("printing attributes of s1 and s2: ");
		s1.print_student_details();
		s2.print_student_details();
		System.out.println("checking branch change for s1 and s2: ");
		s1.branch_change();
		s2.branch_change();
		System.out.println("printing attributes of s1 and s2 after branch_change: ");
		s1.print_student_details();
		s2.print_student_details();
	}
}	