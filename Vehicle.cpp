#include "Vehicle.h"
#include <sstream>

Vehicle::Vehicle() { year = 0; }

Vehicle::Vehicle(string plateNumber, string vehicleType, int year, VehicleOwner owner) {
    this->plateNumber = plateNumber;
    this->vehicleType = vehicleType;
    this->year = year;
    this->owner = owner;
}

string Vehicle::getPlateNumber() const { return plateNumber; }
string Vehicle::getVehicleType() const { return vehicleType; }
int Vehicle::getYear() const { return year; }
VehicleOwner Vehicle::getOwner() const { return owner; }

string Vehicle::toCSV() const {
    stringstream ss;
    ss << plateNumber << "," << vehicleType << "," << year << ","
       << owner.getName() << "," << owner.getEmail() << ","
       << owner.getPhone();
    return ss.str();
}