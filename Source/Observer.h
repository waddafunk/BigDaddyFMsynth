/*
  ==============================================================================

    Observer.h
    Created: 31 May 2020 3:13:24pm
    Author:  daveg

  ==============================================================================
*/

#pragma once


class Observer {

    virtual void update(int id, int row, float value) = 0;
};