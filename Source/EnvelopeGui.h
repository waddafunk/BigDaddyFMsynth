/*
  ==============================================================================

    EnvelopeGui.h
    Created: 23 May 2020 4:13:15pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"
#include "Coordinate.h"



enum envelope { attack, decay, sustain, release };

//==============================================================================
/*
*/
class EnvelopeGui    : public ModuleGui
{
public:
    EnvelopeGui();
    EnvelopeGui(int x, int y, int width, int height);
    ~EnvelopeGui();

    void paint (Graphics&) override;
    void resized() override;
    void mouseDown(const MouseEvent& event) override;

private:
    std::map<envelope, Coordinate*> env{ {envelope::attack,new Coordinate()},{envelope::decay , new Coordinate()},{envelope::sustain , new Coordinate()},{envelope::release , new Coordinate()} };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGui)
};
