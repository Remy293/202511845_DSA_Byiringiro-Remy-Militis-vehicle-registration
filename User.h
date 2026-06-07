#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User {
private:
    string name;
    string email;
    string phone;
public:
    User();
    User(string name, string email, string phone);
    void setName(string name);
    void setEmail(string email);
    void setPhone(string phone);
    string getName() const;
    string getEmail() const;
    string getPhone() const;
};
#endif