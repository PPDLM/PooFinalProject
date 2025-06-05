#include "Curator.hpp"
#include "AudiovisContent.hpp"

int main() {
	Curator theCurator;
	std::string welcomeInputinMain = theCurator.welcomeMenu();
	theCurator.catalogMenu(theCurator, welcomeInputinMain);
	return 0;
}