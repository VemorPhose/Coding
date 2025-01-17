import java.util.*;

public class test {

    public static class Patient {
        int patientId, appointmentMonth;
        String name, appointmentType;

        public Patient(int patientId, String name) {
            this.appointmentMonth = 0;
            this.patientId = patientId;
            this.name = name;
        }

        void bookAppointment(String type, int appointmentMonth, ArrayList<Doctor> doctors) {
            boolean validType = false;
            for (Doctor doctor : doctors) {
                if (doctor.specialization.equals(type)) {
                    validType = true;
                    if (doctor.availableSlots == 0) {
                        System.out.println("No available slots for " + type + " appointments.");
                        break;
                    }
                    this.appointmentType = type;
                    this.appointmentMonth = appointmentMonth;
                    doctor.availableSlots -= 1;
                    System.out.println("Appointment with " + doctor.specialization + " doctor booked. " +
                            doctor.availableSlots + " slots remaining.");
                    break;
                }
            }
            if (!validType) {
                System.out.println("Specialization " + type + " not found.");
            }
        }

        void cancelAppointment(String type, int cancelMonth, ArrayList<Doctor> doctors) {
            boolean validType = false;
            for (Doctor doctor : doctors) {
                if (doctor.specialization.equals(type)) {
                    validType = true;
                    this.appointmentType = null;
                    doctor.availableSlots += 1;
                    System.out.println("Appointment with " + doctor.specialization + " doctor canceled. " +
                            doctor.availableSlots + " slots remaining.");
                    calculateFee(cancelMonth);
                    break;
                }
            }
            if (!validType) {
                System.out.println("Specialization " + type + " not found.");
            }
        }

        void calculateFee(int cancelMonth) {}
    }

    public static class InvalidPatientIDException extends Exception {
        public InvalidPatientIDException(String message) {
            super(message);
        }
    }

    public static class Inpatient extends Patient {
        String wardNumber;

        public Inpatient(int patientId, String name, String wardNumber) {
            super(patientId, name);
            this.wardNumber = wardNumber;
            try {
                validatePatientId(patientId);
            } catch (InvalidPatientIDException e) {
                System.out.println("Invalid patient ID: " + patientId + ", should be even number");
                this.patientId = -1;
            }
        }

        void validatePatientId(int patientId) throws InvalidPatientIDException {
            if (patientId % 2 != 0) {
                throw new InvalidPatientIDException("Invalid patient ID: " + patientId + ", should be even number");
            }
        }

        void calculateFee(int cancelMonth) {
            if (cancelMonth - this.appointmentMonth > 3) {
                System.out.println("Cancellation fee is Rs." + ((cancelMonth - this.appointmentMonth) * 1000));
            } else {
                System.out.println("No cancellation fee.");
            }
        }
    }

    public static class Outpatient extends Patient {
        String clinicNumber;

        public Outpatient(int patientId, String name, String clinicNumber) {
            super(patientId, name);
            this.clinicNumber = clinicNumber;
            try {
                validatePatientId(patientId);
            } catch (InvalidPatientIDException e) {
                System.out.println("Invalid patient ID: " + patientId + ", should be odd number");
                this.patientId = -1;
            }
        }

        void validatePatientId(int patientId) throws InvalidPatientIDException {
            if (patientId % 2 != 1) {
                throw new InvalidPatientIDException("Invalid patient ID: " + patientId + ", should be odd number");
            }
        }

        void calculateFee(int cancelMonth) {
            if (cancelMonth - this.appointmentMonth > 2) {
                System.out.println("Cancellation fee is Rs." + ((cancelMonth - this.appointmentMonth) * 500));
            } else {
                System.out.println("No cancellation fee.");
            }
        }
    }

    public static class Doctor {
        String specialization;
        int availableSlots;

        public Doctor(String specialization, int availableSlots) {
            this.specialization = specialization;
            this.availableSlots = availableSlots;
        }
    }

    public static void main(String[] args) {
        ArrayList<Person> persons = new ArrayList<Person>();
        ArrayList<Medicine> medicines = new ArrayList<Medicine>();

        medicines.add(new Medicine("A", "Analgesic", 10));
        medicines.add(new Medicine("B", "Antibiotic", 8));
        medicines.add(new Medicine("C", "Analgesic", 5));
        medicines.add(new Medicine("D", "Anti-inflammatory", 4));
        medicines.add(new Medicine("E", "Anti-inflammatory", 4));

        persons.add(new Patient(2, "Alice", "P001"));
        persons.add(new Patient(4, "Bob", "P002"));
        persons.add(new Doctor(1, "Dr. Smith", "D101"));
        persons.add(new Doctor(3, "Dr. Johnson", "D102"));

        // Prescribing medicines and calculating charges as per test cases
        for (Person person : persons) {
            if (person instanceof Patient) {
                Patient patient = (Patient) person;
                patient.prescribeMedicine("Paracetamol", medicines);
                patient.calculateCharge(3); // Assuming 3 days as visit duration
            } else if (person instanceof Doctor) {
                Doctor doctor = (Doctor) person;
                doctor.prescribeMedicine("Amoxicillin", medicines);
                doctor.calculateCharge(5); // Assuming 5 hours as visit duration
            }
            System.out.println();
        }
    }
}
