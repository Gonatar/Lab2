#include "Menu.h"
#include <iostream>
#include <limits>

using namespace std;

void Menu::run() {
    int choice;
    
    do {
        displayMainMenu();
        choice = getInput(0, 5);
        
        switch(choice) {
            case 1:
                addWorker();
                break;
            case 2:
                displayAllWorkers();
                break;
            case 3:
                findExperiencedWorkers();
                break;
            case 4:
                deleteWorker();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
        }
        
        if (choice != 0) {
            enter();
        }
    } while(choice != 0);
}

void Menu::displayMainMenu() {
    cout << "\n=== WorkerControl Management ===" << endl;
    cout << "Workers in database: " << WorkerControl.getCount() << endl;
    cout << "1. Add worker" << endl;
    cout << "2. Display all workers" << endl;
    cout << "3. Find experienced workers" << endl;
    cout << "4. Delete worker" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}

void Menu::addWorker() {
    cout << "\n=== Add New Worker ===" << endl;
    WorkerControl.addWorker();
    WorkerControl.sortByFIO();
}

void Menu::displayAllWorkers() {
    cout << "\n=== All Workers ===" << endl;
    WorkerControl.displayAll();
}

void Menu::findExperiencedWorkers() {
    cout << "\n=== Find Experienced Workers ===" << endl;
    int years;
    cout << "Enter minimum years of experience: ";
    cin >> years;
    if (cin.fail() || years < 0) {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    WorkerControl.findExperienced(years);
}

void Menu::deleteWorker() {
    cout << "\n=== Delete Worker ===" << endl;
    WorkerControl.displayAll();
    
    if (WorkerControl.getCount() == 0) {
        return;
    }
    
    cout << "Enter worker number to delete (1-" << WorkerControl.getCount() << "): ";
    int index = getInput(1, WorkerControl.getCount());
    WorkerControl.deleteWorker(index - 1);
}

void Menu::enter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int Menu::getInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter number between " << min << " and " << max << ": ";
        } else {
            break;
        }
    }
    return input;
}