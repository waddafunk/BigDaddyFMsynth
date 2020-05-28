/*
  ==============================================================================

    WavePainter.cpp
    Created: 25 May 2020 2:21:53pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WavePainter.h"

//==============================================================================
WavePainter::WavePainter()
{
    setFramesPerSecond(60); // [1]
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WavePainter::WavePainter(int x, int y)
{
    setFramesPerSecond(60); // [1]
    xPos = x;
    yPos = y;
    height = 800;
    width = 700;
}

WavePainter::WavePainter(int x, int y, int height, int width)
{
    xPos = x;
    yPos = y;
    this->height = height;
    this->width = width;
}



WavePainter::~WavePainter(){
    wavePainted.clear();
}

void WavePainter::setMyBounds()
{
    this->setBounds(xPos, yPos, width, height);
}

void WavePainter::paint (Graphics& g)
{

}

void WavePainter::resized()
{
  //  this->setBounds(xPos,yPos,width, height);
    

}
float WavePainter::getFreq() const
{
    return freq;
}

void WavePainter::setFreq(float freq)
{
    this->freq = freq;
}


float WavePainter::getHeight() const
{
    return height;
}

void WavePainter::setHeight(float height)
{
    this->height = height;
}

float WavePainter::getWidth() const
{
    return width;
}

void WavePainter::setWidth(float width)
{
    this->width = width;
}

int WavePainter::getXPos() const
{
    return xPos;
}

void WavePainter::setXPos(int xPos)
{
    this->xPos = xPos;
}

int WavePainter::getYPos() const
{
    return yPos;
}

void WavePainter::setYPos(int yPos)
{
    this->yPos = yPos;
}

void WavePainter::setTriggered(bool isTriggered)
{
    this->triggered = isTriggered;
}

void WavePainter::pushPainted(float pos)
{
    wavePainted.push_back(pos);
}

