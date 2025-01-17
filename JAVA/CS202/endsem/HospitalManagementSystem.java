import java.util.*;

public class HospitalManagementSystem {
    abstract class Person {
        public int personId;
        public String name;
    
        public Person(int personId, String name) {
            this.personId = personId;
            this.name = name;
        }
    }
    
    class Patient extends Person {
        public String ailmentType;
        public boolean isInsured;
        public String medicineName;
        public int quantity;
    
        public Patient(int personId, String name, String ailmentType, boolean isInsured, String medicineName, int quantity) {
            super(personId, name);
            this.ailmentType = ailmentType;
            this.isInsured = isInsured;
            this.medicineName = medicineName;
            this.quantity = quantity;
        }

        void displayInfo() {
            System.out.println("personId: " + personId);
            System.out.println("name: " + name);
            System.out.println("ailmentType: " + ailmentType);
            System.out.println("medicineName: " + medicineName);
            System.out.println("quantity: " + quantity);
            System.out.println("isInsured: " + isInsured);
        }
    
        public void prescribeMedicine(String medicineName, int quantity, ArrayList<Medicine> medicines) throws OutOfStockException {
            for (Medicine medicine : medicines) {
                if (medicine.getMedicineName().equals(medicineName)) {
                    try {
                        validateMedicine(medicine, quantity);
                        medicine.reduceStock(quantity);
                        this.medicineName = medicineName;
                        this.quantity = quantity;
                        System.out.println("Medicine prescribed successfully.");
                    } catch (OutOfStockException e) {
                         System.out.println("Insufficient stock for " + medicineName);
                    }
                    return;
                }
            }
            System.out.println("Medicine not found.");
        }
    
        public void validateMedicine(Medicine medicine, int quantity) throws OutOfStockException {
            if (medicine.getStockQuantity() >= quantity) {
                throw new OutOfStockException("Insufficient stock for " + medicineName);
            }
        }
    
        public void calculateCharges(int daysAdmitted) {
            int baseCharge = 500 * daysAdmitted;
            double discount = isInsured ? 0.1 : 0.0;
            double totalCharge = baseCharge * (1 - discount);
            System.out.println("Total hospital charges for " + name + ": " + totalCharge);
        }
    }
    
    class Doctor extends Person {
        public String specialization;
        public int patientsAssigned;
    
        public Doctor(int personId, String name, String specialization, int patientsAssigned) {
            super(personId, name);
            this.specialization = specialization;
            this.patientsAssigned = patientsAssigned;
        }
    
        public void calculateSalary(int daysWorked) {
            int baseSalary = 1000 * daysWorked;
            int bonus = patientsAssigned > 3 ? 2000 : 0;
            int totalSalary = baseSalary + bonus;
            System.out.println("Total salary for " + name + ": " + totalSalary);
        }

        void displayInfo() {
            System.out.println("personId: " + personId);
            System.out.println("name: " + name);
            System.out.println("specialization: " + specialization);
            System.out.println("patientAssigned: " + patientsAssigned);
        }
    }
    
    class Medicine {
        public String medicineName;
        public String category;
        public int stockQuantity;
    
        public Medicine(String medicineName, String category, int stockQuantity) {
            this.medicineName = medicineName;
            this.category = category;
            this.stockQuantity = stockQuantity;
        }
    
        public String getMedicineName() {
            return medicineName;
        }
    
        public int getStockQuantity() {
            return stockQuantity;
        }
    
        public void reduceStock(int quantity) {
            this.stockQuantity -= quantity;
        }

        void displayInfo() {
            System.out.println("medicineName: " + medicineName);
            System.out.println("category: " + category);
            System.out.println("stock: " + stockQuantity);
        }
    }
    
    class OutOfStockException extends Exception {
        public OutOfStockException(String message) {
            super(message);
        }
    }

    public static void main(String[] args) {
        ArrayList<Person> persons = new ArrayList<>();
        ArrayList<Medicine> medicines = new ArrayList<>();
    
        // 1
        persons.add(new Patient(1, "Alice", "P001"));
        persons.add(new Patient(2, "Bob", "P002"));
        persons.add(new Patient(3, "Charlie", "P003"));
        persons.add(new Doctor(4, "Dr. Smith", "D101"));
        persons.add(new Doctor(5, "Dr. Gary", "D102"));
    
        medicines.add(new Medicine("Paracetamol", "Painkiller", 10));
        medicines.add(new Medicine("Ibuprofen", "Painkiller", 8));
        medicines.add(new Medicine("Amoxicillin", "Antibiotic", 5));
        medicines.add(new Medicine("Azithromycin", "Antibiotic", 4));
    
        System.out.println("All Patient Records:");
        for (Person person : persons) {
            if (person instanceof Patient) {
                Patient patient = (Patient) person;
                patient.displayInfo();
            }
        }
    
        System.out.println("\nAll Doctor Records:");
        for (Person person : persons) {
            if (person instanceof Doctor) {
                Doctor doctor = (Doctor) person;
                doctor.displayInfo();
            }
        }
    
        System.out.println("\nAll Medicine Records with available stock:");
        for (Medicine medicine : medicines) {
            if (medicine.getStockQuantity() > 0) {
                medicine.displayInfo();
            }
        }
    
        // 2
        Patient newPatient = new Patient(6, "Daisy", "P004");
        persons.add(newPatient);
        System.out.println("\nNewly added Patient record:");
        newPatient.displayInfo();
    
        // 3
        Patient selectedPatient = (Patient) persons.get(0);
        String medicineName = "Paracetamol";
        int quantity = 2;
        selectedPatient.prescribeMedicine(medicineName, quantity, medicines);
        System.out.println("\nUpdated Patient and Medicine Records after Prescription:");
        selectedPatient.displayInfo();
        for (Medicine medicine : medicines) {
            medicine.displayInfo();
        }
    
        // 4
        int daysAdmitted = 5; // Example input for Patient charges
        System.out.println("\nHospital Charges for Patient:");
        selectedPatient.calculateCharges(daysAdmitted);
    
        Doctor selectedDoctor = (Doctor) persons.get(3); // Example doctor (Dr. Smith)
        int daysWorked = 20; // Example input for Doctor salary
        System.out.println("\nSalary for Doctor:");
        selectedDoctor.calculateSalary(daysWorked);
    }
    
}
