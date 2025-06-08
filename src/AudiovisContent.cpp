#include "AudiovisContent.hpp"
#include <iostream>

// Default constructor
AudiovisContent::AudiovisContent() = default;

// Constructor parametrizado con 'type' como primer argumento
AudiovisContent::AudiovisContent(const std::string& newType, int newId, const std::string& newName,
                                 int newHrDuration, int newMinDuration, int newSecDuration,
                                 int newRating, const std::string& newGenre)
    : type(newType), id(newId), name(newName), hrDuration(newHrDuration),
      minDuration(newMinDuration), secDuration(newSecDuration),
      rating(newRating), genre(newGenre) {}

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

// Getter and setter (rating)
int AudiovisContent::getRating() const { return rating; }
void AudiovisContent::setRating(int newRating) { rating = newRating; }

// Getter and setter (genre)
const std::string& AudiovisContent::getGenre() const { return genre; }
void AudiovisContent::setGenre(const std::string& newGenre) { genre = newGenre; }

// Métodos opcionales
void AudiovisContent::addRating(int addedRating) {
    std::cout << "AudiovisContent::addRating not implemented yet." << std::endl;
}
void AudiovisContent::showOverallRating() {
    std::cout << "AudiovisContent::showOverallRating not implemented yet." << std::endl;
}