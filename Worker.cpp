#include "Worker.h"
#include <iostream>
#include <limits>

Worker::Worker() : fio(nullptr), post(nullptr), year(0){
    cout << "Default constructor for Worker" << endl;
}

Worker::Worker(const char* fio, const char* post, int year) : year(year){
    cout << "Parameterized constructor for Worker" << endl;
    
    if (!fio || strlen(fio) == 0) {
        throw WorkerException("Invalid FIO: cannot be null or empty");
    }
    if (!post || strlen(post) == 0) {
        throw WorkerException("Invalid post: cannot be null or empty");
    }
    if (year < 1900 || year > 2025) {
        throw WorkerException("Invalid year: must be between 1900 and 2025");
    }
    
    this->fio = new char[strlen(fio) + 1];
    strcpy(this->fio, fio);
    
    this->post = new char[strlen(post) + 1];
    strcpy(this->post, post);
}

Worker::Worker(const Worker& other) : year(other.year){
    cout << "Copy constructor for Worker" << endl;
    
    if (!other.fio) {
        throw WorkerException("Cannot copy: source FIO is null");
    }
    
    fio = new char[strlen(other.fio) + 1];
    strcpy(fio, other.fio);
    
    if (!other.post) {
        delete[] fio;
        throw WorkerException("Cannot copy: source post is null");
    }
    
    post = new char[strlen(other.post) + 1];
    strcpy(post, other.post);
}

Worker::~Worker(){
    cout << "Destructor for Worker (";
    if(fio) cout << fio;
    else cout << "empty";
    cout << ")" << endl;
    
    delete[] fio;
    delete[] post;
}

void Worker::setFio(const char* fio) {
    if (!fio || strlen(fio) == 0) {
        throw WorkerException("Invalid FIO: cannot be null or empty");
    }
    
    delete[] this->fio;
    this->fio = new char[strlen(fio) + 1];
    strcpy(this->fio, fio);
}

void Worker::setPost(const char* post) {
    if (!post || strlen(post) == 0) {
        throw WorkerException("Invalid post: cannot be null or empty");
    }
    
    delete[] this->post;
    this->post = new char[strlen(post) + 1];
    strcpy(this->post, post);
}

void Worker::setYear(const int year) {
    if (year < 1900 || year > 2025) {
        throw WorkerException("Invalid year: must be between 1900 and 2025");
    }
    this->year = year;
}

const char* Worker::getFio() const {
    return fio ? fio : "No Name";
}

const char* Worker::getPost() const {
    return post ? post : "No Post";
}

const int Worker::getYear() const {
    return year;
}

ostream& operator<<(ostream& os, const Worker& worker) {
    os << "FIO: " << worker.getFio() << ", Post: " << worker.getPost() 
       << ", Year: " << worker.getYear();
    return os;
}

istream& operator>>(istream& is, Worker& worker) {
    char buffer[256];
    
    cout << "Enter FIO: ";
    is >> ws;
    is.getline(buffer, 256);
    if (strlen(buffer) == 0) {
        throw WorkerException("FIO cannot be empty");
    }
    worker.setFio(buffer);
    
    cout << "Enter post: ";
    is.getline(buffer, 256);
    if (strlen(buffer) == 0) {
        throw WorkerException("Post cannot be empty");
    }
    worker.setPost(buffer);
    
    cout << "Enter year: ";
    int y;
    is >> y;
    if (is.fail()) {
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        throw WorkerException("Invalid year format");
    }
    worker.setYear(y);
    
    return is;
}