import java.util.*;

public class ass3b {
    public static class Book {
        int bookId, yearOfPublication, numberOfAvailableCopies, totalCopies;
        String bookTitle, authorName, publisherName;
        
        Book() {
            this.bookId = 0;
            this.yearOfPublication = 0;
            this.numberOfAvailableCopies = 0;
            this.totalCopies = 0;
            this.bookTitle = "";
            this.authorName = "";
            this.publisherName = "";
        }
        Book(int numCopies) {
            this.bookId = 0;
            this.yearOfPublication = 0;
            this.numberOfAvailableCopies = 0;
            this.totalCopies = numCopies;
            this.bookTitle = "";
            this.authorName = "";
            this.publisherName = "";
        }

        void setDetails() {
            this.bookId = 0;
            this.yearOfPublication = 0;
            this.numberOfAvailableCopies = 0;
            this.totalCopies = 0;
            this.bookTitle = "";
            this.authorName = "";
            this.publisherName = "";
        }
        void setDetails(int id, String title, int year, String author, String publisher, int available, int total) {
            this.bookId = id;
            this.yearOfPublication = year;
            this.numberOfAvailableCopies = available;
            this.totalCopies = total;
            this.bookTitle = title;
            this.authorName = author;
            this.publisherName = publisher;
        }

        int getDetails(int id) {
            if (this.bookId != id) return 0;
            System.out.println("bookId: " + this.bookId);
            System.out.println("bookTitle: " + this.bookTitle);
            System.out.println("yearOfPublication: " + this.yearOfPublication);
            System.out.println("authorName: " + this.authorName);
            System.out.println("publisherName: " + this.publisherName);
            System.out.println("numberOfAvailableCopies: " + this.numberOfAvailableCopies);
            System.out.println("totalCopies: " + this.totalCopies);
            return 1;
        }

        int issueBook(int id) {
            if (this.bookId != id) return 0;
            if (this.numberOfAvailableCopies == 0) return -1;
            System.out.println("Issued 1 copy of bookId: " + this.bookId);
            this.numberOfAvailableCopies -= 1;
            return 1;
        }

        int returnBook(int id) {
            if (this.bookId != id) return 0;
            if (this.numberOfAvailableCopies == totalCopies)
                this.totalCopies += 1;
            System.out.println("Returned 1 copy of bookId: " + this.bookId);
            this.numberOfAvailableCopies += 1;
            return 1;
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Book[] bookArray = new Book[5];

        int bookId, yearOfPublication, numberOfAvailableCopies, totalCopies;
        String bookTitle, authorName, publisherName;

        for (int i = 0; i < 5; i++) {
            System.out.println("Enter details of book " + (i+1));
            System.out.println("bookId: ");
            bookId = sc.nextInt();
            System.out.println("bookTitle: ");
            bookTitle = sc.next();
            System.out.println("yearOfPublication: ");
            yearOfPublication = sc.nextInt();
            System.out.println("authorName: ");
            authorName = sc.next();
            System.out.println("publisherName: ");
            publisherName = sc.next();
            System.out.println("numberOfAvailableCopies: ");
            numberOfAvailableCopies = sc.nextInt();
            System.out.println("totalCopies: ");
            totalCopies = sc.nextInt();
            System.out.println();
            bookArray[i] = new Book();
            bookArray[i].setDetails(bookId, bookTitle, yearOfPublication, authorName, publisherName, numberOfAvailableCopies, totalCopies);
        }

        int flag = 1, id;
        do {
            System.out.println("1. Set Details");
            System.out.println("2. Get Details");
            System.out.println("3. Issue Book");
            System.out.println("4. Return Book");
            System.out.println("0. Exit");
            System.out.println("Enter choice: ");
            flag = sc.nextInt();
            System.out.println();

            switch (flag) {
                case 1:
                    System.out.println("Enter details of book");
                    System.out.println("bookId: ");
                    bookId = sc.nextInt();
                    System.out.println("bookTitle: ");
                    bookTitle = sc.next();
                    System.out.println("yearOfPublication: ");
                    yearOfPublication = sc.nextInt();
                    System.out.println("authorName: ");
                    authorName = sc.next();
                    System.out.println("publisherName: ");
                    publisherName = sc.next();
                    System.out.println("numberOfAvailableCopies: ");
                    numberOfAvailableCopies = sc.nextInt();
                    System.out.println("totalCopies: ");
                    totalCopies = sc.nextInt();
                    System.out.println();
                    int f = 0;
                    for (int i = 0; i < 5; i++) {
                        if (bookArray[i].bookId == bookId) {
                            bookArray[i].setDetails(bookId, bookTitle, yearOfPublication, authorName, publisherName, numberOfAvailableCopies, totalCopies);
                            f = 1;
                        }
                    }
                    if (f == 0) System.out.println("bookId not found");
                    else System.out.println("successfully set book details with given id");
                    break;
                case 2:
                    System.out.println("Enter id: ");
                    id = sc.nextInt();
                    for (int i = 0; i < 5; i++) {
                        bookArray[i].getDetails(id);
                    }
                    break;
                case 3:
                    System.out.println("Enter id: ");
                    id = sc.nextInt();
                    for (int i = 0; i < 5; i++) {
                        bookArray[i].issueBook(id);
                    }
                    break;
                case 4:
                    System.out.println("Enter id: ");
                    id = sc.nextInt();
                    for (int i = 0; i < 5; i++) {
                        bookArray[i].returnBook(id);
                    }
                    break;
                default:
                    break;
            }
        } while (flag != 0);

        sc.close();
    }
}