#include "Movie.hpp"
#include <iostream>
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
    std::cout << "Calificación: " << rating << std::endl;
    std::cout << "=======================" << std::endl;
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
    j["rating"] = rating;
    j["genre"] = genre;
    return j;
}