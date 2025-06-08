#include "Episode.hpp"
#include <numeric> // para std::accumulate
#include <iostream> // para advertencia

// Constructor por defecto
Episode::Episode()
    : id(0), title(""), duration(0) {}

// Constructor parametrizado
Episode::Episode(int newId, const std::string& newTitle, int newDuration)
    : id(newId), title(newTitle), duration(newDuration) {}

// Getters
int Episode::getId() const {
    return id;
}

const std::string& Episode::getTitle() const {
    return title;
}

int Episode::getDuration() const {
    return duration;
}

const std::vector<int>& Episode::getRatings() const {
    return ratings;
}

// Setters
void Episode::setId(int newId) {
    id = newId;
}

void Episode::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Episode::setDuration(int newDuration) {
    duration = newDuration;
}

void Episode::setRatings(const std::vector<int>& newRatings) {
    ratings = newRatings;
}

// Agregar una calificación (con validación y advertencia)
void Episode::addRating(int addedRating) {
    if (addedRating >= 1 && addedRating <= 5) {
        ratings.push_back(addedRating);
    } else {
        std::cerr << "Advertencia: La calificación debe estar entre 1 y 5. Valor recibido: " << addedRating << std::endl;
    }
}

// Calcular el promedio de ratings
float Episode::getAverageRating() const {
    if (ratings.empty()) return 0.0f;
    float sum = std::accumulate(ratings.begin(), ratings.end(), 0);
    return sum / ratings.size();
}

// Serialización a JSON
nlohmann::json Episode::toJson() const {
    nlohmann::json j;
    j["id"] = id;
    j["title"] = title;
    j["duration"] = duration;
    j["ratings"] = ratings;
    return j;
}

// Crear episodio desde JSON
Episode Episode::fromJson(const nlohmann::json& j) {
    Episode ep(
        j.at("id").get<int>(),
        j.at("title").get<std::string>(),
        j.at("duration").get<int>()
    );
    if (j.contains("ratings")) {
        ep.setRatings(j.at("ratings").get<std::vector<int>>());
    }
    return ep;
}
