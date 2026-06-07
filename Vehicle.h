#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
#include <vector>
using namespace std;
// Base class
class User {
private:
string name;
string email;
string phone;
public:
User();
User(string n, string e, string p);
string getName();
string getEmail();
string getPhone();
void setName(string n);
void setEmail(string e);
void setPhone(string p);
};
// Derived class
class VehicleOwner : public User {
public:
VehicleOwner();
VehicleOwner(string n, string e, string p);
};
// Vehicle class associated with VehicleOwner
class Vehicle {
private:
string plateNumber;
string vehicleType;
int year;
VehicleOwner owner;
public:
Vehicle();
Vehicle(string plate, string type, int yr, VehicleOwner o);
string getPlate();
string getType();
int getYear();
VehicleOwner getOwner();
};
// Validation functions
bool isValidEmail(string email);
bool isValidPhone(string phone);
bool isValidPlate(string plate);
// File functions
void saveRecord(Vehicle v);
vector<Vehicle> loadRecords();
// Menu functions
void addRecord();
void displayAll();
void searchRecord();
#endif
