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
    int numOfOsc = 8;
    addPainters(numOfOsc);
    addOscillatorKnobs(numOfOsc);
    addOscillatorLfo(numOfOsc);
}

OscillatorGui::OscillatorGui(int x, int y)
{
    xPos = x;
    yPos = y;
    int numOfOsc = 8;
    addPainters(numOfOsc);
    addOscillatorKnobs(numOfOsc);
    addOscillatorLfo(numOfOsc);
}

OscillatorGui::OscillatorGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;
    int numOfOsc = 8;
    addPainters(numOfOsc);
    addOscillatorKnobs(numOfOsc);
    addOscillatorLfo(numOfOsc);
}

OscillatorGui::~OscillatorGui()
{
    for (auto& painter : painters) {
        delete painter;
    }
    //paintedWaves.clear();
    for (auto& knobSection : knobSections) {
        delete knobSection;
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


void OscillatorGui::addPainters(int n) {
    for (size_t i = 0; i < n; ++i) {
        painters.push_back(new SinePainter(width * 2 / 5 *  2 / 3, height * i / n, width * 2 / 5 * 1 / 3, height / n));
    }

    for (auto& painter : painters) {
        //std::vector<float>* paintedWave = painter->getPaintedAddress();
        //paintedWaves.push_back(paintedWave);
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

void OscillatorGui::addOscillatorKnobs(int n)
{
    for (size_t i = 0; i < n; ++i) {
        addKnobSection(0, height * i / n, width * 2 / 5 *  2 / 3, height / n, 4, tSection::filter, i);
    }
        
}


void OscillatorGui::addOscillatorLfo(int n)
{
    for (size_t i = 0; i < n; ++i) {
        addKnobSection(width * 2 / 5, height * i / n, width * 2 / 5 * 2 / 3, height / n, 4, tSection::lfo, i);
    }

}

