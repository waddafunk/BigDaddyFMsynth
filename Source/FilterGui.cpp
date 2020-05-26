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
    xPos = 0;
    yPos = 0;
    height = 0;
    width = 0;
    addKnobSection(xPos, yPos, width, height, direction::horizontal, 2);
}

FilterGui::FilterGui(int x, int y)
{
    xPos = x;
    yPos = y;
    height = 40;
    width = 40;
    addKnobSection(xPos, yPos, width, height, direction::horizontal, 2);
}

FilterGui::FilterGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;
    addKnobSection(xPos, yPos, width, height, direction::horizontal, 2);
}

FilterGui::~FilterGui()
{
    for (auto& knobSection : knobSections) {
        delete knobSection;
    }
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


}

void FilterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

