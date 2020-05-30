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
    addPainters();
    addOscillatorKnobs();
    addOscillatorLfo();
    addFilters();
}

OscillatorGui::OscillatorGui(int x, int y)
{
    xPos = x;
    yPos = y;
    addPainters();
    addOscillatorKnobs();
    addOscillatorLfo();
    addFilters();
}

OscillatorGui::OscillatorGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;
    addPainters();
    addOscillatorKnobs();
    addOscillatorLfo();
    addFilters();
}

OscillatorGui::~OscillatorGui()
{
    for (auto& painter : painters) {
        delete painter;
    }

    for (auto& knobSection : knobSections) {
        delete knobSection;
    }

    for (auto& filter : filters) {
        delete filter;
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



//TODO button to add an oscillator!
//TODO autoresize each waveform each time a new one is added

void OscillatorGui::addPainters(WavePainter * painter) {
    painters.push_back(painter);
    painter->setFramesPerSecond(60);
    painter->setMyBounds();
    addAndMakeVisible(painter);
}



void OscillatorGui::addPainters() {
    for (size_t i = 0; i < numOfOsc; ++i) {
        painters.push_back(new SinePainter(width * 2 / 5 * 2 / 3, height * i / numOfOsc, width * 2 / 5 * 1 / 3, height / numOfOsc));
    }

    for (auto& painter : painters) {
        //std::vector<float>* paintedWave = painter->getPaintedAddress();
        //paintedWaves.push_back(paintedWave);
        painter->setFramesPerSecond(60);
        painter->setMyBounds();
        addAndMakeVisible(painter);
    }
}


void OscillatorGui::addOscillatorKnobs()
{
    for (size_t i = 0; i < numOfOsc; ++i) {
        addKnobSection(0, height * i / numOfOsc, width * 2 / 5 *  2 / 3, height / numOfOsc, 4, tSection::oscillator, i);
    }
        
}


void OscillatorGui::addOscillatorLfo()
{
    for (size_t i = 0; i < numOfOsc; ++i) {
        addKnobSection(width * 2 / 5, height * i / numOfOsc, width * 4 / 15, height / numOfOsc, 4, tSection::lfo, i);
    }

}

void OscillatorGui::addFilters()
{
    for (size_t i = 0; i < numOfOsc; ++i) {

      addFilter(width * 2 / 5 + width * 4 / 15 , height * i / numOfOsc, width * 2 / 5 * 1 / 3, height / numOfOsc);
    }
}

void OscillatorGui::addFilter(int x, int y, int w, int h){
    FilterGui* filter = new FilterGui(x, y, w, h);
    filters.push_back(filter);
    filter->setMyBounds();
    addAndMakeVisible(filter);
    
}
