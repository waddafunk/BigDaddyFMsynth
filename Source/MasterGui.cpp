/*
  ==============================================================================

    MasterGui.cpp
    Created: 23 May 2020 4:14:08pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MasterGui.h"

//==============================================================================
MasterGui::MasterGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

MasterGui::MasterGui(int x, int y, int width, int height)
{
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    addKnobSection(0, 0, width, height/3, 3, tSection::master);
    fader.setBounds(0, height/3, width, height * 2 / 3 -30);
    fader.setSliderStyle(Slider::SliderStyle::LinearVertical);
    fader.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    fader.addListener(this);
    fader.setRange(-32, 9, 0.1);
    fader.setSkewFactorFromMidPoint(-16);
    fader.setValue(0);
    addAndMakeVisible(fader);

    sender = new MySender(tSection::master);
}

MasterGui::~MasterGui()
{
    for (auto& knobSection : knobSections)
    {
        delete knobSection;
    }

    delete sender;
}

void MasterGui::paint (Graphics& g)
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

void MasterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void MasterGui::sliderValueChanged(Slider* slider)
{
    float value = std::pow(10, slider->getValue()/20);
   sender->send("/FmSynth/Master",3, value );
}

void MasterGui::sliderDragStarted(Slider* slider)
{
}

void MasterGui::sliderDragEnded(Slider* slider)
{
}
