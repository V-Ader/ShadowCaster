#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>
#include "player.hpp"


class Line
{
public:
    enum type
    {
        undefined,
        Wall,
        Ray
    };

    virtual sf::Vector2f getBegin() =0;
    virtual sf::Vector2f getEnd() =0;
    virtual Line::type getType() =0;
};

class Wall : public Line
{
private:
    sf::Vector2f begin; //the begin vector of the wall
    sf::Vector2f end; //the end vector of the wall
    std::vector <sf::Vector2f> points; 
        //it may contains some extra points, f.e intersections points

    bool belong(sf::Vector2f point, sf::Vector2f b_line, sf::Vector2f e_line);
    void addPoint(sf::Vector2f point);
    
public:
    Wall(sf::Vector2f begin, sf::Vector2f end);
    ~Wall();

    sf::Vector2f getBegin() override;
    sf::Vector2f getEnd() override;
    std::vector<sf::Vector2f> getPoints();
    Line::type getType() override;

    void addIntersectionPoint(Wall wall); 
        //it adds extra points to the `points` vector. 
        //Thanks to that we can create a ray to these points
};

class Ray : public Line
{
private:
    Player* source; //the begin of every ray is the same. it is the source.
        //thanks that i will not have to update evey single starting point
    sf::Vector2f end;   //current end. it can change because of intersection with walls
    sf::Vector2f destiny; //the cosnt point of end. it will not change. ever.

    bool belong(sf::Vector2f point, sf::Vector2f b_line, sf::Vector2f e_line);

public:
    Ray();
    Ray(Player* source, sf::Vector2f end);
    ~Ray();

    sf::Vector2f getBegin() override;
    sf::Vector2f getEnd() override;

    void setEnd(sf::Vector2f end);
    void setDestiny(sf::Vector2f dest);

    Line::type getType() override; //im not sure if i'm gonna use that

    sf::Vector2f getFirstIntPoint(std::vector< Line* > walls);
        //it returns the closest point of intersection.
        //if there is no int. then returns it's destiny.

    double qDistance(sf::Vector2f point1, sf::Vector2f point2);

    double getAngle(sf::Vector2f start, sf::Vector2f end);
};

