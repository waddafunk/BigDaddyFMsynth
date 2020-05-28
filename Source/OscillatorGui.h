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




//==============================================================================
/*
*/
class OscillatorGui    : public ModuleGui
{
public:
    OscillatorGui();
    OscillatorGui(int x, int y);
    OscillatorGui(int x, int y, int w, int h);
    ~OscillatorGui();

    void paint (Graphics&) override;
    void resized() override;

    void addPainters(int w, int h);

    void addPainters(WavePainter* painter);
    std::vector<std::vector<float>*> getPainters() { return this->paintedWaves; };

private:
    std::vector<WavePainter*> painters;
    std::vector<std::vector<float>*> paintedWaves;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorGui)
        
};
