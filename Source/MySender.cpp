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
    setFramesPerSecond(1);
    connect("127.0.0.1", 57120);
}

MySender::~MySender()
{
}

void MySender::update()
{
    send("/FmSynth/test", 1.0f);
}
