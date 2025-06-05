#ifndef AUDIOVISCONTENT_HPP
#define AUDIOVISCONTENT_HPP

#include <iostream>
#include <string>

class AudiovisContent {
private:
    // Attributes
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
    AudiovisContent(int newId, const std::string& newName, int newHrDuration, int newMinDuration, int newSecDuration, int newRating, const std::string& newGenre);


    // Destructor
    ~AudiovisContent();

    // Getter and setter (id)
    int getId() const;
    void setId(int id);

    // Getter and setter (name)
    const std::string& getName() const;
    void setName(const std::string& name);

    // Getter and setter (hrDuration)
    int getHrDuration() const;
    void setHrDuration(int hrDuration);

    // Getter and setter (minDuration)
    int getMinDuration() const;
    void setMinDuration(int minDuration);

    // Getter and setter (secDuration)
    int getSecDuration() const;
    void setSecDuration(int secDuration);

    // Getter and setter (rating)
    int getRating() const;
    void setRating(int rating);

    // Getter and setter (genre)
    const std::string& getGenre() const;
    void setGenre(const std::string& genre);

    // Methods
    void addRating(int addedRating);
    void showOverallRating();
};

#endif // AUDIOVISCONTENT_HPP