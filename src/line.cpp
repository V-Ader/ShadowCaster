#include "line.hpp"

Wall::Wall(sf::Vector2f begin, sf::Vector2f end)
:begin(begin), end(end)
{

}

Wall::~Wall() {

}

sf::Vector2f Wall::getBegin()
{
    return this->begin;
}
sf::Vector2f Wall::getEnd()
{
    return this->end;
}
std::vector<sf::Vector2f> Wall::getPoints()
{
    return this->points;
}

Line::type Wall::getType() {
    return Line::type::Wall;
}

void Wall::addPoint(sf::Vector2f point)
{
    this->points.push_back(point);
};

void Wall::addIntersectionPoint(Wall wall)
{
    int x1, x2, x3, x4, y1, y2, y3, y4, t, divider;
    double x, y;

    y2 = this->end.y;
    y1 = this->begin.y;
    x1 = this->begin.x;
    x2 = this->end.x;

    x3 = wall.getBegin().x;
    x4 = wall.getEnd().x;

    y3 = wall.getBegin().y;
    y4 = wall.getEnd().y;

    t = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4);

    divider = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);

    if(divider == 0) return;

    x = x1 + t * (x2-x1) / divider;
    y = y1 +  t *(y2-y1) / divider;

    if(belong(sf::Vector2f(x,y), wall.getBegin(), wall.getEnd()) &&
        belong(sf::Vector2f(x,y), this->begin, this->end ))
    {
        this->points.push_back(sf::Vector2f(x,y));
    }

    return;
}

bool Wall::belong(sf::Vector2f point, sf::Vector2f b_line, sf::Vector2f e_line)
{

    if( (point.x > b_line.x && point.x > e_line.x) || (point.x < b_line.x && point.x < e_line.x) )
        return false;
    if( (point.y > b_line.y && point.y > e_line.y) || (point.y < b_line.y && point.y < e_line.y) )
        return false;
  

    return true;
}

Ray::Ray()
{
}

Ray::Ray(Player* source, sf::Vector2f end)
:source(source), end(end), destiny(end)
{
}

Ray::~Ray() {}

sf::Vector2f Ray::getBegin()
{
    return this->source->getPosition();
}
sf::Vector2f Ray::getEnd()
{
    return this->end;
}


Line::type Ray::getType()
{
    return Line::type::Ray;
}

sf::Vector2f Ray::getFirstIntPoint(std::vector< Line* > walls)
{
    int x1, x2, x3, x4, y1, y2, y3, y4, t, divider;
    double x, y;
    std::vector <sf::Vector2f> points = {this->destiny};
    y2 = this->destiny.y;
    y1 = this->source->getPosition().y;
    x1 = this->source->getPosition().x;
    x2 =this->destiny.x;
    
    for(int i = 0; i < (int) walls.size(); ++i)
    {
        x3 = walls.at(i)->getBegin().x;
        x4 = walls.at(i)->getEnd().x;

        y3 = walls.at(i)->getBegin().y;
        y4 = walls.at(i)->getEnd().y;

        t = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4);

        divider = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);

        if(divider == 0) continue;

        x = x1 + t * (x2-x1) / divider;
        y = y1 +  t *(y2-y1) / divider;

        if(!belong(sf::Vector2f(x,y), walls.at(i)->getBegin(), walls.at(i)->getEnd()) || 
            !belong(sf::Vector2f(x,y), this->source->getPosition(), this->destiny ))
        {
            continue;
        }
        else
        {
            points.push_back(sf::Vector2f(x,y));
        }
    }
    double min_d = qDistance(this->getBegin(), points.at(0));
    sf::Vector2f min_point = points.at(0);
    double d;
    for(auto point : points)
    {
        d = qDistance(this->getBegin(), point);

        if(d < min_d)
        {
            min_point = point;
            min_d = d;
        }

    }

    return min_point;
}

void Ray::setEnd(sf::Vector2f end)
{
    this->end = end;
}

void Ray::setDestiny(sf::Vector2f dest)
{
    this->destiny = dest;
}

bool Ray::belong(sf::Vector2f point, sf::Vector2f b_line, sf::Vector2f e_line)
{

    if( (point.x > b_line.x && point.x > e_line.x) || (point.x < b_line.x && point.x < e_line.x) )
        return false;
    if( (point.y > b_line.y && point.y > e_line.y) || (point.y < b_line.y && point.y < e_line.y) )
        return false;
  

    return true;
}

double Ray::qDistance(sf::Vector2f point1, sf::Vector2f point2)
{
    return (point1.x-point2.x)*(point1.x-point2.x) + (point1.y-point2.y)*(point1.y-point2.y);
}

double Ray::getAngle(sf::Vector2f start, sf::Vector2f end)
{
    return atan2(end.y - start.y, end.x - start.x);
}