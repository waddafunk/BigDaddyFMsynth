/*
  ==============================================================================

    AnimatedEditor.h
    Created: 23 May 2020 11:44:44pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"MyAnime.h"
#include"PluginProcessor.h"

//==============================================================================
/*
*/
class AnimatedEditor    : public MyAnime
{
public:
    AnimatedEditor();
    ~AnimatedEditor();

    void paint (Graphics&) override;
    void resized() override;
    void update() override;


private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimatedEditor)

};
