/*
  ==============================================================================

    OscillatorGui.cpp
    Created: 23 May 2020 4:12:58pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorGui.h"

//==============================================================================
OscillatorGui::OscillatorGui()
{


    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    xPos = 0;
    yPos = 0;
    height = 300;
    width = 300;
    addPainters(width, height);
}

OscillatorGui::OscillatorGui(int x, int y)
{
    xPos = x;
    yPos = y;
    addPainters(width, height);
}

OscillatorGui::OscillatorGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;
    addPainters(w,h);
}

OscillatorGui::~OscillatorGui()
{
    for (auto& painter : painters) {
        delete painter;
    }
}

void OscillatorGui::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void OscillatorGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void OscillatorGui::addPainters(int w, int h) {
    painters.push_back(new SquarePainter(0, 0, w/2, h/2));
    painters.push_back(new SinePainter(w/2, 0, w/2, h/2));
    painters.push_back(new TrianglePainter(0, h/2, w/2, h/2));
    painters.push_back(new SawPainter(w/2, h/2, w/2, h/2));

    for (auto& painter : painters) {
        painter->setFramesPerSecond(60);
        painter->setMyBounds();
        addAndMakeVisible(painter);
    }
}


//TODO button to add an oscillator!
//TODO autoresize each waveform each time a new one is added

void OscillatorGui::addPainters(WavePainter * painter) {
    painters.push_back(painter);
    painter->setFramesPerSecond(60);
    painter->setMyBounds();
    addAndMakeVisible(painter);
}
