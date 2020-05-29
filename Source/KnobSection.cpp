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

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob, tSection type, int row) : xPos{ x }, yPos{ y }, width{ w }, height{ h }
{
    checkDirection();
    addKnobs(nKnob, row);
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
        temp = new Slider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox);
        String knobName = getSocketName() + ">=" + std::to_string(i);
        temp->setName(knobName); //set name to send to socket
        temp->addListener(this);
        temp->setLookAndFeel(&KnobLAF);
        addAndMakeVisible(temp); // makes visible each knob
        knobs.push_back(temp);
    }
    arrange();
}

void KnobSection::addKnobs(int nKnob, int row)
{
    Slider* temp;

    for (size_t i = 0; i < nKnob; ++i) {
        temp = new Slider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox);
        String knobName = getSocketName() + ">=" + std::to_string(row) + ">=" + std::to_string(i);
        std::string stdName = knobName.toStdString();
        temp->setName(knobName); //set name to send to socket
        temp->addListener(this);
        temp->setLookAndFeel(&KnobLAF);
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
    //case tSection::filter: return "/FmSynth/Filter";
    case tSection::matrix: return "/FmSynth/Matrix";
    case tSection::lfo: return "/Fm/Synth/Lfo";
    case tSection::oscillator: return "/FmSynth/Oscillator";
    case tSection::master: return "/FmSynth/Master";
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
    String name = slider->getName();
    String token1, token2, token3; // token1 module name, token 2 position and token3 additional position if matrix
    std::string delimiter = ">=", strTok3, stdName = name.toStdString(); //cast to std string


    token1 = String(stdName.substr(0, stdName.find(">=")).c_str()); //module name
    stdName.erase(0, stdName.find(delimiter) + delimiter.length()); //erase delimiter
    token2 = String(stdName.substr(0, stdName.find(">=")).c_str()); //position


    float token2float = std::stoi(token2.toStdString());  //cast position to float
    float token3float;


    stdName.erase(0, stdName.find(delimiter) + delimiter.length());

    strTok3 = "Matrix";
    float value; //slider value


    if ((token1.toStdString().find(strTok3) != std::string::npos) || (token1.toStdString().find("Oscillator") != std::string::npos)) { //if matrix

        token3 = String(stdName.substr(0, stdName.find(">=")).c_str()); // additional position
        token3float = std::stoi(token3.toStdString());  
        value = slider->getValue();
        sender.send(token1, token2float, token3float, value); //send
    }
    else {
        sender.send(token1, token2float, value); //send
    }
        
        
    
 
}

void KnobSection::sliderDragStarted(Slider*)
{
}

void KnobSection::sliderDragEnded(Slider*)
{
}