#include "vehicle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
// ---- User class ----
User::User() {}
User::User(string n, string e, string p) {
name = n;
email = e;
phone = p;
}
string User::getName() { return name; }
string User::getEmail() { return email; }
string User::getPhone() { return phone; }

void User::setName(string n) { name = n; }
void User::setEmail(string e) { email = e; }
void User::setPhone(string p) { phone = p; }
// ---- VehicleOwner class ----
VehicleOwner::VehicleOwner() {}
VehicleOwner::VehicleOwner(string n, string e, string p) : User(n, e, p) {}
// ---- Vehicle class ----
Vehicle::Vehicle() {}
Vehicle::Vehicle(string plate, string type, int yr, VehicleOwner o) {
plateNumber = plate;
vehicleType = type;
year 	= yr;
owner 	= o;
}
string Vehicle::getPlate() { return plateNumber; }
string Vehicle::getType() { return vehicleType; }
int 	Vehicle::getYear() { return year; }
VehicleOwner Vehicle::getOwner() { return owner; }
// ---- Validation functions ----
bool isValidEmail(string email) {
int atPos = email.find('@');
int dotPos = email.rfind('.');
if (atPos == string::npos || dotPos == string::npos) return false;
if (atPos == 0 || dotPos < atPos) return false;
if (dotPos == email.length() - 1) return false;
return true;
}
bool isValidPhone(string phone) {
if (phone.length() != 13) return false;
if (phone.substr(0, 4) != "+250") return false;
for (int i = 4; i < phone.length(); i++) {
if (!isdigit(phone[i])) return false;
}
return true;
}
bool isValidPlate(string plate) {
// Format: RAA123A (3 letters, 3 digits, 1 letter)
if (plate.length() != 7) return false;
if (!isalpha(plate[0]) || !isalpha(plate[1]) || !isalpha(plate[2])) return false;
if (!isdigit(plate[3]) || !isdigit(plate[4]) || !isdigit(plate[5])) return false;
if (!isalpha(plate[6])) return false;
return true;
}
// ---- File functions ----
void saveRecord(Vehicle v) {
ofstream file("records.txt", ios::app);
file << v.getPlate() 	<< ","
<< v.getType() 	<< ","
<< v.getYear() 	<< ","
<< v.getOwner().getName() << ","
<< v.getOwner().getEmail() << ","
<< v.getOwner().getPhone() << "\n";
file.close();
}
vector<Vehicle> loadRecords() {
vector<Vehicle> records;
ifstream file("records.txt");
string line;
while (getline(file, line)) {
stringstream ss(line);
string plate, type, yearStr, name, email, phone;
getline(ss, plate, ',');
getline(ss, type, 	',');
getline(ss, yearStr, ',');
getline(ss, name, 	',');
getline(ss, email, ',');
getline(ss, phone, ',');
int year = stoi(yearStr);
VehicleOwner owner(name, email, phone);
Vehicle v(plate, type, year, owner);
records.push_back(v);
}
file.close();
return records;
}
// ---- Menu functions ----
void addRecord() {
string plate, type, name, email, phone;
int year;
do {
cout << "Enter plate number (e.g. RAA123A): ";
cin >> plate;
if (!isValidPlate(plate))
cout << "Invalid plate. Must be like RAA123A.\n";
} while (!isValidPlate(plate));
cout << "Enter vehicle type (e.g. Sedan, SUV): ";
cin >> type;
cout << "Enter year of manufacture: ";
cin >> year;
cin.ignore();
cout << "Enter owner name: ";
getline(cin, name);
do {
cout << "Enter owner email: ";
cin >> email;
if (!isValidEmail(email))
cout << "Invalid email. Must contain @ and .\n";
} while (!isValidEmail(email));
do {
cout << "Enter phone number (e.g. +250788123456): ";
cin >> phone;
if (!isValidPhone(phone))
cout << "Invalid phone. Must start with +250 and be 13 characters.\n";
} while (!isValidPhone(phone));
VehicleOwner owner(name, email, phone);
Vehicle v(plate, type, year, owner);
saveRecord(v);
cout << "Record saved successfully!\n";
}
void displayAll() {
vector<Vehicle> records = loadRecords();
if (records.empty()) {
cout << "\nNo records found.\n";
return;
}
cout << "\n";
cout << left
<< setw(10) << "Plate"
<< setw(10) << "Type"
<< setw(7) << "Year"
<< setw(18) << "Owner"
<< setw(25) << "Email"
<< setw(15) << "Phone"
<< "\n";
cout << string(85, '-') << "\n";
for (int i = 0; i < records.size(); i++) {
Vehicle v = records[i];
cout << left
<< setw(10) << v.getPlate()
<< setw(10) << v.getType()
<< setw(7) << v.getYear()
<< setw(18) << v.getOwner().getName()
<< setw(25) << v.getOwner().getEmail()
<< setw(15) << v.getOwner().getPhone()
<< "\n";
}
}
void searchRecord() {
string plate;
cout << "Enter plate number to search: ";
cin >> plate;
vector<Vehicle> records = loadRecords();
bool found = false;
for (int i = 0; i < records.size(); i++) {
if (records[i].getPlate() == plate) {
cout << "\n--- Vehicle Found ---\n";
cout << "Plate Number : " << records[i].getPlate() 	<< "\n";
cout << "Vehicle Type : " << records[i].getType() 	<< "\n";
cout << "Year	: " << records[i].getYear()	<< "\n";
cout << "Owner Name : " << records[i].getOwner().getName() << "\n";
cout << "Email 	: " << records[i].getOwner().getEmail() << "\n";
cout << "Phone 	: " << records[i].getOwner().getPhone() << "\n";
found = true;
break;
}
}
if (!found) {
cout << "Vehicle with plate " << plate << " not found.\n";
}
}
