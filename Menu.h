#ifndef MENU_H
#define MENU_H

#include "WorkerControl.h"
#include "FileProcessor.h"

class Menu {
private:
    WorkerControl WorkerControl;
    
    void displayMainMenu();
    void addWorker();
    void editWorker();
    void displayAllWorkers();
    void findExperiencedWorkers();
    void deleteWorker();
    void processFile();
    void enter();
    int getInput(int min, int max);

public:
    void run();
};

#endif