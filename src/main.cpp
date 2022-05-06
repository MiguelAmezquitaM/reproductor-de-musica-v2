#include <menu.hpp>
#include <iostream>
using namespace RDM;

int main() {
    try {
        mainMenu();
    }
    catch (std::exception* e) {
        std::cout << "Ocurrio un error desconocido\n";
        std::cout << e->what() << "\n";
    }
    return 0;
}
