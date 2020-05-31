/*
  ==============================================================================

    Converter.h
    Created: 30 May 2020 12:27:56am
    Author:  daveg

  ==============================================================================
*/

#pragma once


class Converter
{
public:
    Converter() {}
    ~Converter() {}

    static float map(float value,
        float start1, float stop1,
        float start2, float stop2) {
        float outgoing =
            start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
        return outgoing;
    }

    



private:

};

