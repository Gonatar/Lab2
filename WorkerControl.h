#ifndef WorkerControl_H
#define WorkerControl_H

#include "Worker.h"

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
    void displayAll();
    void sortByFIO();
    void findExperienced(int minYears);
    void deleteWorker(int index);
    int getCount() const;
};

#endif