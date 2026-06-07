#include <iostream>
#include "vehicle.h"
using namespace std;
int main() {
int choice;
do {
cout << "\n=== Vehicle Registration System ===\n";
cout << "1. Add new record\n";
cout << "2. Display all records\n";
cout << "3. Search by plate number\n";
cout << "4. Exit\n";
cout << "Enter choice: ";
cin >> choice;
if 	(choice == 1) addRecord();
else if (choice == 2) displayAll();
else if (choice == 3) searchRecord();
else if (choice == 4) cout << "Goodbye!\n";
else cout << "Invalid choice. Try again.\n";
} while (choice != 4);
return 0;
}
