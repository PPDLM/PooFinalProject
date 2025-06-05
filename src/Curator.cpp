#include "Curator.hpp"
#include "AudiovisContent.hpp"

#include <iostream>

// Constructors
Curator::Curator() = default;
Curator::Curator(const std::list<AudiovisContent>& newCatalog) : catalog(newCatalog) {}

// Destructors
Curator::~Curator() = default;

// Getter and setter (Catalog)
const std::list<AudiovisContent>& Curator::getCatalog() const {
    return catalog;
}
void Curator::setCatalog(const std::list<AudiovisContent>& newCatalog) {
    this->catalog = newCatalog;
}

// Methods
std::string Curator::welcomeMenu() {
    std::string welcomeInput;
    std::cout << "============== ¡Bienvenido a Tecflix! ==============" << std::endl;
    while (true) {
        std::cout << "- Para acceder al catálogo, pulse la tecla ENTER." << std::endl;
        std::cout << "- Para salir, pulse la tecla \"E\"." << std::endl;
        std::cout << "> ";
        std::getline(std::cin, welcomeInput);
        if (welcomeInput.empty() || welcomeInput == "e" || welcomeInput == "E") {
            return welcomeInput;
        } else {
            std::cout << "======= Input inválido, vuelva a intentarlo. =======" << std::endl;
        }
    }
}

void Curator::catalogMenu(Curator theCurator, std::string welcomeInputinCatalog) {
    if (welcomeInputinCatalog.empty()) {
        std::cout << "Cargando cátalogo..." << std::endl;

    } 
    else if (welcomeInputinCatalog == "e" || welcomeInputinCatalog == "E") {
    std::cout << "Saliendo..." << std::endl;
    }
}

void Curator::showCatalog() {

}

void Curator::readCatalog() {
    
}