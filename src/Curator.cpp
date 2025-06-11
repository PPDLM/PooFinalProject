#include "Curator.hpp"
#include "AudiovisContent.hpp"
#include "Movie.hpp"
#include "Series.hpp"
#include "Episode.hpp"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <limits>
#include <opencv2/opencv.hpp> // Para imágenes
#include <cstdlib> // Para abrir videos

// Función auxiliar para validar entrada de enteros
int inputInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Intente de nuevo.\n";
        }
    }
}

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
void Curator::showCatalog() {
    if (catalog.empty()) {
        std::cout << "El catálogo está vacío." << std::endl;
        return;
    }

    while (true) {
        std::cout << "\n=== MENÚ CATÁLOGO ===\n";
        std::cout << "1) Mostrar todo por orden de ID\n";
        std::cout << "2) Mostrar solo películas\n";
        std::cout << "3) Mostrar solo series\n";
        std::cout << "4) Mostrar por género\n";
        std::cout << "5) Mostrar episodios de una serie\n";
        std::cout << "6) Salir del catálogo\n";
        int option = inputInt("Seleccione una opción (1-6): ");

        std::vector<std::shared_ptr<AudiovisContent>> filtered;

        if (option == 2) {
            for (const auto& content : catalog)
                if (content->getType() == "movie")
                    filtered.push_back(content);
            if (filtered.empty()) {
                std::cout << "No hay películas en el catálogo." << std::endl;
                continue;
            }
        } else if (option == 3) {
            for (const auto& content : catalog)
                if (content->getType() == "series")
                    filtered.push_back(content);
            if (filtered.empty()) {
                std::cout << "No hay series en el catálogo." << std::endl;
                continue;
            }
        } else if (option == 4) {
            std::cout << "Ingrese el género a filtrar: ";
            std::string genreInput;
            std::getline(std::cin, genreInput);
            for (const auto& content : catalog)
                if (content->getGenre() == genreInput)
                    filtered.push_back(content);
            if (filtered.empty()) {
                std::cout << "No hay contenido del género \"" << genreInput << "\" en el catálogo." << std::endl;
                continue;
            }
        } else if (option == 5) {
            showEpisodesOfSeries();
            continue;
        } else if (option == 6) {
            break;
        } else {
            // Opción 1 o inválida: todo por orden de ID
            filtered.assign(catalog.begin(), catalog.end());
        }

        // Mostrar el resultado
        std::cout << "\n==== Catálogo ====\n";
        for (const auto& content : filtered)
            content->show();

        // Submenú de acciones sobre el catálogo filtrado
        catalogActionsMenu(filtered);
        std::cout << "¡Gracias por usar Tecflix!" << std::endl;
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
                item.at("genre")
            );
            // Leer ratings del json si existen
            if (item.contains("ratings")) {
                movie->setRatings(item.at("ratings").get<std::vector<int>>());
            }
            catalog.push_back(movie);
        } else if (type == "series") {
            std::list<Episode> episodes;
            if (item.contains("episodes")) {
                for (const auto& ep : item.at("episodes")) {
                    Episode episode(
                        ep.at("id"),
                        ep.at("title"),
                        ep.at("duration")
                    );
                    // Leer ratings de episodio si existen
                    if (ep.contains("ratings")) {
                        episode.setRatings(ep.at("ratings").get<std::vector<int>>());
                    }
                    episodes.push_back(episode);
                }
            }
            auto series = std::make_shared<Series>(
                item.at("id"),
                item.at("name"),
                item.at("hrDuration"),
                item.at("minDuration"),
                item.at("secDuration"),
                item.at("genre"),
                episodes
            );
            // Leer ratings de la serie si existen
            if (item.contains("ratings")) {
                series->setRatings(item.at("ratings").get<std::vector<int>>());
            }
            catalog.push_back(series);
        }
    }
}

// Guardar el catálogo en JSON
void Curator::saveCatalog() const {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& content : catalog) {
        j.push_back(content->toJson());
    }
    std::ofstream file("../data/catalog.json");
    if (!file) {
        std::cerr << "No se pudo guardar el catálogo." << std::endl;
        return;
    }
    file << j.dump(4);
}

// Mostrar episodios de una serie
void Curator::showEpisodesOfSeries() const {
    int option = inputInt("\nBuscar serie por:\n1) ID\n2) Nombre\nSeleccione opción: ");

    std::shared_ptr<Series> foundSeries = nullptr;
    if (option == 1) {
        int id = inputInt("Ingrese el ID de la serie: ");
        for (const auto& content : catalog) {
            if (content->getType() == "series" && content->getId() == id) {
                foundSeries = std::dynamic_pointer_cast<Series>(content);
                break;
            }
        }
    } else {
        std::string name;
        std::cout << "Ingrese el nombre de la serie: ";
        std::getline(std::cin, name);
        for (const auto& content : catalog) {
            if (content->getType() == "series" && content->getName() == name) {
                foundSeries = std::dynamic_pointer_cast<Series>(content);
                break;
            }
        }
    }

    if (!foundSeries) {
        std::cout << "Serie no encontrada." << std::endl;
        return;
    }

    std::cout << "\nEpisodios de la serie: " << foundSeries->getName() << std::endl;
    int epNum = 1;
    for (const auto& ep : foundSeries->getEpisodes()) {
        std::cout << "Episodio " << epNum++ << ": ";
        std::cout << "Título: " << ep.getTitle();
        std::cout << ", Duración: " << ep.getDuration() << " min";
        std::cout << ", Calificación promedio: " << ep.getAverageRating();
        std::cout << std::endl;
    }
}
void showImage(const std::string& imagePath) {
    cv::Mat img = cv::imread(imagePath);
    if (img.empty()) {
        std::cout << "Error al cargar la imagen: " << imagePath << std::endl;
        return;
    }
    cv::imshow("Imagen", img);
    cv::waitKey(0); // Esperar a que el usuario cierre la imagen
}

void playVideo(const std::string& videoPath) {
    std::string command = "ffplay -autoexit -nodisp " + videoPath; // FFmpeg para reproducir video
    system(command.c_str()); // Ejecutar el comando
}

// Submenú de acciones sobre el catálogo filtrado
void Curator::catalogActionsMenu(const std::vector<std::shared_ptr<AudiovisContent>>& filtered) {
    if (filtered.empty()) return;

    while (true) {
        std::cout << "\n--- ¿Qué desea hacer? ---\n";
        std::cout << "1) Calificar un contenido\n";
        std::cout << "2) Ver calificación promedio\n";
        std::cout << "3) Mostrar video real (no implementado)\n";
        std::cout << "4) Mostrar imagen real (no implementada)\n";
        std::cout << "5) Volver al menú anterior\n";
        int subOption = inputInt("Seleccione una opción (1-5): ");

        if (subOption == 1) { // Calificar
            int id = inputInt("Ingrese el ID del contenido que desea calificar: ");

            auto it = std::find_if(filtered.begin(), filtered.end(), [&](const std::shared_ptr<AudiovisContent>& content) {
                return content->getId() == id;
            });
            if (it == filtered.end()) {
                std::cout << "ID no encontrado.\n";
                continue;
            }

            if ((*it)->getType() == "movie") {
                int rating = inputInt("Ingrese la calificación (1-5): ");
                if (rating < 1 || rating > 5) {
                    std::cout << "Calificación inválida. Debe estar entre 1 y 5.\n";
                    continue;
                }
                (*it)->addRating(rating);
                saveCatalog();
                std::cout << "Calificación agregada.\n";
            } else if ((*it)->getType() == "series") {
                int tipo = inputInt("¿Desea calificar la serie en general (1) o un episodio en específico (2)? ");
                auto seriesPtr = std::dynamic_pointer_cast<Series>(*it);
                if (tipo == 1) {
                    int rating = inputInt("Ingrese la calificación para la serie (1-5): ");
                    if (rating < 1 || rating > 5) {
                        std::cout << "Calificación inválida. Debe estar entre 1 y 5.\n";
                        continue;
                    }
                    seriesPtr->addRating(rating);
                    saveCatalog();
                    std::cout << "Calificación agregada a la serie.\n";
                } else if (tipo == 2) {
                    int epId = inputInt("Ingrese el ID del episodio: ");
                    bool found = false;
                    for (auto& ep : seriesPtr->getEpisodesRef()) {
                        if (ep.getId() == epId) {
                            int rating = inputInt("Ingrese la calificación para el episodio (1-5): ");
                            if (rating < 1 || rating > 5) {
                                std::cout << "Calificación inválida. Debe estar entre 1 y 5.\n";
                                found = true; // Para no mostrar "ID de episodio no encontrado"
                                break;
                            }
                            ep.addRating(rating);
                            saveCatalog();
                            std::cout << "Calificación agregada al episodio.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        std::cout << "ID de episodio no encontrado.\n";
                }
            }
        } else if (subOption == 2) { // Ver promedio
            int id = inputInt("Ingrese el ID del contenido: ");

            auto it = std::find_if(filtered.begin(), filtered.end(), [&](const std::shared_ptr<AudiovisContent>& content) {
                return content->getId() == id;
            });
            if (it == filtered.end()) {
                std::cout << "ID no encontrado.\n";
                continue;
            }

            if ((*it)->getType() == "movie") {
                std::cout << "Promedio de calificación: " << (*it)->getAverageRating() << std::endl;
            } else if ((*it)->getType() == "series") {
                int tipo = inputInt("¿Desea ver el promedio general de la serie (1) o de un episodio (2)? ");
                auto seriesPtr = std::dynamic_pointer_cast<Series>(*it);
                if (tipo == 1) {
                    std::cout << "Promedio de la serie: " << seriesPtr->getAverageRating() << std::endl;
                } else if (tipo == 2) {
                    int epId = inputInt("Ingrese el ID del episodio: ");
                    bool found = false;
                    for (const auto& ep : seriesPtr->getEpisodes()) {
                        if (ep.getId() == epId) {
                            std::cout << "Promedio del episodio: " << ep.getAverageRating() << std::endl;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        std::cout << "ID de episodio no encontrado.\n";
                }
            }
        } else if (subOption == 3) {
            std::cout << "Opción nueva! Por lo tanto ten en cuenta que tenemos solamente videos disponibles para: \nPELÍCULAS: Anora y Nosferatu.\nSERIES: Broklyn 99 y Stranger Things\n";
            int id = inputInt("Ingrese el ID del contenido: ");
            std::string videoPath = "videos/" + std::to_string(id) + ".mp4"; // Ruta estándar para video
            playVideo(videoPath);
        } else if (subOption == 4) {
            std::cout << "Opción nueva! Por lo tanto ten en cuenta que tenemos solamente imágenes disponibles para: \nPELÍCULAS: Interestelar, El conjuro, Anastasia, Y tu mamá también y Dune.\nSERIES: Friends, La Casa del Dragón, Mentes Criminales, Peppa Pig y Rick y Morty\n";
            int id = inputInt("Ingrese el ID del contenido: ");
            std::string imagePath = "images/" + std::to_string(id) + ".jpg"; // Ruta estándar para imagen
            showImage(imagePath);
        } else if (subOption == 5) {
            break; // Volver al menú anterior
        }
    }
}
