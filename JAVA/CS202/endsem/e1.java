import java.util.*;

public class e1 {
    abstract public static class User {
        int userId, issueMonthNum;
        String name, borrowedBook, bookType;

        public User(int userId, String name) {
            this.issueMonthNum = 0;
            this.userId = userId;
            this.name = name;
        }

        void issueBook(String title, int issueMonthNum, ArrayList<Book> books) {
            Boolean vaildBook = false;
            for (int i = 0; i < books.size(); i++) {
                if (books.get(i).title.equals(title)) {
                    vaildBook = true;
                    if (books.get(i).availableCopies == 0) {
                        System.out.println("Book " + title + " is out of stock.");
                        break;
                    }
                    this.bookType = books.get(i).type;
                    this.borrowedBook = title;
                    this.issueMonthNum = issueMonthNum;
                    books.get(i).availableCopies -= 1;
                    System.out.println("Book " + title + " of type " + books.get(i).type + " now has " + books.get(i).availableCopies + " copies left.");
                    break;
                }
            }
            if (vaildBook == false) {
                System.out.println("Book " + title + " not found in library.");
            }
        }

        void returnBook(String title, int returnMonthNum, ArrayList<Book> books) {
            Boolean vaildBook = false;
            for (int i = 0; i < books.size(); i++) {
                if (books.get(i).title.equals(title)) {
                    vaildBook = true;
                    this.borrowedBook = null;
                    this.bookType = null;
                    books.get(i).availableCopies += 1;
                    System.out.println("Book " + title + " of type " + books.get(i).type + " now has " + books.get(i).availableCopies + " copies left.");
                    calculateFine(returnMonthNum);
                    break;
                }
            }
            if (vaildBook == false) {
                System.out.println("Book " + title + " not found in database.");
            }
        }

        void calculateFine(int returnMonthNum) {}
    }

    public static class InvalidUserIDException extends Exception {
        public InvalidUserIDException(String message) {
            super(message);
        }
    }

    public static class StudentUser extends User {
        String studentRoll;

        public StudentUser(int userId, String name, String studentRoll) {
            super(userId, name);
            this.studentRoll = studentRoll;
            try {
                validateUserId(userId);
            } catch (InvalidUserIDException e) {
                System.out.println("Invalid user ID: " + userId + ", should be even number");
                this.userId = -1;
            }
        }

        void validateUserId(int userId) throws InvalidUserIDException {
            if (userId%2 != 0) {
                throw new InvalidUserIDException("Invalid user ID: " + userId + ", should be even number");
            }
        }

        void calculateFine(int returnMonthNum) {
            if (returnMonthNum - this.issueMonthNum > 3) {
                System.out.println("Fine amount is Rs." + ((returnMonthNum - this.issueMonthNum) * 2000));
            }
            else System.out.println("No fine.");
        }
    }

    public static class FacultyUser extends User {
        String empId;

        public FacultyUser(int userId, String name, String empId) {
            super(userId, name);
            this.empId = empId;
            try {
                validateUserId(userId);
            } catch (InvalidUserIDException e) {
                System.out.println("Invalid user ID: " + userId + ", should be odd number");
                this.userId = -1;
            }
        }

        void validateUserId(int userId) throws InvalidUserIDException {
            if (userId%2 != 1) {
                throw new InvalidUserIDException("Invalid user ID: " + userId + ", should be odd number");
            }
        }

        void calculateFine(int returnMonthNum) {
            if (returnMonthNum - this.issueMonthNum > 5) {
                System.out.println("Fine amount is Rs." + ((returnMonthNum - this.issueMonthNum) * 5000));
            }
            else System.out.println("No fine.");
        }
    }

    public static class Book {
        String title, type;
        int availableCopies;

        public Book(String title, String type, int availableCopies) {
            this.title = title;
            this.type = type;
            this.availableCopies = availableCopies;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        ArrayList<User> users = new ArrayList<User>();
        ArrayList<Book> books = new ArrayList<Book>();

        books.add(new Book("Computer Organization", "Text", 5));
        books.add(new Book("Gemba Kaizen", "Non-Text", 5));
        books.add(new Book("Let us C", "Text", 5));
        books.add(new Book("Operating Systems", "Text", 5));
        books.add(new Book("The Alchemist", "Non-Text", 5));

        users.add(new StudentUser(2, "Pratap", "154"));
        users.add(new StudentUser(4, "Prasoon", "153"));
        users.add(new StudentUser(6, "Tanmay", "126"));
        users.add(new StudentUser(8, "Pranita", "151"));
        users.add(new StudentUser(10, "Shourya", "207"));

        users.add(new FacultyUser(1, "Kaustuv Nag", "123"));
        users.add(new FacultyUser(3, "Arijit Nath", "234"));
        users.add(new FacultyUser(5, "Pawan Mishra", "345"));
        users.add(new FacultyUser(7, "Masihuddin", "456"));
        users.add(new FacultyUser(9, "Ferdous Ahmed", "567"));

        int flag = 0;
        int userId, issueMonthNum, returnMonthNum;
        String name, roll, bookName, buf;
        StudentUser student;
        FacultyUser faculty;
        User user;
        int userUpdatedIndex = -1;
        do {
            System.out.println("0. Exit");
            System.out.println("1. Add Student User");
            System.out.println("2. Add Faculty User");
            System.out.println("3. Issue Book");
            System.out.println("4. Return Book");
            System.out.println("5. Display all");
            System.out.println();
            System.out.print("Enter choice: ");
            flag = sc.nextInt();
            System.out.println();

            switch (flag) {
                case 1:
                    System.out.println("Enter userId, name, roll: ");
                    userId = sc.nextInt();
                    sc.nextLine();
                    name = sc.nextLine();
                    roll = sc.nextLine();
                    users.add(new StudentUser(userId, name, roll));
                    user = users.get(users.size() - 1);
                    student = (StudentUser)user;
                    System.out.println("userId: " + student.userId);
                    System.out.println("name: " + student.name);
                    System.out.println("roll no: " + student.studentRoll);
                    break;
                case 2:
                    System.out.println("Enter userId, name, empId: ");
                    userId = sc.nextInt();
                    sc.nextLine();
                    name = sc.nextLine();
                    roll = sc.nextLine();
                    users.add(new FacultyUser(userId, name, roll));
                    user = users.get(users.size() - 1);
                    faculty = (FacultyUser)user;
                    System.out.println("userId: " + faculty.userId);
                    System.out.println("name: " + faculty.name);
                    System.out.println("empId: " + faculty.empId);
                    break;
                case 3:
                    System.out.println("Enter userId, issueMonthNum, book name: ");
                    userId = sc.nextInt();
                    issueMonthNum = sc.nextInt();
                    sc.nextLine();
                    bookName = sc.nextLine();
                    for (int i = 0; i < users.size(); i++) {
                        if (users.get(i).userId == userId) {
                            userUpdatedIndex = i;
                            break;
                        }
                    }
                    if (userUpdatedIndex == -1) {
                        System.out.println("userId: " + userId + " not found.");
                        break;
                    }
                    users.get(userUpdatedIndex).issueBook(bookName, issueMonthNum, books);
                    user = users.get(userUpdatedIndex);
                    userUpdatedIndex = -1;
                    System.out.println("Updated User records:");
                    System.out.println("userId: " + user.userId);
                    System.out.println("name: " + user.name);
                    System.out.println("borrowed book: " + user.borrowedBook);
                    System.out.println("book type: " + user.bookType);
                    System.out.println("issue month num: " + user.issueMonthNum);
                    break;
                case 4:
                    System.out.println("Enter userId, returnMonthNum, book name: ");
                    userId = sc.nextInt();
                    returnMonthNum = sc.nextInt();
                    sc.nextLine();
                    bookName = sc.nextLine();
                    for (int i = 0; i < users.size(); i++) {
                        if (users.get(i).userId == userId) {
                            userUpdatedIndex = i;
                            break;
                        }
                    }
                    if (userUpdatedIndex == -1) {
                        System.out.println("userId: " + userId + " not found.");
                        break;
                    }
                    users.get(userUpdatedIndex).returnBook(bookName, returnMonthNum, books);
                    user = users.get(userUpdatedIndex);
                    userUpdatedIndex = -1;
                    System.out.println("Updated User records:");
                    System.out.println("userId: " + user.userId);
                    System.out.println("name: " + user.name);
                    System.out.println("borrowed book: " + user.borrowedBook);
                    System.out.println("book type: " + user.bookType);
                    System.out.println("issue month num: " + user.issueMonthNum);
                    break;
                case 5:
                    System.out.println("Users:\n");
                    for (User x: users) {
                        System.out.println("userId: " + x.userId);
                        System.out.println("name: " + x.name);
                        System.out.println();
                    }
                    System.out.println("Books:\n");
                    for (Book x: books) {
                        System.out.println("title: " + x.title);
                        System.out.println("type: " + x.type);
                        System.out.println("copies: " + x.availableCopies);
                        System.out.println();
                    }
                    break;
                default:
                    break;
            }
        } while (flag != 0);

        sc.close();
    }
}