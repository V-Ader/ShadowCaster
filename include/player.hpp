#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Vector2f position;
    int speed;

public:
    Player(sf::Vector2f position);
    ~Player();

    void setPosition(sf::Vector2f position, bool relative);
    sf::Vector2f getPosition();
    int getSpeed();

};