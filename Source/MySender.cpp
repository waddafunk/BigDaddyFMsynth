/*
  ==============================================================================

    MySender.cpp
    Created: 27 May 2020 3:42:22pm
    Author:  daveg

  ==============================================================================
*/

#include "MySender.h"

MySender::MySender()
{
    setFramesPerSecond(10);
    connect("127.0.0.1", 57120);
}

MySender::~MySender()
{
}

void MySender::update()
{
    frames += getFrameCounter();
    float dat = std::cos(10 * frames / 60 );
    send("/FmSynth/test", dat);
}
