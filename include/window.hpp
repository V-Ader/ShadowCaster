#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "line.hpp"
#include "system.hpp"

class Window
{
private:
    std::vector<System*> sys;
	sf::RenderWindow window;
    sf::Sprite spr;
    sf::Sprite player_sprite;
    sf::Texture bcgTexture;
    sf::Texture shadowTexture;
    sf::Texture playerTexture;
    bool debug_mode;
    bool mouse_mode;

    void linesRenderer();
    void areaRenderer();
    void pointRenderer();
    void playerRenderer();

public:
	Window(System* system);

    bool isOpen();

    void update();

    void render();

    void handleEvents();

};
