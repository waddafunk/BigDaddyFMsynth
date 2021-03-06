/*
  ==============================================================================

    MyNotchFilter.cpp
    Created: 27 May 2020 8:53:45pm
    Author:  jacop

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyNotchFilter.h"

//==============================================================================
MyNotchFilter::MyNotchFilter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MyNotchFilter::MyNotchFilter(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    this->width = w;
    this->height = h;
}

MyNotchFilter::~MyNotchFilter()
{
}

void MyNotchFilter::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MyNotchFilter", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void MyNotchFilter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
