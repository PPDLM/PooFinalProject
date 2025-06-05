#ifndef CURATOR_HPP
#define CURATOR_HPP

#include "AudiovisContent.hpp"
#include <list>

class Curator {
private:
    // Attribute
    std::list<AudiovisContent> catalog;

public:
    // Constructors
    Curator();
    Curator(const std::list<AudiovisContent>& newCatalog);

    // Destructor
    ~Curator();

    // Getter and setter (Catalog)
    const std::list<AudiovisContent>& getCatalog() const;
    void setCatalog(const std::list<AudiovisContent>& newCatalog);

    // Methods
    std::string welcomeMenu();
    void catalogMenu(Curator theCurator, std::string welcomeInputinCatalog);
    void showCatalog();
};

#endif // CURATOR_HPP