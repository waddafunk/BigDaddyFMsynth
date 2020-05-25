/*
  ==============================================================================

    SinePainter.cpp
    Created: 25 May 2020 5:56:54pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SinePainter.h"

//==============================================================================
SinePainter::SinePainter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SinePainter::SinePainter(int x, int y){
    xPos = x;
    yPos = y;
    height = 300;
    width = 300;
}

SinePainter::~SinePainter()
{
}

void SinePainter::paint (Graphics& g)
{

    //g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));


    auto numberOfDots = getWidth(); // [1]
    Path spinePath;         // [2]
    int amplitude = 150;
    freq = 0.02;

    for (auto i = 0; i < numberOfDots; ++i) // [3]
    {

        Point<float> p(i * getWidth() / (numberOfDots - 2),
            getHeight() / 2.0f + amplitude * std::cos(i * freq /*/ numberOfDots*/ + 8 * freq /*/ numberOfDots*/ * getFrameCounter()));

        if (i == 0)
            spinePath.startNewSubPath(p);  // if this is the first point, start a new path..
        else
            spinePath.lineTo(p);           // ...otherwise add the next point
    }



    // draw an outline around the path that we have created
    g.strokePath(spinePath, PathStrokeType(4.0f)); // [4]

    repaint();

}

void SinePainter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
