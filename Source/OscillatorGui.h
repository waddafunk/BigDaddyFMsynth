/*
  ==============================================================================

    OscillatorGui.h
    Created: 23 May 2020 4:12:58pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"
#include "SawPainter.h"
#include "SinePainter.h"
#include "SquarePainter.h"
#include "TrianglePainter.h"
#include "WavePainter.h"
#include "FilterGui.h"



//==============================================================================
/*
*/
class OscillatorGui    : public ModuleGui, public Button::Listener
{
public:
    OscillatorGui();
    OscillatorGui(int x, int y);
    OscillatorGui(int x, int y, int w, int h);
    ~OscillatorGui();

    void paint (Graphics&) override;
    void resized() override;

    void addPainters(WavePainter* painter);
    //std::vector<std::vector<float>*> getPainters() { return this->paintedWaves; };


    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider*) override;
    void sliderDragEnded(Slider*) override;

    void buttonStateChanged(Button* button) override;
    void buttonClicked(Button* button) override;

private:
    std::vector<WavePainter*> painters;
    std::vector<FilterGui*> filters;
    std::vector<ToggleButton *>buttons;
    int numOfOsc = 8;
    //std::vector<std::vector<float>*> paintedWaves; //TODO: set waves length to perceptual present

    void addOscillatorKnobs();
    void addOscillatorLfo();
	void addTriggers();
    void addPainters();
    void addFilter(int x, int y, int w, int h);

    void addFilters();




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorGui)
        
};
