/*
  ==============================================================================

    MyFilter.h
    Created: 28 May 2020 12:15:15pm
    Author:  jacop

  ==============================================================================
*/

#pragma once
#include "ModuleGui.h"
#include "Coordinate.h"
#include "Converter.h"

class MyFilter : public ModuleGui{
public:
    //==============================================================================
    MyFilter()
    {
    }



    void paint(Graphics& g) override
    {
        
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

    void setCutoffFromHz(float cutOff)    //float cutOff: cutoff frequency value in hertz
    {
        if(cutOff >= 20.0f && cutOff <= 10000.0f)   //unnecessary check?
            this->cutoff = cutOff * width / 10000.0f;   //adjust to component dimensions
    }

    /*
    void setCutoff(float cutOff)    //float cutOff: cutoff frequency value in hertz
    {
        this->cutoff = cutOff;
    }
    */
    void setResonance(float resonance)  //float resonance: range in [0, 1]
    {
    
        this->resonance = std::min(std::max(resonance, 0.0f), 1.0f); //noice
    }


    float getCutoff() 
    {
        return this->cutoff;
    }

    float getResonance() {
        return this->resonance;
    }


    void mouseDown(const MouseEvent& event) override{

        Coordinate mousePos;
        mousePos.setCoordinates(event.getMouseDownX(), event.getMouseDownY());
        setCutoffFromHz(Converter::map(mousePos.getX(), 0, width, 20, 10000));
        setResonance( -1 * (Converter::map(mousePos.getY(), 0, height, 0, 1) - 1 ));
    }
   
    void mouseDrag(const MouseEvent& event) override {
        Coordinate mousePos;
        bool isLegalX = true;
        bool isLegalY = true;
        mousePos.setCoordinates(event.getPosition().getX(), event.getPosition().getY());

        if (mousePos.getX() < 0) {
            setCutoffFromHz(20);
            isLegalX = false;
        }
        else {
            if (mousePos.getX() > width) {
                setCutoffFromHz(10000);
                isLegalX = false;
            }
        }

        if (mousePos.getY() > height) {
            setResonance(0);
            isLegalY = false;
        }
        else {
            if (mousePos.getY() < 0) {
                setResonance(1);
                isLegalY = false;
            }
        }

        if (isLegalX) {
            setCutoffFromHz(Converter::map(mousePos.getX(), 0, width, 20, 10000));
        }
        if (isLegalY) {
            setResonance(-1 * (Converter::map(mousePos.getY(), 0, height, 0, 1) - 1));
        }
        
        
        
    }
    


protected:

    float cutoff = 440 * width / 10000.0f;
    float resonance = 0.7f * height;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyFilter)
};


