#include "Series.hpp"
#include <iostream>
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
    std::cout << "Calificación: " << rating << std::endl;
    std::cout << "Episodios:" << std::endl;
    int epCount = 1;
    for (const auto& ep : episodes) {
        std::cout << "  Episodio " << epCount++ << ": "
                  << ep.getTitle() << " (ID: " << ep.getId()
                  << ", Duración: " << ep.getDuration() << " min)" << std::endl;
    }
    std::cout << "=======================" << std::endl;
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
    j["rating"] = rating;
    j["genre"] = genre;

    j["episodes"] = nlohmann::json::array();
    for (const auto& ep : episodes) {
        nlohmann::json epJson;
        epJson["id"] = ep.getId();
        epJson["title"] = ep.getTitle();
        epJson["duration"] = ep.getDuration();
        j["episodes"].push_back(epJson);
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
