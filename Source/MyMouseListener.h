/*
  ==============================================================================

    MyMouseListener.h
    Created: 25 May 2020 11:16:01pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MyMouseListener    : public MouseListener
{
public:
    MyMouseListener();
    ~MyMouseListener();


    void mouseMove(const MouseEvent & event) override;

    void mouseEnter(const MouseEvent & event) override;

    void mouseExit(const MouseEvent & event) override;

    void mouseDown(const MouseEvent & event) override;

    void mouseDrag(const MouseEvent & event) override;

    void mouseUp(const MouseEvent & event) override;

    void mouseDoubleClick(const MouseEvent & event) override;

    void mouseWheelMove(const MouseEvent & event,
        const MouseWheelDetails & wheel) override;

    void mouseMagnify(const MouseEvent & event, float scaleFactor)override ;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyMouseListener)
};
