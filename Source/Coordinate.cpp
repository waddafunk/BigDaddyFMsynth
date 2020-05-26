/*
  ==============================================================================

    Coordinate.cpp
    Created: 25 May 2020 11:54:53pm
    Author:  daveg

  ==============================================================================
*/

#include "Coordinate.h"

Coordinate::Coordinate()
{
    x = 0;
    y = 0;
}

Coordinate::Coordinate(float x, float y)
{
    this->x = x;
    this->y = y;
}


float Coordinate::getX() const
{
    return x;
}

void Coordinate::setX(float x)
{
    if(x>=0){
        this->x = x;
    }else{
        this->x = 0;
    }
}

float Coordinate::getY() const
{
    return y;
}

void Coordinate::setY(float y)
{
    if (y >= 0) {
        this->y = y;
    }
    else {
        this->y = 0;
    }
}

void Coordinate::setCoordinates(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Coordinate::setCoordinates(Coordinate pos)
{
    this->x = pos.getX();
    this->y = pos.getY();
}

float Coordinate::computeDistanceFrom(Coordinate point)
{
    return sqrt(pow(this->x - point.getX(), 2) + pow(this->y - point.getY(), 2));
}

bool Coordinate::hasHigherXThan(Coordinate point)
{
    if(this->x>point.getX())
        return true;
    return false;
}

bool Coordinate::hasHigherYThan(Coordinate point)
{
    if (this->y > point.getY())
        return true;
    return false;
}

bool Coordinate::hasLowerYThan(Coordinate point)
{
    if (this->y < point.getY())
        return true;
    return false;
}


bool Coordinate::hasLowerXThan(Coordinate point)
{
    if (this->x < point.getX())
        return true;
    return false;
}

