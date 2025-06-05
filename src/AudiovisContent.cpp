#include "AudiovisContent.hpp"

#include <iostream>

// Constructors
AudiovisContent::AudiovisContent() = default;
AudiovisContent::AudiovisContent(int newId, const std::string& newName, int newHrDuration, int newMinDuration, int newSecDuration, int newRating, const std::string& newGenre)
    : id(newId), name(newName), hrDuration(newHrDuration), minDuration(newMinDuration), secDuration(newSecDuration), rating(newRating), genre(newGenre) {}

// Destructor
AudiovisContent::~AudiovisContent() = default;

// Getter and setter (id)
int AudiovisContent::getId() const {
    return id;
}
void AudiovisContent::setId(int newId) {
    this->id = newId;
}

// Getter and setter (name)
const std::string& AudiovisContent::getName() const {
    return name;
}
void AudiovisContent::setName(const std::string& newName) {
    this->name = newName;
}

// Getter and setter (hrDuration)
int AudiovisContent::getHrDuration() const {
    return hrDuration;
}
void AudiovisContent::setHrDuration(int newHrDuration) {
    this->hrDuration = newHrDuration;
}

// Getter and setter (minDuration)
int AudiovisContent::getMinDuration() const {
    return minDuration;
}
void AudiovisContent::setMinDuration(int newMinDuration) {
    this->minDuration = newMinDuration;
}

// Getter and setter (secDuration)
int AudiovisContent::getSecDuration() const {
    return secDuration;
}
void AudiovisContent::setSecDuration(int newSecDuration) {
    this->secDuration = newSecDuration;
}

// Getter and setter (rating)
int AudiovisContent::getRating() const {
    return rating;
}
void AudiovisContent::setRating(int newRating) {
    this->rating= newRating;
}

// Getter and setter (genre)
const std::string& AudiovisContent::getGenre() const {
    return genre;
}
void AudiovisContent::setGenre(const std::string& newGenre) {
    this->genre = newGenre;
}

// Methods
void AudiovisContent::addRating(int addedRating) {
    std::cout<<"AudiovisContent::addRating not implemented yet."<<std::endl;
}
void AudiovisContent::showOverallRating() {
    std::cout<<"AudiovisContent::showOverallRating not implemented yet."<<std::endl;
}