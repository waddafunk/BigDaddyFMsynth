/*
  ==============================================================================

    Coordinate.h
    Created: 25 May 2020 11:54:53pm
    Author:  daveg

  ==============================================================================
*/


#include "math.h"
#pragma once

class Coordinate{

public:
    Coordinate();
    Coordinate(float x, float y);

    float getX() const;
    void setX(float x);

    float getY() const;
    void setY(float y);

    void setCoordinates(float x, float y);

    float computeDistanceFrom(Coordinate point);

private:
    float x;
    float y;



};
