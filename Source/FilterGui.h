/*
  ==============================================================================

    FilterGui.h
    Created: 23 May 2020 4:13:23pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"
#include "KnobSection.h"
#include "FilterGraph.h"
#include "MyHighPass.h"
#include "MylowPass.h"
#include "MyFilter.h"

//==============================================================================
/*
*/
class FilterGui    : public ModuleGui, public Button::Listener
{
public:
    FilterGui();
    FilterGui(int x, int y);
    FilterGui(int x, int y, int w, int h);
    FilterGui(int x, int y, int w, int h, int n);
    ~FilterGui();

    void paint (Graphics&) override;
    void resized() override;

    void addMyFilters(int n);

    void buttonStateChanged(Button* button) override;
    void buttonClicked(Button* button) override;

   // void addMyFilter(FilterGraph* painter);


private:
    std::vector<MyFilter*> myFilters;
    std::vector<ToggleButton*> buttons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGui)
};
