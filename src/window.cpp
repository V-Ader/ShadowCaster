#include "window.hpp"
#include <iostream>
Window::Window(System* system)
{
    this->debug_mode = false;
    this->mouse_mode = false;
    this->sys.push_back(system);
	this->window.create(sf::VideoMode(720, 720), "ShadowCaster");
	window.setFramerateLimit(30);
    
    bcgTexture.loadFromFile("../assets/background.png");
    this->spr.setTexture(bcgTexture);
    shadowTexture.loadFromFile("../assets/background2.png");
    this->playerTexture.loadFromFile("../assets/mr5.png");
    this->player_sprite.setTexture(playerTexture);


}

bool Window::isOpen() {
    return this->window.isOpen();
}

void Window::update()
{
    for(auto& system :sys)
    {
        system->updateRays();
    }
}

void Window::handleEvents()
{   
    for(auto& system : sys)
    {
        sf::Mouse mouse;
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) this->window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Left)
                {
                    system->setPlayerPosition(sf::Vector2f(-system->getPlayerSpeed(), 0), true);
                }
                else if(event.key.code == sf::Keyboard::Right)
                {
                    system->setPlayerPosition(sf::Vector2f(system->getPlayerSpeed(), 0), true);
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    system->setPlayerPosition(sf::Vector2f(0,-system->getPlayerSpeed()), true);
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    system->setPlayerPosition(sf::Vector2f(0,system->getPlayerSpeed()), true);
                }
                else if(event.key.code == sf::Keyboard::Space)
                {
                    this->debug_mode = !this->debug_mode;
                    if(this->debug_mode) std::cout << "debug mode on" << std::endl;
                    else std::cout << "debug mode off" << std::endl;
                }
                else if(event.key.code == sf::Keyboard::M)
                {
                    this->mouse_mode = !this->mouse_mode;
                    if(this->mouse_mode) std::cout << "mouse mode on" << std::endl;
                    else std::cout << "mouse mode off" << std::endl;
                }
            }

            if(this->mouse_mode)
                system->setPlayerPosition(
                    sf::Vector2f(mouse.getPosition(this->window).x, mouse.getPosition(this->window).y), false);
            
        }

    }
}

void Window::linesRenderer()
{
    for(auto& system : sys)
    {
        std::vector< Line* > templines;
        sf::VertexArray linesArray (sf::Lines,
            (system->getWalls().size()+system->getRays().size())*2);

        for(int i = 0; i < (int) system->getWalls().size(); ++i)
        {
            templines.push_back(&system->getWalls().at(i));
            linesArray.append(system->getWalls().at(i).getBegin());
            linesArray.append(system->getWalls().at(i).getEnd());
        }

        for(int i = 0; i < (int) system->getRays().size(); ++i)
        {
            templines.push_back(&system->getRays().at(i));
            linesArray.append(system->getRays().at(i).getBegin());
            linesArray.append(system->getRays().at(i).getEnd());
        }
        this->window.draw(linesArray);
    }
}

void Window::areaRenderer()
{
    for(auto& system : sys)
    {
        std::vector <sf::Vector2f> points = system->getPoints();
        int i, j;
        sf::Vector2f temp;  

        for (i = 1; i < (int) points.size(); i++) 
        {  
            temp = points.at(i);  
            j = i - 1;  
            while (j >= 0 && system->compareVecs(points.at(j), temp)) 
            {  
                points.at(j + 1) = points.at(j);  
                j = j - 1;  
            }  
            points.at(j + 1) = temp;  
        } 

        std::vector < sf::VertexArray  > triangles;
        sf::Vector2f start;
        sf::Vector2f end;
        sf::VertexArray  temporary(sf::Triangles, 3);
        temporary[0].position = system->getPlayer()->getPosition();
        temporary[1].position = points[0];
        temporary[2].position = points[1];
        triangles.push_back(temporary);

        for(int i = 1; i < (int) points.size(); i++)
        {   
            temporary[1].position = temporary[2].position;
            temporary[2].position = points.at(i);

            triangles.push_back(temporary);
        }
        temporary[1].position = temporary[2].position;
        temporary[2].position = points.at(0);
        triangles.push_back(temporary);

    
        for(auto triangle : triangles)
        {
            triangle[0].texCoords = triangle[0].position;
            triangle[1].texCoords = triangle[1].position;
            triangle[2].texCoords = triangle[2].position;
            this->window.draw(triangle, &shadowTexture);
        }
    
    }
}

void Window::pointRenderer()
{
    for(auto& system : sys)
    {
        sf::CircleShape renderBody;
        int radius = 3;
        renderBody.setRadius(radius);
        for(auto point : system->getPoints())
        {
            renderBody.setPosition(point - sf::Vector2f(radius, radius));

            this->window.draw(renderBody);
        }
    }
}

void Window::playerRenderer()
{
    
    for(auto& system : sys)
    {
        player_sprite.setPosition(system->getPlayer()->getPosition()-sf::Vector2f(30,30));
        this->window.draw(player_sprite);
    }
}

void Window::render()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(this->spr);
    
    this->areaRenderer();
    if(this->debug_mode)
    {
        this->pointRenderer();
        this->linesRenderer(); 
    }

    this->playerRenderer();
    

    this->window.display();
}