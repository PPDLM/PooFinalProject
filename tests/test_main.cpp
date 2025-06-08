#include "Curator.hpp"
#include <iostream>

int main() {
    Curator curator;

    // Menú de bienvenida
    std::string input = curator.welcomeMenu();

    // Salir si el usuario así lo decide
    if (input == "e" || input == "E") {
        std::cout << "Hasta pronto." << std::endl;
        return 0;
    }

    // Menú principal del catálogo
    curator.catalogMenu(input);
    return 0;
}
