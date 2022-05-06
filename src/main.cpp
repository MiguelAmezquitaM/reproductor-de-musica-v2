#include <menu.hpp>
#include <iostream>
using namespace RDM;

int main() {
    try {
        mainMenu();
    }
    catch (...) {
        std::cout << "Ocurrio un error desconocido\n";
    }
    return 0;
}
