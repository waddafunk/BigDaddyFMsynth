/*
  ==============================================================================

    FilterGraph.h
    Created: 27 May 2020 11:14:05am
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyFilter.h"
#include"ModuleGui.h"
#include "Coordinate.h"

//==============================================================================
/*
*/
class FilterGraph    : public ModuleGui
{
public:
    FilterGraph();
    FilterGraph(int x, int y, int width, int height);
    ~FilterGraph();

    void paint (Graphics&) override;
    void resized() override;
    void setMyBounds();
    void addGraphs();

    void setSelectedGraph(int selectedGraph); //0 lowpass, 1 highpass, 2 bandpass, 3 notch
    int getSelectedGraph() { return this->selectedGraph; }


private:

    float triggerDistance = 0;

    std::vector <MyFilter*> myGraphs;

    int selectedGraph = 0; //0 lowpass, 1 highpass, 2 bandpass, 3 notch

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGraph)
};
