/*
  ==============================================================================

    MyLowPass.cpp
    Created: 27 May 2020 8:51:40pm
    Author:  jacop

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyLowPass.h"
#include "Coordinate.h"

//==============================================================================
MyLowPass::MyLowPass()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MyLowPass::MyLowPass(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    this->width = w;
    this->height = h;
}

MyLowPass::~MyLowPass()
{
}

void MyLowPass::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path filterPath;
    Point<float> start((float)0, (float)(height / 2)), cutX(getCutoff(), (float)-getResonance() * 2.0f * height * 0.7f + height * 0.5f), 
        preCutX(cutX.getX() * 99.0f / 100.0f, height / 2.0f), 
        endLinear(preCutX.getX() * 95.0f / 100.0f, (float)(height / 2)), endp(cutX.getX() + width / 10, (float)height);
    
    if (endp.getX() > width)
        endp.setX(width);
    
    filterPath.startNewSubPath(start);  // if this is the first point, start a new path..
    filterPath.lineTo(endLinear);
    filterPath.cubicTo(preCutX, cutX, endp);


    // draw an outline around the path that we have created
    g.strokePath(filterPath, PathStrokeType(2.0f)); // [4]
    g.fillEllipse(cutX.getX(), height * (1.0f - getResonance()) - 10.0f, 10.0f, 10.0f);

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void MyLowPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void MyLowPass::mouseDown(const MouseEvent& event) {
    float triggerDistance = 50.0;
    float minDistance = 0;

    Point<float> mousePos(event.getMouseDownX(), event.getMouseDownY()), cutoffDrag(getCutoff(), getResonance() / 2);
    float currentDistance = mousePos.getDistanceFrom(cutoffDrag);
    if (currentDistance < triggerDistance) {
        setCutoff(mousePos.getX());
        setResonance(mousePos.getY() * 2);
    }
}