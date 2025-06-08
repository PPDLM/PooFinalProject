#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "AudiovisContent.hpp"

class Movie : public AudiovisContent {
public:
    // Constructor por defecto
    Movie() : AudiovisContent("movie", 0, "", 0, 0, 0, 0, "") {}

    // Constructor parametrizado
    Movie(int newId, const std::string& newName, int newHrDuration, int newMinDuration,
          int newSecDuration, int newRating, const std::string& newGenre)
        : AudiovisContent("movie", newId, newName, newHrDuration, newMinDuration, newSecDuration, newRating, newGenre) {}

    // Implementación de métodos virtuales puros
    void show() const override;
    nlohmann::json toJson() const override;
};

#endif // MOVIE_HPP