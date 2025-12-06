#ifndef WORKEREXCEPTION_H
#define WORKEREXCEPTION_H

#include <exception>
#include <cstring>


class WorkerException : public std::exception {
private:
    char* message;
public:
    WorkerException(const char* msg) {
        message = new char[strlen(msg) + 1];
        strcpy(message, msg);
    }
    
    WorkerException(const WorkerException& other) : std::exception(other) {
        message = new char[strlen(other.message) + 1];
        strcpy(message, other.message);
    }
    
    WorkerException& operator=(const WorkerException& other) {
        if (this != &other) {
            delete[] message;
            message = new char[strlen(other.message) + 1];
            strcpy(message, other.message);
        }
        return *this;
    }
    
    ~WorkerException() noexcept override {
        delete[] message;
    }
    
    const char* what() const noexcept override {
        return message;
    }
};

#endif