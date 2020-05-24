/*
  ==============================================================================

    AnimatedEditor.cpp
    Created: 23 May 2020 11:44:44pm
    Author:  jacop

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AnimatedEditor.h"

//==============================================================================
AnimatedEditor::AnimatedEditor()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    baseColour = Colours::limegreen;
    interpolateColour = Colours::sandybrown;
}

AnimatedEditor::~AnimatedEditor()
{

}


void AnimatedEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AnimatedEditor::update()
{
    // This function is called at the frequency specified by the setFramesPerSecond() call
    // in the constructor. You can use it to update counters, animate values, etc.
    framesPassed += getFrameCounter();
    alpha = (float)((std::sin(0.002 * framesPassed / 6000) + 1) / 4 + 0.5 );
    hue = (float)((std::cos(0.002 * framesPassed / 6000) + 1) / 2);
    saturation = (float)((std::sin(0.002 * framesPassed / 6000) + 1) / 4 + 0.75);
    interpolated = (float)((std::sin(0.002 * framesPassed / 6000) + 1) / 2);

}

void AnimatedEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(baseColour.withMultipliedSaturation(saturation).withMultipliedAlpha(alpha).withRotatedHue(hue).interpolatedWith(interpolateColour, interpolated));
    repaint();
}
