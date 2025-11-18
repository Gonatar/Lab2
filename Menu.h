#ifndef MENU_H
#define MENU_H

#include "WorkerControl.h"

class Menu {
private:
    WorkerControl WorkerControl;
    
    void displayMainMenu();
    void addWorker();
    void displayAllWorkers();
    void sortWorkers();
    void findExperiencedWorkers();
    void deleteWorker();
    void enter();
    int getInput(int min, int max);

public:
    void run();
};

#endif