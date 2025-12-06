#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "WorkerException.h"
using namespace std;

class Worker{
    private:
    char* fio;
    char* post;
    int year;

    public:
    Worker();
    Worker(const char* fio, const char* post, const int year);
    Worker(const Worker& other);

    ~Worker();

    void setFio(const char* fio);
    void setPost(const char* post);
    void setYear(const int year);

    const char* getFio() const;
    const char* getPost() const;
    const int getYear() const;
    const char* getSurname() const;

    friend ostream& operator<<(ostream& os, const Worker& worker);
    friend istream& operator>>(istream& is, Worker& worker);
};

#endif