#ifndef WORKER_H
#define WORKER_H

#include <iostream>
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
};

#endif