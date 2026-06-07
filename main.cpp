#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include "Vehicle.h"
using namespace std;

bool validEmail(string email) {
    return email.find('@') != string::npos &&
           email.find('.') != string::npos;
}

bool validPhone(string phone) {
    regex pattern("^\\+250[0-9]{9}$");
    return regex_match(phone, pattern);
}

bool validPlate(string plate) {
    regex pattern("^[R][A-Z]{2}[0-9]{3}[A-Z]$");
    return regex_match(plate, pattern);
}

void addRecord() {
    string plate, type, name, email, phone;
    int year;

    do { cout << "Plate Number: "; cin >> plate; }
    while (!validPlate(plate));

    cout << "Vehicle Type: "; cin >> type;
    cout << "Year: "; cin >> year;

    cin.ignore();
    cout << "Owner Name: ";
    getline(cin, name);

    do { cout << "Email: "; getline(cin, email); }
    while (!validEmail(email));

    do { cout << "Phone: "; getline(cin, phone); }
    while (!validPhone(phone));

    VehicleOwner owner(name, email, phone);
    Vehicle vehicle(plate, type, year, owner);

    ofstream file("records.txt", ios::app);
    file << vehicle.toCSV() << endl;
}

void searchVehicle() {
    string searchPlate;
    cout << "Enter Plate Number: ";
    cin >> searchPlate;

    ifstream file("records.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string plate, type, year, name, email, phone;

        getline(ss, plate, ',');
        getline(ss, type, ',');
        getline(ss, year, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (plate == searchPlate) {
            cout << plate << " " << type << " " << year << " "
                 << name << " " << email << " " << phone << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Vehicle does not exist." << endl;
}

void displayAll() {
    ifstream file("records.txt");
    string line;

    while (getline(file, line))
        cout << line << endl;
}

int main() {
    int choice;
    do {
        cout << "\n1.Add\n2.Search\n3.Display\n4.Exit\nChoice: ";
        cin >> choice;

        switch(choice) {
            case 1: addRecord(); break;
            case 2: searchVehicle(); break;
            case 3: displayAll(); break;
        }
    } while(choice != 4);

    return 0;
}