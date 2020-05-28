/*
  ==============================================================================

    KnobSection.h
    Created: 26 May 2020 1:58:38pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MySender.h"

//==============================================================================
/*
*/

enum class direction {horizontal, vertical};
enum class typeOfSection {filter,matrix};

class KnobSection    : public Component, public Slider::Listener
{
public:
    KnobSection();
    KnobSection(int x,int y, int w, int h);
    KnobSection(int x, int y, int w, int h, int nKnob);
    KnobSection(int x, int y, int w, int h, int nKnob,typeOfSection type);

    ~KnobSection();


    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider*) override;
    void sliderDragEnded(Slider*) override;


    void setMyBounds();
    void addKnobs(int nKnob);

    void send();

    


private:
    std::vector<Slider*> knobs;
    int xPos;
    int yPos;
    int width;
    int height;
    direction dir;
    typeOfSection type;


    void arrange();
    void checkDirection();

    MySender sender;


    String getSocketName();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobSection)
};
