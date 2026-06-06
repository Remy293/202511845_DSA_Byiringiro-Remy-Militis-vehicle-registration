#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <regex>

using namespace std;

// ==========================================
// 1. INHERITANCE DESIGN & ENCAPSULATION
// ==========================================

// Base Class: User
class User {
protected:
    string name;
    string email;
    string phone;

public:
    // Default Constructor
    User() : name(""), email(""), phone("") {}

    // Parameterized Constructor
    User(string n, string e, string p) : name(n), email(e), phone(p) {}

    // Getters and Setters
    string getName() const { return name; }
    void setName(string n) { name = n; }

    string getEmail() const { return email; }
    void setEmail(string e) { email = e; }

    string getPhone() const { return phone; }
    void setPhone(string p) { phone = p; }
};

// Derived Class: VehicleOwner (Inherits from User)
class VehicleOwner : public User {
public:
    // Default Constructor chaining to Base Default Constructor
    VehicleOwner() : User() {}

    // Parameterized Constructor demonstrating Constructor Chaining
    VehicleOwner(string n, string e, string p) : User(n, e, p) {}
};

// Independent Class: Vehicle (Associated with VehicleOwner)
class Vehicle {
private:
    string plateNumber;
    string vehicleType;
    int year;
    VehicleOwner owner; // Composition/Association relationship

public:
    // Default Constructor
    Vehicle() : plateNumber(""), vehicleType(""), year(0), owner() {}

    // Parameterized Constructor
    Vehicle(string plate, string type, int y, VehicleOwner vo) 
        : plateNumber(plate), vehicleType(type), year(y), owner(vo) {}

    // Getters and Setters
    string getPlateNumber() const { return plateNumber; }
    void setPlateNumber(string plate) { plateNumber = plate; }

    string getVehicleType() const { return vehicleType; }
    void setVehicleType(string type) { vehicleType = type; }

    int getYear() const { return year; }
    void setYear(int y) { year = y; }

    VehicleOwner getOwner() const { return owner; }
    void setOwner(VehicleOwner vo) { owner = vo; }

    // Helper to format data into CSV line
    string toCSV() const {
        return plateNumber + "," + vehicleType + "," + to_string(year) + "," +
               owner.getName() + "," + owner.getEmail() + "," + owner.getPhone();
    }
};

// ==========================================
// 2. INPUT VALIDATION UTILITIES
// ==========================================

class Validator {
public:
    // Validates Plate Number pattern (e.g., RAA123A)
    static bool validatePlate(const string& plate) {
        regex pattern("^[A-Z]{3}[0-9]{3}[A-Z]{1}$");
        return regex_match(plate, pattern);
    }

    // Validates Email format containing '@' and '.' cleanly
    static bool validateEmail(const string& email) {
        regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        return regex_match(email, pattern);
    }

    // Validates Phone starting with +250, exactly 13 chars, digits only after prefix
    static bool validatePhone(const string& phone) {
        regex pattern("^\\+250[0-9]{9}$");
        return regex_match(phone, pattern);
    }
};

// ==========================================
// 3. FILE HANDLING & SYSTEM OPERATIONS
// ==========================================

class SystemManager {
private:
    const string filename = "records.txt";

public:
    // Append a new record to the file
    void addRecord(const Vehicle& vehicle) {
        ofstream outFile(filename, ios::app);
        if (!outFile) {
            cout << "\n[Error] Could not open file to save record.\n";
            return;
        }
        outFile << vehicle.toCSV() << "\n";
        outFile.close();
        cout << "\n>> Record saved successfully to " << filename << "!\n";
    }

    // Read all records using stringstream processing
    vector<Vehicle> getAllRecords() {
        vector<Vehicle> records;
        ifstream inFile(filename);
        if (!inFile) {
            return records; // Returns empty list if file doesn't exist yet
        }

        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string plate, type, yearStr, name, email, phone;

            // Split CSV values via stringstream
            getline(ss, plate, ',');
            getline(ss, type, ',');
            getline(ss, yearStr, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');

            // Convert data types safely
            int year = 0;
            try {
                year = stoi(yearStr);
            } catch (...) {
                year = 0;
            }

            VehicleOwner owner(name, email, phone);
            Vehicle vehicle(plate, type, year, owner);
            records.push_back(vehicle);
        }
        inFile.close();
        return records;
    }

    // Formatted display of a single row
    void printRow(const Vehicle& v) const {
        cout << left << setw(14) << v.getPlateNumber()
             << setw(14) << v.getVehicleType()
             << setw(8)  << v.getYear()
             << setw(20) << v.getOwner().getName()
             << setw(25) << v.getOwner().getEmail()
             << v.getOwner().getPhone() << "\n";
    }

    // Formatted table view of all records
    void displayAll() {
        vector<Vehicle> records = getAllRecords();
        if (records.empty()) {
            cout << "\nNo records found in " << filename << ".\n";
            return;
        }

        cout << "\n" << string(95, '=') << "\n";
        cout << left << setw(14) << "Plate No" 
             << setw(14) << "Type" 
             << setw(8)  << "Year" 
             << setw(20) << "Owner Name" 
             << setw(25) << "Email" 
             << "Phone Number\n";
        cout << string(95, '-') << "\n";

        for (const auto& vehicle : records) {
            printRow(vehicle);
        }
        cout << string(95, '=') << "\n";
    }

    // Precise search by unique plate number
    void searchByPlate(string plate) {
        // Normalize input to uppercase
        for (auto &c : plate) c = toupper(c);

        vector<Vehicle> records = getAllRecords();
        bool found = false;

        for (const auto& vehicle : records) {
            if (vehicle.getPlateNumber() == plate) {
                if (!found) {
                    cout << "\n--- Record Found Details ---\n";
                    cout << "Plate Number : " << vehicle.getPlateNumber() << "\n";
                    cout << "Vehicle Type : " << vehicle.getVehicleType() << "\n";
                    cout << "Mfg Year     : " << vehicle.getYear() << "\n";
                    cout << "Owner Name   : " << vehicle.getOwner().getName() << "\n";
                    cout << "Owner Email  : " << vehicle.getOwner().getEmail() << "\n";
                    cout << "Owner Phone  : " << vehicle.getOwner().getPhone() << "\n";
                    cout << string(28, '-') << "\n";
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            cout << "\n[Result] Error: Vehicle with plate " << plate << " does not exist in the system.\n";
        }
    }
};

// ==========================================
// 4. INTERACTIVE CONSOLE USER INTERFACE
// ==========================================

int main() {
    SystemManager manager;
    int choice;

    do {
        cout << "\n===== VEHICLE REGISTRATION SYSTEM =====\n";
        cout << "1. Add New Vehicle Record\n";
        cout << "2. Display All Records (Table View)\n";
        cout << "3. Search Vehicle by Plate Number\n";
        cout << "4. Exit System\n";
        cout << "Enter your choice (1-4): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input type. Please restart or select carefully.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(); // Flush stream buffer

        if (choice == 1) {
            string plate, type, name, email, phone;
            int year;

            // Loop until a structurally accurate Plate is specified
            while (true) {
                cout << "Enter Plate Number (e.g., RAA123A): ";
                getline(cin, plate);
                // Convert plate input to uppercase automatically for standardization
                for (auto &c : plate) c = toupper(c);
                if (Validator::validatePlate(plate)) break;
                cout << "[Invalid Format] Must be 3 upper letters, 3 digits, then 1 letter.\n";
            }

            cout << "Enter Vehicle Type (e.g., Sedan, SUV): ";
            getline(cin, type);

            while (true) {
                cout << "Enter Vehicle Year: ";
                if (cin >> year && year > 1800 && year <= 2026) {
                    cin.ignore();
                    break;
                }
                cout << "[Invalid Year] Please enter a valid production year.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cout << "Enter Owner Full Name: ";
            getline(cin, name);

            while (true) {
                cout << "Enter Owner Email Address: ";
                getline(cin, email);
                if (Validator::validateEmail(email)) break;
                cout << "[Invalid Format] Email must contain standard format symbols like '@' and '.'\n";
            }

            while (true) {
                cout << "Enter Owner Phone Number (e.g., +250788123456): ";
                getline(cin, phone);
                if (Validator::validatePhone(phone)) break;
                cout << "[Invalid Format] Must start with '+250' followed by exactly 9 digits.\n";
            }

            // Bind values dynamically using architecture objects
            VehicleOwner owner(name, email, phone);
            Vehicle vehicle(plate, type, year, owner);
            manager.addRecord(vehicle);

        } else if (choice == 2) {
            manager.displayAll();
        } else if (choice == 3) {
            string searchPlate;
            cout << "Enter Plate Number to search: ";
            getline(cin, searchPlate);
            manager.searchByPlate(searchPlate);
        } else if (choice == 4) {
            cout << "\nExiting System. Thank you!\n";
        } else {
            cout << "\n[Error] Choice outside valid criteria. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
