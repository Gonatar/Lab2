#include "Worker.h"

Worker::Worker() : fio(nullptr), post(nullptr), year(0){
    cout << "Default constructor for Worker" << endl;
}

Worker::Worker(const char* fio, const char* post, int year) : year(year){
    cout << "Parameterized constructor for Worker" << endl;
    
    this->fio = new char[strlen(fio) + 1];
    strcpy(this->fio, fio);
    
    this->post = new char[strlen(post) + 1];
    strcpy(this->post, post);
}

Worker::Worker(const Worker& other) : year(other.year){
    cout << "Copy constructor for Worker" << endl;
    
    if(other.fio) {
        fio = new char[strlen(other.fio) + 1];
        strcpy(fio, other.fio);
    } else {
        fio = nullptr;
    }
    
    if(other.post) {
        post = new char[strlen(other.post) + 1];
        strcpy(post, other.post);
    } else {
        post = nullptr;
    }
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
    delete[] this->fio;
    this->fio = new char[strlen(fio) + 1];
    strcpy(this->fio, fio);
}

void Worker::setPost(const char* post) {
    delete[] this->post;
    this->post = new char[strlen(post) + 1];
    strcpy(this->post, post);
}

void Worker::setYear(const int year) {
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
    is.ignore();
    is.getline(buffer, 256);
    worker.setFio(buffer);
    
    cout << "Enter post: ";
    is.getline(buffer, 256);
    worker.setPost(buffer);
    
    cout << "Enter year: ";
    int y;
    is >> y;
    worker.setYear(y);
    
    return is;
}