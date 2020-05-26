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
    void mouseDrag(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;

private:
    std::map<envelope, Coordinate*> env{ {envelope::attack,new Coordinate()},{envelope::decay , new Coordinate()},{envelope::sustain , new Coordinate()},{envelope::release , new Coordinate()} };
    float triggerDistance = 0;
    bool moving = false;
    Coordinate* currentPoint = nullptr; //used to position of the point we're ecurrently moving
    envelope currentEnv = envelope::attack; // used to store what type of point we're currently moving
                                            //used to set boundaries in dragging


    int envToInt(envelope enve);



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGui)
};
