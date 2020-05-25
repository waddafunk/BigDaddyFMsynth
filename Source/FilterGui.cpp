/*
  ==============================================================================

    FilterGui.cpp
    Created: 23 May 2020 4:13:23pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterGui.h"

//==============================================================================
FilterGui::FilterGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FilterGui::FilterGui(int x, int y)
{
    xPos = x;
    yPos = y;
    height = 40;
    width = 40;
}


FilterGui::~FilterGui()
{
}

void FilterGui::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("FilterGui", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text

    

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    auto numberOfDots = getWidth(); // [1]
    Path spinePath;         // [2]
    int amplitude = 150;
    float freq = 0.02f;

    for (auto i = 0; i < numberOfDots; ++i) // [3]
    {

        Point<float> p(i * getWidth() / (numberOfDots - 2),
            getHeight() / 2.0f + amplitude * std::cos(i * freq + 8 * freq * getFrameCounter()));

        if (i == 0)
            spinePath.startNewSubPath(p);  // if this is the first point, start a new path..
        else
            spinePath.lineTo(p);           // ...otherwise add the next point
    }



    // draw an outline around the path that we have created
    g.strokePath(spinePath, PathStrokeType(4.0f)); // [4]


}

void FilterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
