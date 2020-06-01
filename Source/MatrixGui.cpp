/*
  ==============================================================================

    MatrixGui.cpp
    Created: 23 May 2020 4:13:06pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MatrixGui.h"

//==============================================================================
MatrixGui::MatrixGui()
{
    xPos = 0;
    yPos = 0;
    height = 40;
    width = 40;
    addKnobSection(0, 0 * height / 4, width, height / 4, 8);
    addKnobSection(0, 1 * height / 4, width, height / 4, 8);
    addKnobSection(0, 2 * height / 4, width, height / 4, 8);
    addKnobSection(0, 3 * height / 4, width, height / 4, 8);

}

MatrixGui::MatrixGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;
    addKnobSection(0, 0 * height / 8, width, height / 8, 8, tSection::matrix, 0);
    addKnobSection(0, 1 * height / 8, width, height / 8, 8, tSection::matrix, 1);
    addKnobSection(0, 2 * height / 8, width, height / 8, 8, tSection::matrix, 2);
    addKnobSection(0, 3 * height / 8, width, height / 8, 8, tSection::matrix, 3);
    addKnobSection(0, 4 * height / 8, width, height / 8, 8, tSection::matrix, 4);
    addKnobSection(0, 5 * height / 8, width, height / 8, 8, tSection::matrix, 5);
    addKnobSection(0, 6 * height / 8, width, height / 8, 8, tSection::matrix, 6);
    addKnobSection(0, 7 * height / 8, width, height / 8, 8, tSection::matrix, 7);
}

MatrixGui::~MatrixGui()
{
    for (auto& knobSection : knobSections) {
        delete knobSection;
    }
}

void MatrixGui::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey.darker(0.8));
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

  }

void MatrixGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
