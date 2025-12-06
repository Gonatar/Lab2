#ifndef WorkerControl_H
#define WorkerControl_H

#include "Worker.h"
#include "WorkerException.h"

class WorkerControl {
private:
    Worker** workers;
    int capacity;
    int count;
    
    void domExpansion();

public:
    WorkerControl();
    ~WorkerControl();
    
    void addWorker();
    void editWorker(int index);
    void displayAll();
    void sortByFIO();
    void findExperienced(int minYears);
    void deleteWorker(int index);
    int getCount() const;
};

#endif