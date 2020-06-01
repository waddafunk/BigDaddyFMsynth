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
    addKnobSection(0, 0, width, height * 1 / 6, 3, tSection::master);
    
    fader.setBounds(0, height * 3 / 8, width, height * 4 / 7 );
    fader.setSliderStyle(Slider::SliderStyle::LinearVertical);
    fader.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    fader.addListener(this);
    fader.setRange(-32, 18, 0.1);
    fader.setSkewFactorFromMidPoint(-16);
    fader.setValue(0);
    fader.setLookAndFeel(&MySliderLAF);
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

void MasterGui::paint(Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    Image img = ImageCache::getFromMemory(BinaryData::BigDaddy_png, BinaryData::BigDaddy_pngSize);
    
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey.darker(0.8));
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    g.drawImage(img,0,height/7,width,width*3/4,0,0,img.getWidth(), img.getHeight(), false);
}

void MasterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void MasterGui::sliderValueChanged(Slider* slider)
{
    float value = std::pow(10, slider->getValue() / 20);
    sender->send("/FmSynth/Master", 3, value);
}

void MasterGui::sliderDragStarted(Slider* slider)
{
}

void MasterGui::sliderDragEnded(Slider* slider)
{
}