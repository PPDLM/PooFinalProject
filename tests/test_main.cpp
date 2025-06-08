#include "Curator.hpp"
#include "AudiovisContent.hpp"

int main() {
    Curator theCurator;
    std::string welcomeInputinMain = theCurator.welcomeMenu();
    theCurator.catalogMenu(welcomeInputinMain);
    return 0;
}