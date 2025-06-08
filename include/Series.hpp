#ifndef SERIES_HPP
#define SERIES_HPP

#include "Episode.hpp"
#include "AudiovisContent.hpp"
#include <list>
#include <string>

class Series : public AudiovisContent {
private:
    std::list<Episode> episodes;

public:
    // Constructor por defecto
    Series() : AudiovisContent("series", 0, "", 0, 0, 0, 0, ""), episodes() {}

    // Constructor parametrizado
    Series(int newId, const std::string& newName, int newHrDuration, int newMinDuration,
           int newSecDuration, int newRating, const std::string& newGenre, const std::list<Episode>& newEpisodes)
        : AudiovisContent("series", newId, newName, newHrDuration, newMinDuration, newSecDuration, newRating, newGenre),
          episodes(newEpisodes) {}

    // Métodos virtuales requeridos
    void show() const override;
    nlohmann::json toJson() const override;

    // Getter y setter de episodios
    const std::list<Episode>& getEpisodes() const;
    void setEpisodes(const std::list<Episode>& newEpisodes);
};

#endif // SERIES_HPP