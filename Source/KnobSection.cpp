/*
  ==============================================================================

    KnobSection.cpp
    Created: 26 May 2020 1:58:38pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KnobSection.h"

//==============================================================================

KnobSection::KnobSection()
{
    xPos = 0;
    yPos = 0;
    height = 40;
    width = 40;
    dir = direction::horizontal;

}

KnobSection::KnobSection(int x, int y, int w, int h) : xPos{ x }, yPos{ y }, width{ w }, height{ h }{
    dir = direction::horizontal;
   
}


KnobSection::KnobSection(int x, int y, int w, int h, direction dir, int nKnob) : xPos{ x }, yPos{ y }, width{ w }, height{ h }, dir{ dir } {
    for (size_t i; i < nKnob; ++i) {
        knobs.push_back(new Slider(Slider::Rotary, Slider::TextBoxBelow));
    }
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob) : xPos{ x }, yPos{ y }, width{ w }, height{ h }{
    dir = direction::horizontal;
    for (size_t i; i < nKnob; ++i) {
        knobs.push_back(new Slider(Slider::Rotary, Slider::TextBoxBelow));
    }
}

KnobSection::~KnobSection(){
    for (auto& knob : knobs) {
        delete knob;
    }
}

void KnobSection::setMyBounds() {
    this->setBounds(xPos, yPos, width, height);
}


void KnobSection::paint (Graphics& g)
{

}

void KnobSection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void KnobSection::sliderValueChanged(Slider* slider)
{
}

void KnobSection::sliderDragStarted(Slider*)
{
}

void KnobSection::sliderDragEnded(Slider*)
{
}
