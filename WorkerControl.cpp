#include "WorkerControl.h"
#include <iostream>
#include <cstring>

using namespace std;

WorkerControl::WorkerControl() : capacity(10), count(0) {
    workers = new Worker*[capacity];
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
    for (int i = 0; i < count; i++) {
        newWorkers[i] = workers[i];
    }
    delete[] workers;
    workers = newWorkers;
}

void WorkerControl::addWorker() {
    if (count >= capacity) domExpansion();
    
    workers[count] = new Worker();
    cin >> *workers[count];
    count++;
    cout << "Worker added. Total: " << count << endl;
}

void WorkerControl::displayAll() {
    if (count == 0) {
        cout << "No workers in database" << endl;
        return;
    }
    
    cout << "\n=== All Workers ===" << endl;
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
    qsort(workers, count, sizeof(Worker*), compareWorkers);
    cout << "Sorted by FIO" << endl;
}

void WorkerControl::findExperienced(int minYears) {
    int currentYear = 2025;
    bool found = false;
    
    cout << "\n=== Workers with experience > " << minYears << " years ===" << endl;
    for (int i = 0; i < count; i++) {
        int experience = currentYear - workers[i]->getYear();
        if (experience > minYears) {
            cout << *workers[i] << " (Experience: " << experience << " years)" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No workers found with experience > " << minYears << " years" << endl;
    }
}

void WorkerControl::deleteWorker(int index) {
    if (index < 0 || index >= count) {
        cout << "Invalid index!" << endl;
        return;
    }
    
    delete workers[index];
    for (int i = index; i < count - 1; i++) {
        workers[i] = workers[i + 1];
    }
    count--;
    cout << "Worker deleted" << endl;
}

int WorkerControl::getCount() const {
    return count;
}