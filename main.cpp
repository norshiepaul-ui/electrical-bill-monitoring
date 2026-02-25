#include <iostream>
#include <fstream>
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

    string getName() { return name; }
    double getPower() { return power; }
    double getHours() { return hours; }

    void setPower(double p) { power = p; }
    void setHours(double h) { hours = h; }

    void display() {
        cout << left << setw(15) << name
             << setw(12) << power
             << setw(10) << hours
             << setw(10) << calculateEnergy()
             << endl;
    }

    void saveToFile(ofstream &outFile) {
        outFile << name << "," << power << "," << hours << endl;
    }

    void loadFromFile(string line) {
        int pos1 = line.find(",");
        int pos2 = line.find(",", pos1 + 1);

        name = line.substr(0, pos1);
        power = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        hours = stod(line.substr(pos2 + 1));
    }
};

Appliance appliances[MAX_APPLIANCES];
int applianceCount = 0;

void loadFromFile() {
    ifstream inFile("appliances.txt");
    string line;

    while (getline(inFile, line) && applianceCount < MAX_APPLIANCES) {
        appliances[applianceCount].loadFromFile(line);
        applianceCount++;
    }

    inFile.close();
}

void saveToFile() {
    ofstream outFile("appliances.txt");

    for (int i = 0; i < applianceCount; i++) {
        appliances[i].saveToFile(outFile);
    }

    outFile.close();
    cout << "Data saved successfully.\n";
}

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

    cout << "\n------------------------------------------------------\n";
    cout << left << setw(15) << "Name"
         << setw(12) << "Power(W)"
         << setw(10) << "Hours"
         << setw(10) << "kWh"
         << endl;
    cout << "------------------------------------------------------\n";

    for (int i = 0; i < applianceCount; i++) {
        appliances[i].display();
    }
}

void updateAppliance() {
    if (applianceCount == 0) {
        cout << "No appliances to update.\n";
        return;
    }

    string updateName;
    cout << "Enter appliance name to update: ";
    cin.ignore();
    getline(cin, updateName);

    bool found = false;

    for (int i = 0; i < applianceCount; i++) {
        if (appliances[i].getName() == updateName) {

            double newPower, newHours;

            cout << "Enter new power rating (Watts): ";
            cin >> newPower;
            while (newPower <= 0) {
                cout << "Power must be greater than 0. Enter again: ";
                cin >> newPower;
            }

            cout << "Enter new daily usage hours (0 - 24): ";
            cin >> newHours;
            while (newHours < 0 || newHours > 24) {
                cout << "Usage hours must be between 0 and 24. Enter again: ";
                cin >> newHours;
            }

            appliances[i].setPower(newPower);
            appliances[i].setHours(newHours);

            cout << "Appliance updated successfully.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Appliance not found.\n";
    }
}

void menu() {
    cout << "\n===== ELECTRICAL LOAD MONITORING SYSTEM =====\n";
    cout << "1. Register Appliance\n";
    cout << "2. View Appliances\n";
    cout << "3. Update Appliance\n";
    cout << "4. Save Data\n";
    cout << "5. Exit\n";
    cout << "Choose option: ";
}

int main() {

    loadFromFile();

    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: registerAppliance(); break;
            case 2: viewAppliances(); break;
            case 3: updateAppliance(); break;
            case 4: saveToFile(); break;
            case 5:
                saveToFile();
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
