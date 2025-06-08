#include "Movie.hpp"
#include <iostream>
#include <numeric>
#include "json.hpp"

// Mostrar información en consola
void Movie::show() const {
    std::cout << "=======================" << std::endl;
    std::cout << "Película: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Duración: "
              << hrDuration << "h "
              << minDuration << "m "
              << secDuration << "s" << std::endl;
    std::cout << "Género: " << genre << std::endl;
    std::cout << "Calificación promedio: " << getAverageRating() << std::endl;
    std::cout << "=======================" << std::endl;
}

// Calcular el promedio de ratings (heredado)
float Movie::getAverageRating() const {
    if (ratings.empty()) return 0.0f;
    float sum = std::accumulate(ratings.begin(), ratings.end(), 0);
    return sum / ratings.size();
}

// Agregar calificación con validación y advertencia
void Movie::addRating(int addedRating) {
    if (addedRating >= 1 && addedRating <= 5) {
        ratings.push_back(addedRating);
    } else {
        std::cout << "[ADVERTENCIA] Calificación inválida. Debe estar entre 1 y 5." << std::endl;
    }
}

// Convertir objeto a JSON
nlohmann::json Movie::toJson() const {
    nlohmann::json j;
    j["type"] = type;
    j["id"] = id;
    j["name"] = name;
    j["hrDuration"] = hrDuration;
    j["minDuration"] = minDuration;
    j["secDuration"] = secDuration;
    j["genre"] = genre;
    j["ratings"] = ratings;
    return j;
}