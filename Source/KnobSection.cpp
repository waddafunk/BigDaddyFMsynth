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
    checkDirection();

}

KnobSection::KnobSection(int x, int y, int w, int h) : xPos{ x }, yPos{ y }, width{ w }, height{ h }{
    checkDirection();
   
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob) : xPos{ x }, yPos{ y }, width{ w }, height{ h }{
    checkDirection();
    addKnobs(nKnob);
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob, tSection type) : xPos{ x }, yPos{ y }, width{ w }, height{ h }
{
    checkDirection();
    addKnobs(nKnob);
    this->type = type;
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob, tSection type, int raw) : xPos{ x }, yPos{ y }, width{ w }, height{ h }
{
    checkDirection();
    addKnobs(nKnob, raw);
    this->type = type;

}

KnobSection::~KnobSection(){
    for (auto& knob : knobs) {
        delete knob;
    }
}


void KnobSection::setMyBounds() {
    this->setBounds(xPos, yPos, width, height);
}


//-----------------------ADD KNOBS-----------
void KnobSection::addKnobs(int nKnob)
{
    Slider* temp;

    for (size_t i = 0; i < nKnob; ++i) {
        temp = new Slider(Slider::Rotary,Slider::NoTextBox);
        String knobName = getSocketName() + std::to_string(i);
        temp->addListener(this);
        addAndMakeVisible(temp); // makes visible each knob
        knobs.push_back(temp);
    }
    arrange();
}

void KnobSection::addKnobs(int nKnob, int raw)
{
    Slider* temp;

    for (size_t i = 0; i < nKnob; ++i) {
        temp = new Slider(Slider::Rotary, Slider::NoTextBox);
        String knobName = getSocketName() + std::to_string(raw) + std::to_string(i);
        temp->addListener(this);
        addAndMakeVisible(temp); // makes visible each knob
        knobs.push_back(temp);
    }
    arrange();
}


void KnobSection::send(){
    sender.send(getSocketName(), 10);
}

//TODO IMPLEMENT AUTOMATIC AND SCALABLE SETBOUND FOR KNOBS 
void KnobSection::arrange() {
    if (knobs.size() == 0){
        return;
    }
    int i = 0;
    float individualWidth, individualHeight;

    switch (dir)
    {
    case direction::horizontal:
        individualHeight = height;
        individualWidth = width / knobs.size();
        for (auto& knob : knobs) {
            knob->setBounds(i * individualWidth, 0, individualWidth, individualHeight);
            i++;
        }
        break;

    case direction::vertical:
        individualHeight = height/knobs.size();
        individualWidth = width;
        for (auto& knob : knobs) {
            knob->setBounds(0, i * individualHeight, individualWidth, individualHeight);
            i++;
        }
        break;
    default:
        break;
    }


}


void KnobSection::checkDirection() {
    if (height > width) {
        dir = direction::vertical;
    }
    else
    {
        dir = direction::horizontal;
    }
}

String KnobSection::getSocketName()
{
    switch (type) {
    case tSection::filter: return "/FmSynth/Filter";
    case tSection::matrix: return "/FmSynth/Matrix";
    default:
        break;
    }
    return "StandardSocket"; //error case
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