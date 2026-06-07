#include "User.h"

User::User() {}

User::User(string name, string email, string phone) {
    this->name = name;
    this->email = email;
    this->phone = phone;
}

void User::setName(string name) { this->name = name; }
void User::setEmail(string email) { this->email = email; }
void User::setPhone(string phone) { this->phone = phone; }

string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }