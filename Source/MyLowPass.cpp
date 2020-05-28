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
    Point<float> start((float)0, (float)(height / 2)), cutX(width / 2, (float)-height / 2), preCutX(cutX.getX() * 99 / 100, height / 2), 
        endLinear(preCutX.getX() / 2, (float)(height / 2)), endp(cutX.getX() + width / 10, (float)height);
    
    if (endp.getX() > width)
        endp.setX(width);
    
    filterPath.startNewSubPath(start);  // if this is the first point, start a new path..
    filterPath.lineTo(endLinear);
    filterPath.cubicTo(preCutX, cutX, endp);


    // draw an outline around the path that we have created
    g.strokePath(filterPath, PathStrokeType(4.0f)); // [4]
    g.fillEllipse(endp.getX() - 20, height / 6, 10.0f, 10.0f);

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void MyLowPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void MyLowPass::setCutoff(float cutOff)
{
    this->cutoff = cutOff;
}

void MyLowPass::setResonance(float resonance)
{
    this->resonance = resonance;
}

void MyLowPass::mouseDown(const MouseEvent& event) {
    triggerDistance = 50;
    float minDistance = 0;
    
    Point<float> mousePos(event.getMouseDownX(), event.getMouseDownY()), cutoffDrag(cutoff, resonance / 2);
    float currentDistance = mousePos.getDistanceFrom(cutoffDrag);
    if (currentDistance < triggerDistance) {
        cutoff = mousePos.getX();
        resonance = mousePos.getY() * 2;
    }

   
}