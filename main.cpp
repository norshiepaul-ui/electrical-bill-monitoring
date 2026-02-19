#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_APPLIANCES = 100;

class Appliance {
private:
    string name;
    double power;
    double hours;

public:
    Appliance() {
        name = "";
        power = 0;
        hours = 0;
    }

    void input() {
        cout << "Enter appliance name: ";
        cin.ignore();
        getline(cin, name);

        while (name.empty()) {
            cout << "Name cannot be empty. Enter again: ";
            getline(cin, name);
        }

        cout << "Enter power rating (Watts): ";
        cin >> power;
        while (power <= 0) {
            cout << "Power must be greater than 0. Enter again: ";
            cin >> power;
        }

        cout << "Enter daily usage hours (0 - 24): ";
        cin >> hours;
        while (hours < 0 || hours > 24) {
            cout << "Usage hours must be between 0 and 24. Enter again: ";
            cin >> hours;
        }
    }

    double calculateEnergy() {
        return (power * hours) / 1000.0;
    }

    void display() {
        cout << left << setw(15) << name
             << setw(12) << power
             << setw(10) << hours
             << setw(10) << calculateEnergy()
             << endl;
    }
};

Appliance appliances[MAX_APPLIANCES];
int applianceCount = 0;

void registerAppliance() {
    if (applianceCount >= MAX_APPLIANCES) {
        cout << "Maximum appliance limit reached.\n";
        return;
    }

    appliances[applianceCount].input();
    applianceCount++;
    cout << "Appliance registered successfully!\n";
}

void viewAppliances() {
    if (applianceCount == 0) {
        cout << "No appliances registered.\n";
        return;
    }

    cout << "\n-----------------------------------------------\n";
    cout << left << setw(15) << "Name"
         << setw(12) << "Power(W)"
         << setw(10) << "Hours"
         << setw(10) << "kWh"
         << endl;
    cout << "-----------------------------------------------\n";

    for (int i = 0; i < applianceCount; i++) {
        appliances[i].display();
    }
}

void menu() {
    cout << "\n===== ELECTRICAL LOAD MONITORING SYSTEM =====\n";
    cout << "1. Register Appliance\n";
    cout << "2. View Appliances\n";
    cout << "3. Exit\n";
    cout << "Choose option: ";
}

int main() {

    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                registerAppliance();
                break;
            case 2:
                viewAppliances();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
