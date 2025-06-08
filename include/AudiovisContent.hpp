#ifndef AUDIOVISCONTENT_HPP
#define AUDIOVISCONTENT_HPP

#include <iostream>
#include <string>
#include <memory>
#include "json.hpp"

class AudiovisContent {
protected:
    // Attributes (protected for derived classes)
    std::string type;
    int id;
    std::string name;
    int hrDuration;
    int minDuration;
    int secDuration;
    int rating;
    std::string genre;

public:
    // Constructors
    AudiovisContent();
    AudiovisContent(const std::string& newType,int newId, const std::string& newName, int newHrDuration, int newMinDuration, int newSecDuration, int newRating, const std::string& newGenre);

    // Destructor
    virtual ~AudiovisContent(); // Polymorphic destructor

    // Getters and setters
    const std::string& getType() const { return type; }

    int getId() const;
    void setId(int id);

    const std::string& getName() const;
    void setName(const std::string& name);

    int getHrDuration() const;
    void setHrDuration(int hrDuration);

    int getMinDuration() const;
    void setMinDuration(int minDuration);

    int getSecDuration() const;
    void setSecDuration(int secDuration);

    int getRating() const;
    void setRating(int rating);

    const std::string& getGenre() const;
    void setGenre(const std::string& genre);

    // Métodos polimórficos puros (obligatorio override en derivadas)
    virtual void show() const = 0; // Para mostrar en consola
    virtual nlohmann::json toJson() const = 0; // Para convertir a JSON

    // Método estático para crear desde JSON
    static std::shared_ptr<AudiovisContent> fromJson(const nlohmann::json& j);

    // Métodos opcionales
    virtual void addRating(int addedRating);
    virtual void showOverallRating();
};

#endif // AUDIOVISCONTENT_HPP