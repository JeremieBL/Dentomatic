#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// Patient structure to store patient information
struct Patient {
    int id;
    string name;
    string phone;
    string email;
    string address;
    string medicalHistory;
};

// Appointment structure to store appointment details
struct Appointment {
    int id;
    int patientId;
    string patientName;
    string date;
    string time;
    string reason;
    string status; // scheduled, completed, cancelled
};

// Global data storage
vector<Patient> patients;
vector<Appointment> appointments;
int nextPatientId = 1;
int nextAppointmentId = 1;

// File names for data persistence
const string PATIENTS_FILE = "patients.dat";
const string APPOINTMENTS_FILE = "appointments.dat";

// Function prototypes
void loadData();
void saveData();
void showMainMenu();
void patientManagement();
void appointmentManagement();
void addPatient();
void viewPatients();
void searchPatient();
void scheduleAppointment();
void viewAppointments();
void updateAppointmentStatus();
string trim(const string& str);

int main() {
    cout << "===========================================\n";
    cout << "   DENTOMATIC - Dental Practice Manager\n";
    cout << "===========================================\n\n";
    
    loadData();
    showMainMenu();
    saveData();
    
    cout << "\nThank you for using Dentomatic!\n";
    return 0;
}

void showMainMenu() {
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Patient Management\n";
        cout << "2. Appointment Management\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                patientManagement();
                break;
            case 2:
                appointmentManagement();
                break;
            case 3:
                cout << "Saving data and exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 3);
}

void patientManagement() {
    int choice;
    do {
        cout << "\n--- Patient Management ---\n";
        cout << "1. Add New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
}

void appointmentManagement() {
    int choice;
    do {
        cout << "\n--- Appointment Management ---\n";
        cout << "1. Schedule Appointment\n";
        cout << "2. View All Appointments\n";
        cout << "3. Update Appointment Status\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                scheduleAppointment();
                break;
            case 2:
                viewAppointments();
                break;
            case 3:
                updateAppointmentStatus();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
}

void addPatient() {
    Patient p;
    p.id = nextPatientId++;
    
    cout << "\n--- Add New Patient ---\n";
    cout << "Patient ID: " << p.id << " (auto-generated)\n";
    
    cout << "Enter patient name: ";
    getline(cin, p.name);
    
    cout << "Enter phone number: ";
    getline(cin, p.phone);
    
    cout << "Enter email: ";
    getline(cin, p.email);
    
    cout << "Enter address: ";
    getline(cin, p.address);
    
    cout << "Enter medical history/notes: ";
    getline(cin, p.medicalHistory);
    
    patients.push_back(p);
    cout << "\nPatient added successfully! Patient ID: " << p.id << "\n";
}

void viewPatients() {
    if(patients.empty()) {
        cout << "\nNo patients in the system.\n";
        return;
    }
    
    cout << "\n--- Patient List ---\n";
    cout << left << setw(5) << "ID" 
         << setw(25) << "Name" 
         << setw(15) << "Phone" 
         << setw(25) << "Email" << "\n";
    cout << string(70, '-') << "\n";
    
    for(const auto& p : patients) {
        cout << left << setw(5) << p.id 
             << setw(25) << p.name 
             << setw(15) << p.phone 
             << setw(25) << p.email << "\n";
    }
}

void searchPatient() {
    if(patients.empty()) {
        cout << "\nNo patients in the system.\n";
        return;
    }
    
    cout << "\n--- Search Patient ---\n";
    cout << "Enter patient name or ID: ";
    string search;
    getline(cin, search);
    
    bool found = false;
    int searchId = -1;
    try {
        searchId = stoi(search);
    } catch(...) {
        // Not a number, search by name
    }
    
    for(const auto& p : patients) {
        if(p.id == searchId || p.name.find(search) != string::npos) {
            cout << "\n--- Patient Details ---\n";
            cout << "ID: " << p.id << "\n";
            cout << "Name: " << p.name << "\n";
            cout << "Phone: " << p.phone << "\n";
            cout << "Email: " << p.email << "\n";
            cout << "Address: " << p.address << "\n";
            cout << "Medical History: " << p.medicalHistory << "\n";
            found = true;
        }
    }
    
    if(!found) {
        cout << "No patient found matching '" << search << "'.\n";
    }
}

void scheduleAppointment() {
    if(patients.empty()) {
        cout << "\nNo patients in the system. Please add patients first.\n";
        return;
    }
    
    Appointment apt;
    apt.id = nextAppointmentId++;
    
    cout << "\n--- Schedule Appointment ---\n";
    cout << "Appointment ID: " << apt.id << " (auto-generated)\n";
    
    cout << "Enter patient ID: ";
    cin >> apt.patientId;
    cin.ignore();
    
    // Find patient name
    bool patientFound = false;
    for(const auto& p : patients) {
        if(p.id == apt.patientId) {
            apt.patientName = p.name;
            patientFound = true;
            break;
        }
    }
    
    if(!patientFound) {
        cout << "Patient ID not found. Appointment not scheduled.\n";
        nextAppointmentId--; // Revert ID increment
        return;
    }
    
    cout << "Enter appointment date (YYYY-MM-DD): ";
    getline(cin, apt.date);
    
    cout << "Enter appointment time (HH:MM): ";
    getline(cin, apt.time);
    
    cout << "Enter reason for visit: ";
    getline(cin, apt.reason);
    
    apt.status = "scheduled";
    
    appointments.push_back(apt);
    cout << "\nAppointment scheduled successfully! Appointment ID: " << apt.id << "\n";
}

void viewAppointments() {
    if(appointments.empty()) {
        cout << "\nNo appointments in the system.\n";
        return;
    }
    
    cout << "\n--- Appointment List ---\n";
    cout << left << setw(5) << "ID" 
         << setw(8) << "Pat.ID" 
         << setw(20) << "Patient Name"
         << setw(12) << "Date" 
         << setw(8) << "Time" 
         << setw(20) << "Reason"
         << setw(12) << "Status" << "\n";
    cout << string(85, '-') << "\n";
    
    for(const auto& apt : appointments) {
        cout << left << setw(5) << apt.id 
             << setw(8) << apt.patientId 
             << setw(20) << apt.patientName.substr(0, 19)
             << setw(12) << apt.date 
             << setw(8) << apt.time 
             << setw(20) << apt.reason.substr(0, 19)
             << setw(12) << apt.status << "\n";
    }
}

void updateAppointmentStatus() {
    if(appointments.empty()) {
        cout << "\nNo appointments in the system.\n";
        return;
    }
    
    cout << "\n--- Update Appointment Status ---\n";
    cout << "Enter appointment ID: ";
    int id;
    cin >> id;
    cin.ignore();
    
    bool found = false;
    for(auto& apt : appointments) {
        if(apt.id == id) {
            cout << "Current status: " << apt.status << "\n";
            cout << "Select new status:\n";
            cout << "1. Scheduled\n";
            cout << "2. Completed\n";
            cout << "3. Cancelled\n";
            cout << "Enter choice: ";
            int choice;
            cin >> choice;
            cin.ignore();
            
            switch(choice) {
                case 1:
                    apt.status = "scheduled";
                    break;
                case 2:
                    apt.status = "completed";
                    break;
                case 3:
                    apt.status = "cancelled";
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            
            cout << "Appointment status updated successfully!\n";
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "Appointment ID not found.\n";
    }
}

void loadData() {
    // Load patients
    ifstream pFile(PATIENTS_FILE);
    if(pFile.is_open()) {
        string line;
        while(getline(pFile, line)) {
            Patient p;
            stringstream ss(line);
            string field;
            
            getline(ss, field, '|'); p.id = stoi(field);
            getline(ss, p.name, '|');
            getline(ss, p.phone, '|');
            getline(ss, p.email, '|');
            getline(ss, p.address, '|');
            getline(ss, p.medicalHistory, '|');
            
            patients.push_back(p);
            if(p.id >= nextPatientId) {
                nextPatientId = p.id + 1;
            }
        }
        pFile.close();
        cout << "Loaded " << patients.size() << " patients.\n";
    }
    
    // Load appointments
    ifstream aFile(APPOINTMENTS_FILE);
    if(aFile.is_open()) {
        string line;
        while(getline(aFile, line)) {
            Appointment apt;
            stringstream ss(line);
            string field;
            
            getline(ss, field, '|'); apt.id = stoi(field);
            getline(ss, field, '|'); apt.patientId = stoi(field);
            getline(ss, apt.patientName, '|');
            getline(ss, apt.date, '|');
            getline(ss, apt.time, '|');
            getline(ss, apt.reason, '|');
            getline(ss, apt.status, '|');
            
            appointments.push_back(apt);
            if(apt.id >= nextAppointmentId) {
                nextAppointmentId = apt.id + 1;
            }
        }
        aFile.close();
        cout << "Loaded " << appointments.size() << " appointments.\n";
    }
}

void saveData() {
    // Save patients
    ofstream pFile(PATIENTS_FILE);
    if(pFile.is_open()) {
        for(const auto& p : patients) {
            pFile << p.id << "|" 
                  << p.name << "|" 
                  << p.phone << "|" 
                  << p.email << "|" 
                  << p.address << "|" 
                  << p.medicalHistory << "|\n";
        }
        pFile.close();
    }
    
    // Save appointments
    ofstream aFile(APPOINTMENTS_FILE);
    if(aFile.is_open()) {
        for(const auto& apt : appointments) {
            aFile << apt.id << "|" 
                  << apt.patientId << "|" 
                  << apt.patientName << "|" 
                  << apt.date << "|" 
                  << apt.time << "|" 
                  << apt.reason << "|" 
                  << apt.status << "|\n";
        }
        aFile.close();
    }
    
    cout << "Data saved successfully.\n";
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
