#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Event {
    string name, date, place, organizer;
};

//  Add a new event
void addEvent() {
    ofstream file("events.txt", ios::app);
    Event e;
    cin.ignore();
    cout << "\nEnter Event Name: ";
    getline(cin, e.name);
    cout << "Enter Event Date (DD/MM/YYYY): ";
    getline(cin, e.date);
    cout << "Enter Event Place: ";
    getline(cin, e.place);
    cout << "Enter Organizer Name: ";
    getline(cin, e.organizer);

    file << e.name << "," << e.date << "," << e.place << "," << e.organizer << endl;
    file.close();

    cout << "\n Event added successfully!\n";
}

//  Show all events
void showEvents() {
    ifstream file("events.txt");
    if (!file) {
        cout << "\n No events found yet!\n";
        return;
    }

    string line;
    int number = 0;
    cout << "\n===== ALL EVENTS =====\n";

    while (getline(file, line)) {
        stringstream ss(line);
        Event e;
        getline(ss, e.name, ',');
        getline(ss, e.date, ',');
        getline(ss, e.place, ',');
        getline(ss, e.organizer, ',');

        cout << "\nEvent #" << ++number << "\n";
        cout << "Name: " << e.name << "\nDate: " << e.date
             << "\nPlace: " << e.place << "\nOrganizer: " << e.organizer << "\n";
        cout << "---------------------------\n";
    }

    if (number == 0)
        cout << "\n No events to show!\n";

    file.close();
}

//  Find an event by name
void searchEvent() {
    ifstream file("events.txt");
    if (!file) {
        cout << "\n No events found!\n";
        return;
    }

    string searchName;
    cin.ignore();
    cout << "\nEnter Event Name to Search: ";
    getline(cin, searchName);

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        Event e;
        getline(ss, e.name, ',');
        getline(ss, e.date, ',');
        getline(ss, e.place, ',');
        getline(ss, e.organizer, ',');

        if (e.name == searchName) {
            cout << "\n Event Found!\n";
            cout << "Name: " << e.name << "\nDate: " << e.date
                 << "\nPlace: " << e.place << "\nOrganizer: " << e.organizer << "\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\n Sorry, no event found with that name.\n";

    file.close();
}

//Update event information
void updateEvent() {
    ifstream file("events.txt");
    if (!file) {
        cout << "\n No events found to update!\n";
        return;
    }

    string searchName;
    cin.ignore();
    cout << "\nEnter Event Name to Update: ";
    getline(cin, searchName);

    ofstream temp("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        Event e;
        getline(ss, e.name, ',');
        getline(ss, e.date, ',');
        getline(ss, e.place, ',');
        getline(ss, e.organizer, ',');

        if (e.name == searchName) {
            cout << "\n Event Found! Enter new details below:\n";
            cout << "Enter New Date: ";
            getline(cin, e.date);
            cout << "Enter New Place: ";
            getline(cin, e.place);
            cout << "Enter New Organizer: ";
            getline(cin, e.organizer);
            found = true;
        }

        temp << e.name << "," << e.date << "," << e.place << "," << e.organizer << endl;
    }

    file.close();
    temp.close();
    remove("events.txt");
    rename("temp.txt", "events.txt");

    if (found)
        cout << "\n Event updated successfully!\n";
    else
        cout << "\n Event not found!\n";
}

//Delete an event
void deleteEvent() {
    ifstream file("events.txt");
    if (!file) {
        cout << "\n No events found to delete!\n";
        return;
    }

    string searchName;
    cin.ignore();
    cout << "\nEnter Event Name to Delete: ";
    getline(cin, searchName);

    ofstream temp("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        Event e;
        getline(ss, e.name, ',');
        getline(ss, e.date, ',');
        getline(ss, e.place, ',');
        getline(ss, e.organizer, ',');

        if (e.name == searchName) {
            found = true;
            continue; // skip (delete)
        }

        temp << e.name << "," << e.date << "," << e.place << "," << e.organizer << endl;
    }

    file.close();
    temp.close();
    remove("events.txt");
    rename("temp.txt", "events.txt");

    if (found)
        cout << "\n Event deleted successfully!\n";
    else
        cout << "\n Event not found!\n";
}

//  Main Menu
int main() {
    int choice;
    do {
        cout << "\n==============================\n";
        cout << "       EVENT MANAGEMENT SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Add Event\n";
        cout << "2. Show All Events\n";
        cout << "3. Search Event\n";
        cout << "4. Update Event\n";
        cout << "5. Delete Event\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEvent(); break;
            case 2: showEvents(); break;
            case 3: searchEvent(); break;
            case 4: updateEvent(); break;
            case 5: deleteEvent(); break;
            case 0: cout << "\n Exiting... Have a nice day!\n"; break;
            default: cout << "\n Wrong choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}