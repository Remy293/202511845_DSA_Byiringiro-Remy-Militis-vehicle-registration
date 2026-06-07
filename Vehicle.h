#ifndef VEHICLE_H
#define VEHICLE_H

#include "VehicleOwner.h"
#include <string>

class Vehicle {
private:
    string plateNumber;
    string vehicleType;
    int year;
    VehicleOwner owner;

public:
    Vehicle();
    Vehicle(string plateNumber, string vehicleType, int year, VehicleOwner owner);
    string getPlateNumber() const;
    string getVehicleType() const;
    int getYear() const;
    VehicleOwner getOwner() const;
    string toCSV() const;
};
#endif