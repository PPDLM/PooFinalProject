#ifndef EPISODE_HPP
#define EPISODE_HPP

#include <string>
#include "json.hpp"

class Episode {
private:
    int id;
    std::string title;
    int duration; // minutos
    std::vector<int> ratings;

public:
    // Constructor por defecto
    Episode();

    // Constructor parametrizado
    Episode(int newId, const std::string& newTitle, int newDuration);

    // Getters
    int getId() const;
    const std::string& getTitle() const;
    int getDuration() const;

    // Ratings accessors
    const std::vector<int>& getRatings() const;
    void setRatings(const std::vector<int>& newRatings);

    // Setters
    void setId(int newId);
    void setTitle(const std::string& newTitle);
    void setDuration(int newDuration);

    // Serialización JSON (opcional, útil si quieres manipular episodios independientes)
    nlohmann::json toJson() const;
    static Episode fromJson(const nlohmann::json& j);
    void addRating(int addedRating);
    float getAverageRating() const;

};

#endif // EPISODE_HPP
