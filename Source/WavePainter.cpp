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



WavePainter::~WavePainter(){
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

