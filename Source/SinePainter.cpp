/*
  ==============================================================================

    SinePainter.cpp
    Created: 23 May 2020 4:13:23pm
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
    xPos = 0;
    yPos = 0;
    height = 40;
    width = 40;

}

SinePainter::SinePainter(int x, int y)
{
    xPos = x;
    yPos = y;
    height = 40;
    width = 40;
}

SinePainter::SinePainter(int x, int y, int width, int height){
    xPos = x;
    yPos = y;
    this->width = width;
    this->height = height;
}


SinePainter::~SinePainter()
{
}


void SinePainter::paint(Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::white);

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    auto numberOfDots = width; // [1]
    Path spinePath;         // [2]
    int amplitude = (height-40)/2;
    float freq = 0.02f;

    //clearWavePainted();

    for (auto i = 0; i < numberOfDots; ++i) // [3]
    {
        float pos = height / 2.0f + amplitude * std::cos(i * freq + 8 * freq * getFrameCounter());
        if (getTriggered())
            pos = height / 2.0f + amplitude * std::cos(i * freq);
        Point<float> p(i * width / (numberOfDots - 2), pos);

        //pushPainted(pos / height);

        if (i == 0)
            spinePath.startNewSubPath(p);  // if this is the first point, start a new path..
        else
            spinePath.lineTo(p);           // ...otherwise add the next point
    }



    // draw an outline around the path that we have created
    g.strokePath(spinePath, PathStrokeType(4.0f)); // [4]


}

void SinePainter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
