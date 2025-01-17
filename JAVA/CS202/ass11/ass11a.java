import java.util.*;

public class ass11a {
    public static class Person {
        String fname, lname, PAN;
        int PIN;

        public Person(String fname, String lname, String PAN, int PIN) throws InvalidPINException {
            this.fname = fname;
            this.lname = lname;
            this.PAN = PAN;
            this.PIN = PIN;
            try {
                validatePIN(PIN);
            } catch (InvalidPINException e) {
                System.out.println("Invalid PIN: PIN must be a 6-digit number.");
            }
        }

        private void validatePIN(int PIN) throws InvalidPINException {
            if (PIN <= 100000 || PIN >= 999999) {
                throw new InvalidPINException("Invalid PIN: PIN must be a 6-digit number.");
            }
        }
    }

    public static class Student extends Person {
        String emailID, rollNo;

        public Student(String fname, String lname, String PAN, int PIN, String emailID, String rollNo) 
                throws InvalidPINException, InvalidEmailException, InvalidRollNumberException {
            super(fname, lname, PAN, PIN);
            this.emailID = emailID;
            this.rollNo = rollNo;
            try {
                validateEmail(emailID);
            } catch (InvalidEmailException e) {
                System.out.println("Invalid Email ID: Must be alphanumeric, contain @ followed by a domain, and have a special character before @.");
            }
            try {
                validateRollNo(rollNo);
            } catch (InvalidRollNumberException e) {
                System.out.println("Invalid Roll Number: Must start with 'stud' followed by 5 digits.");
            }
        }

        private void validateEmail(String email) throws InvalidEmailException{
            if (!email.matches("^[0-9a-zA-Z]*[@!#$&*]+[0-9a-zA-Z]*[@][0-9a-zA-Z]+([.][0-9a-zA-Z]+)+$")) {
                throw new InvalidEmailException("Invalid Email ID: Must be alphanumeric, contain @ followed by a domain, and have a special character before @.");
            }
        }

        private void validateRollNo(String rollNo) throws InvalidRollNumberException {
            if (!rollNo.matches("stud\\d{5}")) {
                throw new InvalidRollNumberException("Invalid Roll Number: Must start with 'stud' followed by 5 digits.");
            }
        }
    }

    public static class Employee extends Person {
        String emailID, employeeID;

        public Employee(String fname, String lname, String PAN, int PIN, String emailID, String employeeID) 
                throws InvalidPINException, InvalidEmailException, InvalidEmployeeIDException {
            super(fname, lname, PAN, PIN);
            this.emailID = emailID;
            this.employeeID = employeeID;
            try {
                validateEmail(emailID);
            } catch (InvalidEmailException e) {
                System.out.println("Invalid Email ID: Must be alphanumeric, contain @ followed by a domain, and have a special character before @.");
            }
            try {
                validateEmployeeID(employeeID);
            } catch (InvalidEmployeeIDException e) {
                System.out.println("Invalid Employee ID: Must start with 'emp' followed by 3 digits.");
            }
        }

        private void validateEmail(String email) throws InvalidEmailException{
            if (!email.matches("^[0-9a-zA-Z]*[@!#$&*]+[0-9a-zA-Z]*[@][0-9a-zA-Z]*[.]+[0-9a-zA-Z.@!#$&*]+$")) {
                throw new InvalidEmailException("Invalid Email ID: Must be alphanumeric, contain @ followed by a domain, and have a special character before @.");
            }
        }

        private void validateEmployeeID(String employeeID) throws InvalidEmployeeIDException {
            if (!employeeID.matches("emp\\d{3}")) {
                throw new InvalidEmployeeIDException("Invalid Employee ID: Must start with 'emp' followed by 3 digits.");
            }
        }
    }

    public static class InvalidPINException extends Exception {
        public InvalidPINException(String message) {
            super(message);
        }
    }

    public static class InvalidEmailException extends Exception {
        public InvalidEmailException(String message) {
            super(message);
        }
    }

    public static class InvalidRollNumberException extends Exception {
        public InvalidRollNumberException(String message) {
            super(message);
        }
    }

    public static class InvalidEmployeeIDException extends Exception {
        public InvalidEmployeeIDException(String message) {
            super(message);
        }
    }

    public static void main(String[] args) {
        // try {
        //     Student student = new Student("John", "Doe", "ABC123456", 123456, "john#doe@example.com", "stud12345");
        // } catch (InvalidEmailException e) {
        //     System.out.println("Invalid email");
        // } catch (InvalidPINException e) {
        //     System.out.println("Invalid PIN");
        // } catch (InvalidRollNumberException e) {
        //     System.out.println("Invalid roll number");
        // }

        // try {
        //     Employee employee = new Employee("Jane", "Smith", "DEF789101", 789101, "janes&mith@example.com", "emp789");
        // } catch (InvalidEmailException e) {
        //     System.out.println("Invalid email");
        // } catch (InvalidPINException e) {
        //     System.out.println("Invalid PIN");
        // } catch (InvalidEmployeeIDException e) {
        //     System.out.println("Invalid employee ID");
        // }

        try {
            Student student2 = new Student("John", "Doe", "ABC123456", 123456, "pratapaditya@chander23b@iiitgin", "stud12345");
        } catch (InvalidEmailException e) {
            System.out.println("Invalid email");
        } catch (InvalidPINException e) {
            System.out.println("Invalid PIN");
        } catch (InvalidRollNumberException e) {
            System.out.println("Invalid roll number");
        }
    }
}