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
    addKnobSection(xPos, yPos, width, height, 2);
}

FilterGui::FilterGui(int x, int y)
{
    xPos = x;
    yPos = y;
    height = 40;
    width = 40;
    addKnobSection(xPos, yPos, width, height, 2);
}

FilterGui::FilterGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;

    addMyFilters(width, height * 3 / 4);
    addKnobSection(0, 3 * height / 4, width, height/4, 8);

}

FilterGui::~FilterGui()
{
    for (auto& knobSection : knobSections) {
        delete knobSection;
    }

    for (auto& filter : myFilters) {
        delete filter;
    }
}

void FilterGui::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component


}

void FilterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterGui::addMyFilters(int w, int h) {
    myFilters.push_back(new FilterGraph(0, 0, w, h));

    for (auto& filter : myFilters) {
        filter->setMyBounds();
        addAndMakeVisible(filter);
    }
}

void FilterGui::addMyFilter(FilterGraph* painter) {
    myFilters.push_back(painter);
}
