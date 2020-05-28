/*
  ==============================================================================

    MyHighPass.cpp
    Created: 27 May 2020 8:52:08pm
    Author:  jacop

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyHighPass.h"

//==============================================================================
MyHighPass::MyHighPass()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MyHighPass::MyHighPass(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    this->width = w;
    this->height = h;
}

MyHighPass::~MyHighPass()
{
}

void MyHighPass::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path filterPath;
    Point<float> cutX(getCutoff(), (float)-getResonance() * 2.0f * height * 0.7f + height * 0.5f), 
        preCutX(cutX.getX() - width / 50, height / 2.0f), start(preCutX.getX() * 90 / 100, (float)height),
        endLinear(width, (float)(height / 2)), endp(cutX.getX() + width / 20, (float)height / 2);
    
    if (endp.getX() > width)
        endp.setX(width);
    
    filterPath.startNewSubPath(start);  // if this is the first point, start a new path..
    filterPath.cubicTo(preCutX, cutX, endp);
    filterPath.lineTo(endLinear);


    // draw an outline around the path that we have created
    g.strokePath(filterPath, PathStrokeType(2.0f)); // [4]
    g.fillEllipse(cutX.getX(), height * (1.0f - getResonance()) - 10.0f, 10.0f, 10.0f);

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void MyHighPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
