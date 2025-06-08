#include "Curator.hpp"
#include "AudiovisContent.hpp"
#include "Movie.hpp"
#include "Series.hpp"
#include "Episode.hpp"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <memory>

// Constructores y destructores
Curator::Curator() {
    readCatalog();
}
Curator::Curator(const std::list<std::shared_ptr<AudiovisContent>>& newCatalog) : catalog(newCatalog) {}
Curator::~Curator() = default;

// Getters y setters
const std::list<std::shared_ptr<AudiovisContent>>& Curator::getCatalog() const { return catalog; }
void Curator::setCatalog(const std::list<std::shared_ptr<AudiovisContent>>& newCatalog) { catalog = newCatalog; }

// Menú de bienvenida
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

// Menú del catálogo
void Curator::catalogMenu(const std::string& welcomeInputInCatalog) {
    if (welcomeInputInCatalog.empty()) {
        std::cout << "Cargando catálogo..." << std::endl;
        showCatalog();
    } else if (welcomeInputInCatalog == "e" || welcomeInputInCatalog == "E") {
        std::cout << "Saliendo..." << std::endl;
    }
}

// Mostrar el catálogo
void Curator::showCatalog() const {
    if (catalog.empty()) {
        std::cout << "El catálogo está vacío." << std::endl;
        return;
    }
    for (const auto& content : catalog) {
        content->show();
    }
}

// Leer el catálogo desde JSON
void Curator::readCatalog() {
    std::ifstream file("../data/catalog.json");
    if (!file) {
        std::cerr << "No se pudo abrir catalog.json" << std::endl;
        return;
    }
    nlohmann::json j;
    file >> j;
    catalog.clear();

    for (const auto& item : j) {
        std::string type = item.at("type");
        if (type == "movie") {
            auto movie = std::make_shared<Movie>(
                item.at("id"),
                item.at("name"),
                item.at("hrDuration"),
                item.at("minDuration"),
                item.at("secDuration"),
                item.at("rating"),
                item.at("genre")
            );
            catalog.push_back(movie);
        } else if (type == "series") {
            std::list<Episode> episodes;
            if (item.contains("episodes")) {
                for (const auto& ep : item.at("episodes")) {
                    episodes.emplace_back(ep.at("id"), ep.at("title"), ep.at("duration"));
                }
            }
            auto series = std::make_shared<Series>(
                item.at("id"),
                item.at("name"),
                item.at("hrDuration"),
                item.at("minDuration"),
                item.at("secDuration"),
                item.at("rating"),
                item.at("genre"),
                episodes
            );
            catalog.push_back(series);
        }
    }
}