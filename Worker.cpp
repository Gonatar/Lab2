#include "Worker.h"

Worker::Worker() : fio(nullptr), post(nullptr), year(0){

}

Worker::Worker(const char* fio, const char* post, int year) : year(year){

}

Worker::Worker(const Worker& other){

}

Worker::~Worker(){

}