/*
  ==============================================================================

    FilterGraph.h
    Created: 27 May 2020 11:14:05am
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"
#include"MyLowPass.h"
#include "MyBandPass.h"
#include "MyHighPass.h"
#include "MyNotchFilter.h"

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

    void setCutoff(float cutoff);
    float getCutoff() { return this->cutoff; };

    void setResonance(float resonance);
    float getResonance() { return this->resonance; };

private:

    std::vector <ModuleGui*> myGraphs;

    int selectedGraph = 0; //0 lowpass, 1 highpass, 2 bandpass, 3 notch
    float cutoff;
    float resonance;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGraph)
};
