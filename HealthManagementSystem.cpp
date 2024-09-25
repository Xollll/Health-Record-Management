//List of Header
#include <iostream> //Input/Output 
#include <fstream> //File
#include <list> //linked list c++ library
#include <queue> //queue c++ library
#include <algorithm> //Operation on sequence purpose
#include <sstream> //sstream (converting between strings and other data types) 


using namespace std; //For using any input/output structure like cout without need to put std :: cout

// Structure for patient records
struct Patient {
    string name;
    int id=0;
    string gender, DOB, address, phone, medicalDATE, medicalDETAILS;
    
   
    bool operator>(const Patient& next) const { //compare patients based on ID for sorting
        return id > next.id;
    }
};

// Structure for Appointment
struct Appointment {
    string patientName;
    int patientID = 0;
    string date, time;
};



//prototype (Global = can access anywhere)
void savePatientRecordsToFile();
void saveAppointmentsToFile();
void deletePatientRecord();
void editPatientRecord();



// Linked list for patient records & appointment (using standard c++ library = more shorter)
list<Patient> patientRecords; //Patient = variable for struct
list<Appointment> appointmentList; //Appointment = variable for struct

// Queue for appointment schedule (FIFO)
queue<Appointment> appointmentQueue;


// Priority queue for emergency cases (Priority Queue)
priority_queue<Patient, vector<Patient>, greater<Patient>> emergencyQueue;



//Function to receive input patient data
void addPatientRecord() {
    Patient newPatient;

    cout << endl;
    cout << "\t\t----------------------------- PLEASE INPUT PATIENT INFORMATION HERE ----------------------------- " << endl << endl;
    cout << endl;

    cin.ignore(); // Clear the newline character left in the buffer
    cout << " Enter patient name (first middle last): ";
    getline(cin, newPatient.name);

    cout << endl;

    cout << " Enter patient ID ( EXAMPLE - 0001): ";
    cin >> newPatient.id;

    cout << endl;

    cout << " Enter patient gender (M/F): ";
    cin >> newPatient.gender;

    cout << endl;

    cout << " Enter patient D.O.B (Date Of Birth) EXAMPLE - 1/1/2022 : ";
    cin >> newPatient.DOB;

    cout << endl;

    cin.ignore(); // Clear the newline character left in the buffer
    cout << " Enter patient address: ";
    getline(cin, newPatient.address);

    cout << endl;

    cout << " Enter patient phone number (000-0000000): ";
    cin >> newPatient.phone;

    cout << endl <<endl;

    cout << "\t\t----------------------------- PLEASE INPUT MEDICAL RECORD HERE ----------------------------- " << endl << endl;

    cout << " Enter medical date: ";
    cin >> newPatient.medicalDATE;

    cout << " Enter medical details: ";
    cin >> newPatient.medicalDETAILS;

    cout << endl << endl;


    // Add the new patient to the linked list
    patientRecords.push_back(newPatient);
    cout << " *********************************" << endl;
    cout << " Patient record added successfully" << endl;
    cout << " *********************************" << endl <<endl;

    // Prompt user to save the data that already to insert
    char saveChoice;
    cout << " Do you want to save the patient records? (y/n): ";
    cin >> saveChoice;
   
    if (saveChoice == 'y' || saveChoice == 'Y') {
        savePatientRecordsToFile(); //go to function save records
    }
}

//Function to Add new appointment
void scheduleAppointment() {
    Appointment newAppointment;

    cout << endl;
    cout << "\t\t----------------------------- PLEASE INPUT APPOINTMENT INFORMATION HERE ----------------------------- \n";
    cout << endl;

    cout << " Enter patient name for appointment (first middle last): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newAppointment.patientName);

    cout << " Enter patient ID (EXAMPLE - 1001) : ";
    cin >> newAppointment.patientID;

    cout << " Enter appointment date (EXAMPLE - 10/11/2020): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newAppointment.date);
    
    cout << " Enter appointment time (EXAMPLE - 09.25 AM): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newAppointment.time);

    // Enqueue the new appointment
    appointmentQueue.push(newAppointment);
    appointmentList.push_back(newAppointment);

    cout << " **********************************" << endl;
    cout << " Appointment scheduled successfully" << endl;
    cout << " **********************************" << endl << endl;

    // Prompt user to save
    char saveChoice;
    cout << " Do you want to save the appointment records? (y/n): ";
    cin >> saveChoice;

    if (saveChoice == 'y' || saveChoice == 'Y') {
        saveAppointmentsToFile();
    }
}

//Function to dequeue appointment using FIFO
void dequeueAppointment() {
    if (!appointmentQueue.empty()) {
        cout << endl;
        cout << " Dequeueing appointment: " << appointmentQueue.front().patientName << endl <<endl;

        // Remove the dequeued appointment from the linked list
        appointmentList.pop_front();

        // Rewrite the entire appointments file
        ofstream file("appointments.txt");
        for (const Appointment& a : appointmentList) {
            file << a.patientID << " " << a.patientName << " " << a.date << " " << a.time << endl;
        }

        cout << " -- Appointment records updated and saved to file. --" << endl;
    }
    else {
        cout << " -- Appointment queue is empty. --" << endl;
    }
}

//Function to cancel appointment and user can choose which to cancel
void cancelAppointment() {
    int cancelID;

    cout << endl;
    cout << " Enter patient ID to cancel appointment: ";
    cin >> cancelID;

    // Search for the appointment based on patient ID
    auto i = find_if(appointmentList.begin(), appointmentList.end(), [cancelID](const Appointment& a) {
        return a.patientID == cancelID;
        });

    if (i != appointmentList.end()) {
        cout << " Canceling appointment for patient: " << i->patientName << endl << endl;

        // Remove the canceled appointment from the linked list
        appointmentList.erase(i);

        // Rewrite the entire appointments file
        ofstream file("appointments.txt");
        for (const Appointment& a : appointmentList) {
            file << a.patientID << " " << a.patientName << " " << a.date << " " << a.time << endl;
        }

        cout << " -- Appointment canceled and records updated. --" << endl;
    }
    else {
        cout << " -- Appointment not found.--" << endl;
    }
}

// Function to save patient records to a text file
void savePatientRecordsToFile() {
    ofstream file("patients.txt");

    for (const Patient& p : patientRecords) {
        file << p.id << " " << p.name << " " << p.gender << " " << p.DOB << " " << p.address << " " << p.phone << " " << p.medicalDATE << " " << p.medicalDETAILS << endl;
    }

    cout << "\n-- Patient records saved to file. --" << endl << endl;
}


// Function to save appointments to a text file
void saveAppointmentsToFile() {
    ofstream file("appointments.txt");

    for (const Appointment& a : appointmentList) {
        file << a.patientID << " " << a.patientName << " " << a.date << " " << a.time << endl;
    }

    cout << "\n-- Appointment records saved to file. --" << endl <<endl;
}

// Function to load appointments from a text file
void loadAppointmentsFromFile() {
    ifstream file("appointments.txt");

    if (file.is_open()) {
        appointmentList.clear(); // Clear existing records

        Appointment appointment;
        while (file >> appointment.patientID >> appointment.patientName >> appointment.date >> appointment.time) {
            appointmentList.push_back(appointment);
        }

        cout << "-- Appointment records loaded from file. --" << endl;
    }
    else {
        cout << "-- Error opening appointments file. --" << endl;
    }
}

// Function to display appointment records
void displayAppointments() {
    if (appointmentList.empty()) {
        cout << "No appointments available." << endl;
        return;
    }

    cout << "\t\t----------------------------- APPOINTMENT RECORDS ----------------------------- " << endl;
    for (const Appointment& a : appointmentList) {
        cout << "ID: " << a.patientID << ", Name: " << a.patientName << ", Date: " << a.date << ", Time: " << a.time << endl;
    }
}



// Function to sort patient records based on patient ID
void sortPatientRecords() {
    patientRecords.sort([](const Patient& a, const Patient& b) { //introsort (use c++ library in sort function)
        return a.id < b.id;
        });
    cout << " -- Patient records sorted successfully based on patient ID. --" << endl;
}

// Function to search for a patient record based on patient ID
void searchPatientRecord() {
    int searchID;
    cout << endl;
    cout << " Enter patient ID to search: ";
    cin >> searchID;

    auto it = find_if(patientRecords.begin(), patientRecords.end(), [searchID](const Patient& p) {
        return p.id == searchID;
        });

    if (it != patientRecords.end()) {
        cout << " -- Patient found: --" << it->name << endl;
    }
    else {
        cout << " -- Patient not found. --" << endl;
    }
}




// Function to handle emergency alert and add to the emergency queue
void PatientEmergency() {
    Patient emergencyAlert;
    cout << "Enter patient name for emergency: ";
    cin.ignore(); // Clear the newline character left in the buffer
    getline(cin, emergencyAlert.name);
    cout << "Enter patient ID: ";
    cin >> emergencyAlert.id;

    // Enqueue the emergency case
    emergencyQueue.push(emergencyAlert);
    cout << "Emergency case handled successfully and added to the priority queue." << endl;

    // Save the emergency case to the emergency.txt file
    ofstream emergencyFile("emergency.txt", ios::app); // Open file in append mode
    if (emergencyFile.is_open()) {
        emergencyFile << emergencyAlert.id << " " << emergencyAlert.name << endl;
        emergencyFile.close();
        cout << "Emergency alert saved to emergency.txt." << endl;
    }
    else {
        cout << "Error opening emergency.txt for saving." << endl;
    }
}

// Function to load emergency Alert from a text file
void loadEmergencyAlertFromFile() {
    ifstream emergencyFile("emergency.txt");

    if (emergencyFile.is_open()) {
        emergencyQueue = priority_queue<Patient, vector<Patient>, greater<Patient>>(); // Clear existing records

        Patient emergencyAlert;
        while (emergencyFile >> emergencyAlert.id >> emergencyAlert.name) {
            emergencyQueue.push(emergencyAlert);
        }

        cout << "Emergency alert loaded from emergency.txt." << endl;
        emergencyFile.close();
    }
    else {
        cout << "Error opening emergency.txt for loading." << endl;
    }
}

// Function to display alerts for emergency Alerts
void displayEmergencyAlerts() {
    if (!emergencyQueue.empty()) {
        cout << "Emergency Alert:\n";
        while (!emergencyQueue.empty()) {
            const Patient& emergencyAlert = emergencyQueue.top();
            cout << "Patient ID: " << emergencyAlert.id << ", Name: " << emergencyAlert.name << " - Emergency alert\n";
            emergencyQueue.pop();
        }
    }
    else {
        cout << "No emergency cases available." << endl;
    }
}

// Function to process emergency cases from the priority queue
void processEmergencies() {
    if (!emergencyQueue.empty()) {
        cout << "Processing emergency alert:\n";
        while (!emergencyQueue.empty()) {
            Patient emergencyAlert  = emergencyQueue.top();
            cout << "Patient ID: " << emergencyAlert.id << ", Name: " << emergencyAlert.name << " - Emergency alert\n";
            

            // Dequeue the emergency alert
            emergencyQueue.pop();
        }
    }
    else {
        cout << "No emergency alert in the priority queue." << endl;
    }
}



// Function to load patient records from a text file
void loadPatientRecordsFromFile() {
    ifstream file("patients.txt");

    if (file.is_open()) {
        patientRecords.clear(); // Clear existing records

        Patient patient;
        while (file >> patient.id >> patient.name >> patient.gender >> patient.DOB >> patient.address >> patient.phone >> patient.medicalDATE >> patient.medicalDETAILS) {
            patientRecords.push_back(patient);
        }

        cout << "Patient records loaded from file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}


// Function to display patient records
void displayPatientRecords() {
    if (patientRecords.empty()) {
        cout << "No patient records available." << endl;
        return;
    }
   
    cout << "\t\t----------------------------- PATIENT RECORDS ----------------------------- " << endl;
    for (const Patient& p : patientRecords) {
        cout << "ID: " << p.id << ", Name: " << p.name << ", Gender: " << p.gender << ", D.O.B: " << p.DOB << ", Address: " << p.address << ", Phone number: " << p.phone << endl;

    }
    int Choice;
    cout << "\n Do you want to : " << endl << endl;
    cout << "1. EDIT" << endl;
    cout << "2. DELETE" << endl; 
    cout << "0. EXIT" << endl << endl;
    cout << "Choose : ";
    cin >> Choice;

    if (Choice == 1) {
        editPatientRecord();
    } else if (Choice == 2) {
        deletePatientRecord();
    }
    else {
        return;
    }
}

//Function Edit Patient Record
void editPatientRecord() {
    int editID;
    string input;

    cout << "Enter patient ID to edit record: ";
    cin >> input;

    // Validate if the input is an integer
    while (true) {
        istringstream iss(input);
        if (iss >> editID && iss.eof()) {
            break; // Valid integer input
        }
        else {
            cout << "Invalid input. Please enter a valid integer for patient ID: ";
            cin >> input;
        }
    }

    // Search for the patient based on ID
    auto change = find_if(patientRecords.begin(), patientRecords.end(), [editID](const Patient& p) {
        return p.id == editID;
        });

    if (change != patientRecords.end()) {
        cout << "Editing record for patient: " << change->name << endl;

        //edit name
        cout << "Enter the new name: ";
        cin.ignore();  // Clear the input buffer
        getline(cin, change->name);


        cout << "Patient record updated successfully." << endl;

        // Rewrite the entire patient records file
        ofstream file("patients.txt");
        for (const Patient& p : patientRecords) {
            file << p.id << " " << p.name << " " << p.gender << " " << p.DOB << " " << p.address << " " << p.phone << " " << p.medicalDATE << " " << p.medicalDETAILS << endl;
        }
    }
    else {
        cout << "Patient record not found." << endl;
    }
}


//Function to delete patient record
void deletePatientRecord() {
    int deleteID;
    string input;

    cout << "Enter patient ID to delete record: ";
    cin >> input;

    // Validate if the input is an integer
    while (true) {
        stringstream ss(input);
        if (ss >> deleteID && ss.eof()) {
            break; // Valid integer input
        }
        else {
            cout << "Invalid input. Please enter a valid integer for patient ID: ";
            cin >> input;
        }
    }

    // Search for the patient based on ID
    auto del = find_if(patientRecords.begin(), patientRecords.end(), [deleteID](const Patient& p) {
        return p.id == deleteID;
        });

    if (del != patientRecords.end()) {
        cout << "Deleting record for patient: " << del->name << endl;

        // Remove the deleted patient record from the linked list
        patientRecords.erase(del);

        // Rewrite the entire patient records file
        ofstream file("patients.txt");
        for (const Patient& p : patientRecords) {
            file << p.id << " " << p.name << " " << p.gender << " " << p.DOB << " " << p.address << " " << p.phone << " " << p.medicalDATE << p.medicalDETAILS << endl;
        }

        cout << "Patient record deleted and records updated." << endl;
    }
    else {
        cout << "Patient record not found" << endl;
    }

    cout << "Returning to the main menu." << endl;
}

//function delete medical record
void displayMedicalRecords() {
    if (patientRecords.empty()) {
        cout << "No patient records available." << endl;
        return;
    }

    cout << "\t\t----------------------------- MEDICAL RECORDS ----------------------------- " << endl;
    
    for (const Patient& p : patientRecords) {
        cout << "ID: " << p.id << ", Name: " << p.name << ", Gender: " << p.gender <<  ", Medical date " << p.medicalDATE << ", Medical details " << p.medicalDETAILS << endl;
    }
}


// Main menu
void showMenu() {
   
    cout << "\n\t\t\t\t\t ================================\n";
    cout << " " << "\t\t\t\t\t+\t\t\t\t + ";
    cout << " " << "\n\t\t\t\t\t+\t\tMenu \t"<<"\t + \n";
    cout << " " << "\t\t\t\t\t+\t\t\t\t +";
    cout << "\n\t\t\t\t\t ================================\n\n";


    cout << "\t\t\t\t\t1. Add Patient Record \n";
    cout << "\t\t\t\t\t2. Sort Patient Records\n";
    cout << "\t\t\t\t\t3. Search Patient Record\n";
    cout << "\t\t\t\t\t4. Schedule Appointment\n";
    cout << "\t\t\t\t\t5. Patient Emergency\n";
    cout << "\t\t\t\t\t6. Load Patient Records\n";
    cout << "\t\t\t\t\t7. Load Emergency Alert File\n";
    cout << "\t\t\t\t\t8. Display Emergency Alert\n";
    cout << "\t\t\t\t\t9. Process Emergency\n";
    cout << "\t\t\t\t\t10. Display Patient Records\n";
    cout << "\t\t\t\t\t11. Load Appointment Records\n";
    cout << "\t\t\t\t\t12. Display Appointment Records\n";
    cout << "\t\t\t\t\t13. Medical Records\n";
    cout << "\t\t\t\t\t14. Cancel Appointment\n";
    cout << "\t\t\t\t\t15. Delete Appointment\n";
    cout << "\t\t\t\t\t16. Exit\n";
    cout << "\n\t\t\t\t\t ================================\n\n";
    cout << "\n\t\t\t\t\tEnter your choice: ";
}

int main() {
    int choice;

 
    cout << "\n\t\t\t WELCOME TO BUDIMAN PRIVATE HOSPITAL PATIENT MANAGEMENT SYSTEM " << endl;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addPatientRecord();
            break;
        case 2:
            sortPatientRecords();
            break;
        case 3:
            searchPatientRecord();
            break;
        case 4:
            scheduleAppointment();
            break;
        case 5:
            PatientEmergency();
            break;
        case 6:
            loadPatientRecordsFromFile();
            break;
        case 7:
            loadEmergencyAlertFromFile();
            break;
        case 8:
            displayEmergencyAlerts();
            break;
        case 9:
            processEmergencies();
            break;
        case 10:
            displayPatientRecords(); 
            break;
        case 11:
            loadAppointmentsFromFile();
            break;
        case 12:
            displayAppointments();
            break;
        case 13:
            displayMedicalRecords();
            break;
        case 14:
            cancelAppointment();
            break;
        case 15:
            dequeueAppointment();
            break;
        case 16:
            cout << "\n\t\t\t\t\tExiting program.\n";
            break;
        default:
            cout << "\n \t\t\t\t\t Invalid choice. Please try again.\n";
        }

    } while (choice != 16);

    return 0;
}