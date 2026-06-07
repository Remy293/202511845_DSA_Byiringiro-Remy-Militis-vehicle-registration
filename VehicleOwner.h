#ifndef VEHICLEOWNER_H
#define VEHICLEOWNER_H
#include "User.h"

class VehicleOwner : public User {
public:
    VehicleOwner();
    VehicleOwner(string name, string email, string phone);
};
#endif