#include "Menu.h"
#include <limits>

using namespace std;

void Menu::run() {
    int choice;
    
    do {
        system("cls");
        displayMainMenu();
        choice = getInput(0, 6);
        
        try {
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
                    editWorker();
                    break;
                case 5:
                    deleteWorker();
                    break;
                case 6:
                    processFile();
                    break;
                case 0:
                    cout << "Exiting..." << endl;
                    break;
            }
        } catch (const WorkerException& e) {
            cout << "\nERROR: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "\nUNEXPECTED ERROR: " << e.what() << endl;
        } catch (...) {
            cout << "\nUNKNOWN ERROR occurred" << endl;
        }
        
        if (choice != 0) {
            enter();
        }
    } while(choice != 0);
}

void Menu::displayMainMenu() {
    cout << "\n=== Worker Management ===" << endl;
    cout << "Workers in database: " << WorkerControl.getCount() << endl;
    cout << "1. Add worker" << endl;
    cout << "2. Display all workers" << endl;
    cout << "3. Find experienced workers" << endl;
    cout << "4. Edit worker" << endl;
    cout << "5. Delete worker" << endl;
    cout << "6. Process text file (2nd task)" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}

void Menu::addWorker() {
    system("cls");
    cout << "\n=== Add New Worker ===" << endl;
    WorkerControl.addWorker();
    WorkerControl.sortByFIO();
}

void Menu::editWorker() {
    system("cls");
    cout << "\n=== Edit Worker ===" << endl;
    
    if (WorkerControl.getCount() == 0) {
        cout << "No workers to edit." << endl;
        return;
    }
    
    try {
        WorkerControl.displayAll();
        
        cout << "\nEnter worker number to edit (1-" << WorkerControl.getCount() 
             << ") or 0 to cancel: ";
        
        int index = getInput(0, WorkerControl.getCount());
        
        if (index == 0) {
            cout << "Edit cancelled." << endl;
            return;
        }
        
        WorkerControl.editWorker(index - 1);
        cout << "Worker edited successfully." << endl;
        
    } catch (const WorkerException& e) {
        cout << "Cannot edit: " << e.what() << endl;
    }
}

void Menu::displayAllWorkers() {
    system("cls");
    cout << "\n=== All Workers ===" << endl;
    WorkerControl.displayAll();
}

void Menu::findExperiencedWorkers() {
    system("cls");
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
    system("cls");
    cout << "\n=== Delete Worker ===" << endl;
    
    if (WorkerControl.getCount() == 0) {
        cout << "No workers to delete." << endl;
        return;
    }
    
    try {
        WorkerControl.displayAll();
        
        cout << "Enter worker number to delete (1-" << WorkerControl.getCount() << "): ";
        int index = getInput(1, WorkerControl.getCount());
        WorkerControl.deleteWorker(index - 1);
    } catch (const WorkerException& e) {
        cout << "Cannot delete: " << e.what() << endl;
    }
}

void Menu::processFile() {
    system("cls");
    cout << "\n=== Process Text File ===" << endl;
    cout << "This function reads 'text.txt' and displays only sentences without commas." << endl;
    
    try {
        FileProcessor::processFileWithoutCommas();
    } catch (const WorkerException& e) {
        cout << "Error: " << e.what() << endl;
        cout << "Please create a file named 'text.txt' in the program directory." << endl;
    } catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
    }
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