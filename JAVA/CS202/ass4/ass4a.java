import java.util.*;

public class ass4a {
    public static class Account {
        int accountNumber, customerID;
        String accountType, serviceBranchIFSC, customerName;
        float minimumBalance, availableBalance;
        static int totalAccountCreated = 0;

        Account () {}

        void setDetails (int acno, String actype, String IFSC, float minbal, float availbal, int ID, String name) {
            accountNumber = acno;
            customerID = ID;
            accountType = actype;
            serviceBranchIFSC = IFSC;
            customerName = name;
            minimumBalance = minbal;
            availableBalance = availbal;
            totalAccountCreated += 1;
        }

        int getDetails(int acno) {
            if (accountNumber != acno) return -1;
            System.out.println("accNo: " + accountNumber);
            System.out.println("accType: " + accountType);
            System.out.println("branchIFSC: " + serviceBranchIFSC);
            System.out.println("minBal: " + minimumBalance);
            System.out.println("availBal: " + availableBalance);
            System.out.println("custID: " + customerID);
            System.out.println("custName: " + customerName);
            System.out.println("totalAccCreated: " + totalAccountCreated);
            return 1;
        }

        int updateDetails(int acno) {
            if (accountNumber != acno) return -1;
            Scanner sc = new Scanner(System.in);
            System.out.println("accType: ");
            accountType = sc.next();
            System.out.println("branchIFSC: ");
            serviceBranchIFSC = sc.next();
            System.out.println("minBal: ");
            minimumBalance = sc.nextFloat();
            System.out.println("availBal: ");
            availableBalance = sc.nextFloat();
            System.out.println("custName: ");
            customerName = sc.next();
            return 1;
        }

        float getBalance (int acno) {
            if (accountNumber != acno) return -1;
            return availableBalance;
        }

        int deposit (int acno, float money) {
            if (accountNumber != acno) return -1;
            availableBalance += money;
            return 1;
        }

        int withdraw (int acno, float money) {
            if (accountNumber != acno) return -1;
            if (availableBalance - minimumBalance >= money) availableBalance -= money;
            else System.out.println("Not enough balance!");
            return 1;
        }

        int totalAccount () {
            return totalAccountCreated;
        }


    }

    public static void compare (Account ac1, Account ac2) {
        if (ac1.availableBalance < ac2.availableBalance) ac2.getDetails(ac2.accountNumber);
        else ac1.getDetails(ac1.accountNumber);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int n; System.out.println("Enter number of accounts: ");
        n = sc.nextInt();
        Account[] accountArray = new Account[n];

        for (int i = 0; i < n; i++) {
            accountArray[i] = new Account();
            int accountNumber, customerID;
            String accountType, serviceBranchIFSC, customerName;
            float minimumBalance, availableBalance;
            System.out.println("accno: ");
            accountNumber = sc.nextInt();
            System.out.println("acctype: ");
            accountType = sc.next();
            System.out.println("branchIFSC: ");
            serviceBranchIFSC = sc.next();
            System.out.println("minBal: ");
            minimumBalance = sc.nextFloat();
            System.out.println("availBal: ");
            availableBalance = sc.nextFloat();
            System.out.println("custID: ");
            customerID = sc.nextInt();
            System.out.println("custName: ");
            customerName = sc.next();
            accountArray[i].setDetails(accountNumber, accountType, serviceBranchIFSC, minimumBalance, availableBalance, customerID, customerName);
        }

        int loopFlag = 0, flag, acno;
        float bal, money;
        do {
            System.out.println();
            System.out.println("1. Update Details");
            System.out.println("2. Get Details");
            System.out.println("3. Get Balance");
            System.out.println("4. Deposit");
            System.out.println("5. Withdraw");
            System.out.println("6. Total Accounts");
            System.out.println("7. Compare");
            System.out.println("0. Exit");
            loopFlag = sc.nextInt();
            System.out.println();

            switch (loopFlag) {
                case 1:
                    flag = -1;
                    System.out.println("acno: ");
                    acno = sc.nextInt();
                    for (int i = 0; i < n; i++) {
                        if (accountArray[i].updateDetails(acno) == 1) flag = 1;
                    }
                    if (flag == -1) System.out.println("Account not found!");
                    break;
                case 2:
                    flag = -1;
                    System.out.println("acno: ");
                    acno = sc.nextInt();
                    for (int i = 0; i < n; i++) {
                        if(accountArray[i].getDetails(acno) == 1) flag = 1;
                    }
                    if (flag == -1) System.out.println("Account not found!");
                    break;
                case 3:
                    bal = -1;
                    System.out.println("acno: ");
                    acno = sc.nextInt();
                    for (int i = 0; i < n; i++) {
                        float temp = accountArray[i].getBalance(acno); 
                        if(temp != -1) bal = temp;
                    }
                    if (bal == -1) System.out.println("Account not found!");
                    else System.out.println(bal);
                    break;
                case 4:
                    flag = -1;
                    System.out.println("acno: ");
                    acno = sc.nextInt();
                    System.out.println("money: ");
                    money = sc.nextFloat();
                    for (int i = 0; i < n; i++) {
                        if(accountArray[i].deposit(acno, money) == 1) flag = 1;
                    }
                    if (flag == -1) System.out.println("Account not found!");
                    break;
                case 5:
                    flag = -1;
                    System.out.println("acno: ");
                    acno = sc.nextInt();
                    System.out.println("money: ");
                    money = sc.nextFloat();
                    for (int i = 0; i < n; i++) {
                        if(accountArray[i].withdraw(acno, money) == 1) flag = 1;
                    }
                    if (flag == -1) System.out.println("Account not found!");
                    break;
                case 6:
                    System.out.println("total accounts: " + accountArray[0].totalAccount());
                    break;
                case 7:
                    int ac1, ac2; System.out.println("Enter accs to compare: ");
                    ac1 = sc.nextInt(); ac2 = sc.nextInt();
                    int ind1 = -1, ind2 = -1;
                    for (int i = 0; i < n; i++) {
                        if (accountArray[i].accountNumber == ac1) ind1 = i;
                        else if (accountArray[i].accountNumber == ac2) ind2 = i;
                    }
                    if (ac1 == -1 || ac2 == -1) System.out.println("Accounts not found!");
                    else {
                        compare(accountArray[ind1], accountArray[ind2]);
                    }
                    break;
                default:
                    break;
            }

        } while (loopFlag != 0);

        sc.close();
    }
}