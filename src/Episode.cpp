#include "Episode.hpp"

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

// Serialización a JSON
nlohmann::json Episode::toJson() const {
    nlohmann::json j;
    j["id"] = id;
    j["title"] = title;
    j["duration"] = duration;
    return j;
}

// Crear episodio desde JSON
Episode Episode::fromJson(const nlohmann::json& j) {
    return Episode(
        j.at("id").get<int>(),
        j.at("title").get<std::string>(),
        j.at("duration").get<int>()
    );
}
