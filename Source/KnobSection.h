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
#include "KnobLookAndFeel.h"

//==============================================================================
/*
*/

enum class direction {horizontal, vertical};

class KnobSection    : public Component, public Slider::Listener
{
public:
    KnobSection();
    KnobSection(int x,int y, int w, int h);
    KnobSection(int x, int y, int w, int h, int nKnob);
    KnobSection(int x, int y, int w, int h, int nKnob, tSection type);
    KnobSection(int x, int y, int w, int h, int nKnob, tSection type, int row);

    ~KnobSection();


    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider*) override;
    void sliderDragEnded(Slider*) override;


    void setMyBounds();
    void addKnobs(int nKnob, MySender* sender);
    void addKnobs(int nKnob, int row, MySender* sender);

    void addKnobs(int nKnob, int row); //deprecating
    
    void setMyOscillatorRange();
    void setMyLFORange();
    void setMyMatrixRange();

    std::vector<float> getLastSent() { return this->lastSent; };

private:
    std::vector<Slider*> knobs;
    int xPos;
    int yPos;
    int width;
    int height;
    direction dir;

    
    void arrange();
    void checkDirection();
    void checkTypeAndSetRange(tSection type);

    MySender *sender;

    KnobLookAndFeel KnobLAF;

    std::vector<float> lastSent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobSection)
};
