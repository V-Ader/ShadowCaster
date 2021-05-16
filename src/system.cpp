#include "system.hpp"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <fstream>

System::System()
{
    srand(time(NULL));
    this->player = new Player(sf::Vector2f(210,210));

    //this->generateWalls();
    this->loadWallsFromFile();
    this->castRays();
}

System::~System()
{
    delete player;
}

void System::addPlayer(Player* newPlayer)
{
    this->player = newPlayer;
}

void System::addWall(sf::Vector2f begin, sf::Vector2f end)
{
    this->walls.push_back(Wall(begin, end));
}

void System::addRay(Player* source, sf::Vector2f end)
{
    this->rays.push_back(Ray(this->player, end));
}

void System::generateWalls()
{
    int test_k = 720;
    this->addWall(sf::Vector2f(0,0), sf::Vector2f(0,test_k));
    this->addWall(sf::Vector2f(0,0), sf::Vector2f(test_k,0));
    this->addWall(sf::Vector2f(test_k,0), sf::Vector2f(test_k,test_k));
    this->addWall(sf::Vector2f(0,test_k), sf::Vector2f(test_k,test_k));

    for(int i = 0; i < 5; ++i)
    {
        this->addWall(
            sf::Vector2f(rand() % test_k + 0,rand() % test_k + 0),
            sf::Vector2f(rand() % test_k + 0,rand() % test_k + 0));
    }

    for(int i = 0; i < (int) this->walls.size(); ++i)
    {
        for(int j = 0; j < (int) this->walls.size(); ++j)
        {
            this->walls.at(i).addIntersectionPoint(this->walls.at(j));
        }
    }
}

void System::loadWallsFromFile()
{
    this->addWall(sf::Vector2f(0,0), sf::Vector2f(0,720));
    this->addWall(sf::Vector2f(0,0), sf::Vector2f(720,0));
    this->addWall(sf::Vector2f(720,0), sf::Vector2f(720,720));
    this->addWall(sf::Vector2f(0,720), sf::Vector2f(720,720));

    std::ifstream file("../assets/demowalls.txt");
    const int k = 60;
    float buff1, buff2, buff3, buff4;
    while(!file.eof())
    {
        file >> buff1 >> buff2 >> buff3 >> buff4;
        buff1 *= k;
        buff2 *= k;
        buff3 *= k;
        buff4 *= k;
        this->addWall(sf::Vector2f(buff1,buff2), sf::Vector2f(buff3,buff4));
    }
    file.close();
}

void System::castRays()
{

    std::vector< sf::Vector2f > ends;
    bool passer = true;
    for(int i = 0; i < (int) this->walls.size(); ++i)
    {
        for(sf::Vector2f vec : ends)
        {
            if(vec.x == this->walls.at(i).getBegin().x && vec.y == this->walls.at(i).getBegin().y)
            {
                passer = false;
            }
        }
        if(passer)
        {
            ends.push_back(this->walls.at(i).getBegin());
        }
        passer = true;
        for(sf::Vector2f vec : ends)
        {
            if(vec.x == this->walls.at(i).getEnd().x && vec.y == this->walls.at(i).getEnd().y)
            {
                passer = false;
            }
        }
        if(passer)
        {
            ends.push_back(this->walls.at(i).getEnd());
        }

        for(int j = 0; j < (int) this->walls.at(i).getPoints().size(); ++j)
        {
            ends.push_back(this->walls.at(i).getPoints().at(j));
        }
    }

    for(sf::Vector2f end : ends)
    {
        this->addRay(this->player, end);
    }
    
}

void System::updateRays()
{
    const int k = 4;
    sf::Vector2f offset1(k, 0);
    sf::Vector2f offset2(0, k);
    float scale = 1000;
    this->points = {};
    this->offRays = {};
    std::vector< Line* > lines = {};
    for(int i = 0; i < (int) this->walls.size(); ++i)
    {
        lines.push_back(&this->walls.at(i));

    }
    for(int i = 0; i < (int) this->rays.size(); ++i)
    {

        points.push_back(rays.at(i).getFirstIntPoint(lines));
        rays.at(i).setEnd(rays.at(i).getFirstIntPoint(lines));

    }

    Ray tempRay(this->player, sf::Vector2f(0,0));
    Ray t_ray;
    for(int i = 0; i < (int) this->rays.size(); ++i)
    {

        tempRay.setEnd(
            this->player->getPosition() - ((this->player->getPosition() - (rays.at(i).getEnd() + offset1))
            * (float) (scale / sqrt(t_ray.qDistance(this->player->getPosition(), (rays.at(i).getEnd() + offset1)))))
            );
        tempRay.setDestiny(tempRay.getEnd());
        tempRay.setEnd(tempRay.getFirstIntPoint(lines));
        offRays.push_back(tempRay);
        points.push_back(tempRay.getEnd());


        tempRay.setEnd(
            this->player->getPosition() - ((this->player->getPosition() - (rays.at(i).getEnd() - offset1))
            * (float) (scale / sqrt(t_ray.qDistance(this->player->getPosition(), (rays.at(i).getEnd() + offset1)))))
            );
        tempRay.setDestiny(tempRay.getEnd());
        tempRay.setEnd(tempRay.getFirstIntPoint(lines));
        offRays.push_back(tempRay);
        points.push_back(tempRay.getEnd());

        tempRay.setEnd(
            this->player->getPosition() - ((this->player->getPosition() - (rays.at(i).getEnd() + offset2))
            * (float) (scale / sqrt(t_ray.qDistance(this->player->getPosition(), (rays.at(i).getEnd() + offset2)))))
            );
        tempRay.setDestiny(tempRay.getEnd());
        tempRay.setEnd(tempRay.getFirstIntPoint(lines));
        offRays.push_back(tempRay);
        points.push_back(tempRay.getEnd());


        tempRay.setEnd(
            this->player->getPosition() - ((this->player->getPosition() - (rays.at(i).getEnd() - offset2))
            * (float) (scale / sqrt(t_ray.qDistance(this->player->getPosition(), (rays.at(i).getEnd() + offset2)))))
            );
        tempRay.setDestiny(tempRay.getEnd());
        tempRay.setEnd(tempRay.getFirstIntPoint(lines));
        offRays.push_back(tempRay);
        points.push_back(tempRay.getEnd());
    }
    
}

bool System::compareVecs(sf::Vector2f &a, sf::Vector2f &b)
{
    Ray t_ray;
    return t_ray.getAngle(this->player->getPosition(), a) < t_ray.getAngle(this->player->getPosition(), b);
}

Player* System::getPlayer()
{
    return this->player;
}

std::vector< Wall > System::getWalls()
{
    return this->walls;
}

std::vector< Ray > System::getRays()
{
    return this->rays;
}

std::vector< Ray > System::getOffRays()
{
    return this->offRays;
}

std::vector <sf::Vector2f> System::getPoints()
{
    return this->points;
}

void System::setPlayerPosition(sf::Vector2f position, bool relative=false)
{
    this->player->setPosition(position, relative);
}

int System::getPlayerSpeed()
{
    return this->player->getSpeed();
}