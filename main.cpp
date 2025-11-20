#include "Menu.h"
#include "WorkerException.h"
#include <iostream>

int main() {
    try {
        Menu menu;
        menu.run();
    } catch (const WorkerException& e) {
        std::cout << "Fatal WorkerException: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Fatal std::exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Fatal unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}