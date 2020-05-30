/*
  ==============================================================================

    MasterGui.h
    Created: 23 May 2020 4:14:08pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"
#include "KnobSection.h"

//==============================================================================
/*
*/
class MasterGui    : public ModuleGui, public Slider::Listener
{
public:
    MasterGui();
    MasterGui(int x, int y, int width, int height);
    ~MasterGui();

    void paint (Graphics&) override;
    void resized() override;



    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

private:
    Slider fader;
    MySender* sender;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterGui)
};
