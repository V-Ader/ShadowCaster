#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "line.hpp"

class System
{
private:
    Player* player;
    std::vector <sf::Vector2f> points;
    std::vector< Wall > walls; 
    std::vector< Ray > rays; 
    std::vector< Ray > offRays;

    void generateWalls();
    void loadWallsFromFile();
    void castRays();
public:
	System();
    ~System();

    void addPlayer(Player* newPlayer);
    void addWall(sf::Vector2f begin, sf::Vector2f end);
    void addRay(Player* source, sf::Vector2f end);

    void updateRays();
    bool compareVecs(sf::Vector2f &a, sf::Vector2f &b);

    Player* getPlayer();
    std::vector< Wall > getWalls(); 
    std::vector< Ray > getRays(); 
    std::vector< Ray > getOffRays();
    std::vector <sf::Vector2f> getPoints();

    void setPlayerPosition(sf::Vector2f position, bool relative);
    int getPlayerSpeed();
};