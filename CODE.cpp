#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Base Class Person
class Person {
protected:
    string name, phone;
public:
    Person() {}
    Person(string n, string p) : name(n), phone(p) {}
    virtual void display() {
        cout << "Name: " << name << "\nPhone: " << phone << endl;
    }
};

// Customer Class
class Customer : public Person {
private:
    int roomNumber;
    int days;
    float rentPerDay;
public:
    Customer() {}
    Customer(string n, string p, int r, int d, float rent)
        : Person(n, p), roomNumber(r), days(d), rentPerDay(rent) {}

    int getRoom() { return roomNumber; }
    float getBill() { return days * rentPerDay; }

    void display() override {
        cout << "\nCustomer Name: " << name
             << "\nPhone: " << phone
             << "\nRoom Number: " << roomNumber
             << "\nDays Stayed: " << days
             << "\nTotal Bill: " << getBill()
             << "\n---------------------------\n";
    }

    string toFile() {
        return name + "," + phone + "," + to_string(roomNumber) + "," +
               to_string(days) + "," + to_string(rentPerDay) + "\n";
    }

    static Customer fromFile(string line) {
        string n, p;
        int r, d;
        float rent;
        size_t pos = 0;
        vector<string> tokens;
        while ((pos = line.find(",")) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        n = tokens[0];
        p = tokens[1];
        r = stoi(tokens[2]);
        d = stoi(tokens[3]);
        rent = stof(tokens[4]);

        return Customer(n, p, r, d, rent);
    }
};

// Hotel Management Class
class Hotel {
private:
    vector<Customer> customers;
    const string filename = "customers.txt";
public:
    Hotel() { loadFromFile(); }

    bool isRoomAvailable(int room) {
        for (auto &c : customers) {
            if (c.getRoom() == room)
                return false;
        }
        return true;
    }

    void addCustomer() {
        string name, phone;
        int room, days;
        float rent;
        cout << "\nEnter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter Room Number: ";
        cin >> room;
        if (!isRoomAvailable(room)) {
            cout << "Room is already booked!\n";
            return;
        }
        cout << "Enter Number of Days: ";
        cin >> days;
        cout << "Enter Rent per Day: ";
        cin >> rent;

        Customer c(name, phone, room, days, rent);
        customers.push_back(c);
        saveToFile();
        cout << "Booking Successful!\n";
    }

    void displayCustomers() {
        cout << "\n--- Current Customers ---\n";
        if (customers.empty()) cout << "No Customers Found!\n";
        for (auto &c : customers) c.display();
    }

    void checkoutCustomer() {
        int room;
        cout << "Enter Room Number to Checkout: ";
        cin >> room;

        bool found = false;
        for (size_t i = 0; i < customers.size(); i++) {
            if (customers[i].getRoom() == room) {
                cout << "Bill Amount: " << customers[i].getBill() << endl;
                customers.erase(customers.begin() + i);
                saveToFile();
                cout << "Checkout Successful!\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "Room not found!\n";
    }

    void saveToFile() {
        ofstream file(filename);
        for (auto &c : customers) file << c.toFile();
        file.close();
    }

    void loadFromFile() {
        customers.clear();
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            if (!line.empty()) customers.push_back(Customer::fromFile(line));
        }
        file.close();
    }
};

// Admin Login System
bool adminLogin() {
    string pass;
    cout << "Enter Admin Password: ";
    cin >> pass;
    return (pass == "admin123"); // Set your password here
}

// Main Function
int main() {
    if (!adminLogin()) {
        cout << "Access Denied!\n";
        return 0;
    }

    Hotel h;
    int choice;
    do {
        cout << "\n--- HOTEL MANAGEMENT SYSTEM ---\n";
        cout << "1. Book Room\n";
        cout << "2. View All Customers\n";
        cout << "3. Checkout Customer\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: h.addCustomer(); break;
            case 2: h.displayCustomers(); break;
            case 3: h.checkoutCustomer(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

