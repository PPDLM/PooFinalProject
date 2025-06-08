#include "AudiovisContent.hpp"
#include "Movie.hpp"
#include "Series.hpp"
#include "Episode.hpp"
#include <iostream>

// Default constructor
AudiovisContent::AudiovisContent() = default;

// Constructor parametrizado SIN rating
AudiovisContent::AudiovisContent(const std::string& newType, int newId, const std::string& newName,
                                 int newHrDuration, int newMinDuration, int newSecDuration,
                                 const std::string& newGenre)
    : type(newType), id(newId), name(newName), hrDuration(newHrDuration),
      minDuration(newMinDuration), secDuration(newSecDuration), genre(newGenre) {}

// Destructor
AudiovisContent::~AudiovisContent() = default;

// Getter and setter (id)
int AudiovisContent::getId() const { return id; }
void AudiovisContent::setId(int newId) { id = newId; }

// Getter and setter (name)
const std::string& AudiovisContent::getName() const { return name; }
void AudiovisContent::setName(const std::string& newName) { name = newName; }

// Getter and setter (hrDuration)
int AudiovisContent::getHrDuration() const { return hrDuration; }
void AudiovisContent::setHrDuration(int newHrDuration) { hrDuration = newHrDuration; }

// Getter and setter (minDuration)
int AudiovisContent::getMinDuration() const { return minDuration; }
void AudiovisContent::setMinDuration(int newMinDuration) { minDuration = newMinDuration; }

// Getter and setter (secDuration)
int AudiovisContent::getSecDuration() const { return secDuration; }
void AudiovisContent::setSecDuration(int newSecDuration) { secDuration = newSecDuration; }

// Getter and setter (genre)
const std::string& AudiovisContent::getGenre() const { return genre; }
void AudiovisContent::setGenre(const std::string& newGenre) { genre = newGenre; }

// Ratings accessors
const std::vector<int>& AudiovisContent::getRatings() const {
    return ratings;
}
void AudiovisContent::setRatings(const std::vector<int>& newRatings) {
    ratings = newRatings;
}

// Métodos para calificaciones
void AudiovisContent::addRating(int addedRating) {
    if (addedRating >= 1 && addedRating <= 5)
        ratings.push_back(addedRating);
}
float AudiovisContent::getAverageRating() const {
    if (ratings.empty()) return 0.0f;
    int sum = 0;
    for (int r : ratings) sum += r;
    return static_cast<float>(sum) / ratings.size();
}

// (opcional) Mostrar el promedio en consola
void AudiovisContent::showOverallRating() {
    std::cout << "Calificación promedio: " << getAverageRating() << std::endl;
}

// Método estático para crear polimórficamente desde JSON
std::shared_ptr<AudiovisContent> AudiovisContent::fromJson(const nlohmann::json& j) {
    std::string type = j.at("type");
    if (type == "movie") {
        auto movie = std::make_shared<Movie>(
            j.at("id").get<int>(),
            j.at("name").get<std::string>(),
            j.at("hrDuration").get<int>(),
            j.at("minDuration").get<int>(),
            j.at("secDuration").get<int>(),
            j.at("genre").get<std::string>()
        );
        if (j.contains("ratings")) {
            movie->setRatings(j.at("ratings").get<std::vector<int>>());
        }
        return movie;
    } else if (type == "series") {
        std::list<Episode> episodes;
        if (j.contains("episodes")) {
            for (const auto& ep : j.at("episodes")) {
                episodes.push_back(Episode::fromJson(ep));
            }
        }
        auto series = std::make_shared<Series>(
            j.at("id").get<int>(),
            j.at("name").get<std::string>(),
            j.at("hrDuration").get<int>(),
            j.at("minDuration").get<int>(),
            j.at("secDuration").get<int>(),
            j.at("genre").get<std::string>(),
            episodes
        );
        if (j.contains("ratings")) {
            series->setRatings(j.at("ratings").get<std::vector<int>>());
        }
        return series;
    }
    return nullptr;
}