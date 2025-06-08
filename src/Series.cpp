#include "Series.hpp"
#include <iostream>
#include <numeric>
#include "json.hpp"

// Mostrar información en consola
void Series::show() const {
    std::cout << "=======================" << std::endl;
    std::cout << "Serie: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Duración promedio por episodio: "
              << hrDuration << "h "
              << minDuration << "m "
              << secDuration << "s" << std::endl;
    std::cout << "Género: " << genre << std::endl;
    std::cout << "Calificación promedio: " << getAverageRating() << std::endl;
    std::cout << "Episodios:" << std::endl;
    int epCount = 1;
    for (const auto& ep : episodes) {
        std::cout << "  Episodio " << epCount++ << ": "
                  << ep.getTitle() << " (ID: " << ep.getId()
                  << ", Duración: " << ep.getDuration() << " min, "
                  << "Calificación promedio: " << ep.getAverageRating() << ")" << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

// Calcular promedio de ratings de la serie
float Series::getAverageRating() const {
    if (ratings.empty()) return 0.0f;
    float sum = std::accumulate(ratings.begin(), ratings.end(), 0);
    return sum / ratings.size();
}

// Agregar calificación con validación
void Series::addRating(int addedRating) {
    if (addedRating < 1 || addedRating > 5) {
        std::cerr << "Advertencia: La calificación debe estar entre 1 y 5." << std::endl;
        return;
    }
    ratings.push_back(addedRating);
}

// Convertir objeto a JSON
nlohmann::json Series::toJson() const {
    nlohmann::json j;
    j["type"] = type;
    j["id"] = id;
    j["name"] = name;
    j["hrDuration"] = hrDuration;
    j["minDuration"] = minDuration;
    j["secDuration"] = secDuration;
    j["genre"] = genre;
    j["ratings"] = ratings;
    j["episodes"] = nlohmann::json::array();
    for (const auto& ep : episodes) {
        j["episodes"].push_back(ep.toJson());
    }
    return j;
}

// Getters y setters de episodios
const std::list<Episode>& Series::getEpisodes() const {
    return episodes;
}

void Series::setEpisodes(const std::list<Episode>& newEpisodes) {
    episodes = newEpisodes;
}

std::list<Episode>& Series::getEpisodesRef() {
    return episodes;
}