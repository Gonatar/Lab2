#include "WorkerControl.h"
#include <iostream>
#include <cstring>

using namespace std;

WorkerControl::WorkerControl() : capacity(10), count(0) {
    workers = new Worker*[capacity];
    if (!workers) {
        throw WorkerException("Memory allocation failed for workers array");
    }
}

WorkerControl::~WorkerControl() {
    for (int i = 0; i < count; i++) {
        delete workers[i];
    }
    delete[] workers;
}

void WorkerControl::domExpansion() {
    capacity *= 2;
    Worker** newWorkers = new Worker*[capacity];
    if (!newWorkers) {
        throw WorkerException("Memory allocation failed during expansion");
    }
    
    for (int i = 0; i < count; i++) {
        newWorkers[i] = workers[i];
    }
    delete[] workers;
    workers = newWorkers;
}

void WorkerControl::addWorker() {
    if (count >= capacity) {
        domExpansion();
    }
    
    workers[count] = nullptr;
    try {
        workers[count] = new Worker();
        cin >> *workers[count];
        count++;
        cout << "Worker added. Total: " << count << endl;
    } catch (...) {
        delete workers[count];
        workers[count] = nullptr;
        throw;
    }
}

void WorkerControl::editWorker(int index) {
    if (index < 0 || index >= count) {
        throw WorkerException("Invalid index for editing");
    }
    
    cout << "\n=== Editing Worker #" << (index + 1) << " ===" << endl;
    cout << "Current data: " << *workers[index] << endl;
    
    cout << "\nEnter new data:" << endl;
    
    try {
        cin >> *workers[index];
        cout << "Worker updated successfully." << endl;
    } catch (const WorkerException& e) {
        cout << "Error: " << e.what() << ". Changes not saved." << endl;
        throw;
    }
    
    sortByFIO();
}

void WorkerControl::displayAll() {
    if (count == 0) {
        throw WorkerException("No workers in database");
    }
    
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << *workers[i] << endl;
    }
}

int compareWorkers(const void* a, const void* b) {
    Worker* workerA = *(Worker**)a;
    Worker* workerB = *(Worker**)b;

    return strcmp(workerA->getFio(), workerB->getFio());
}

void WorkerControl::sortByFIO() {
    if (count == 0) {
        throw WorkerException("Cannot sort: no workers in database");
    }
    qsort(workers, count, sizeof(Worker*), compareWorkers);
    cout << "Sorted by FIO" << endl;
}

void WorkerControl::findExperienced(int minYears) {
    if (count == 0) {
        throw WorkerException("No workers in database");
    }
    if (minYears < 0) {
        throw WorkerException("Minimum years cannot be negative");
    }
    
    int currentYear = 2025;
    bool found = false;
    
    cout << "\n=== Workers with experience > " << minYears << " years ===" << endl;
    for (int i = 0; i < count; i++) {
        int experience = currentYear - workers[i]->getYear();
        if (experience > minYears) {
            cout << "- " << workers[i]->getSurname() 
                 << " (Experience: " << experience << " years)" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No workers found with experience > " << minYears << " years" << endl;
    }
}

void WorkerControl::deleteWorker(int index) {
    if (index < 0 || index >= count) {
        throw WorkerException("Invalid index for deletion");
    }
    
    delete workers[index];
    for (int i = index; i < count - 1; i++) {
        workers[i] = workers[i + 1];
    }
    count--;
    workers[count] = nullptr;
    cout << "Worker deleted" << endl;
}

int WorkerControl::getCount() const {
    return count;
}