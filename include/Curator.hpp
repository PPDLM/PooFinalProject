#ifndef CURATOR_HPP
#define CURATOR_HPP

#include "AudiovisContent.hpp"
#include <list>
#include <memory>
#include <string>

class Curator {
private:
    // Ahora la lista es de punteros inteligentes para polimorfismo real
    std::list<std::shared_ptr<AudiovisContent>> catalog;

public:
    // Constructores
    Curator();
    Curator(const std::list<std::shared_ptr<AudiovisContent>>& newCatalog);

    // Destructor
    ~Curator();

    // Getter y setter para el catálogo
    const std::list<std::shared_ptr<AudiovisContent>>& getCatalog() const;
    void setCatalog(const std::list<std::shared_ptr<AudiovisContent>>& newCatalog);

    // Métodos de interacción
    std::string welcomeMenu();
    void catalogMenu(const std::string& welcomeInputInCatalog);
    void showCatalog();
    void readCatalog();
    void showEpisodesOfSeries() const;
    void catalogActionsMenu(const std::vector<std::shared_ptr<AudiovisContent>>& filtered);
    void saveCatalog() const;
};

#endif // CURATOR_HPP