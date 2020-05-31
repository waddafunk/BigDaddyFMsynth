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
#include "MySender.h"

enum class filterType {highpass, lowpass};

const float M_PI = 3.14159265359;

class MyFilter : public ModuleGui{
public:
    //==============================================================================
    MyFilter()
    {
    }
    MyFilter(float cutOff, float gain, float resonance) : cutoff{ cutoff }, gain{ gain }, resonance{ resonance } {
        sender = new MySender(tSection::filter);
    }

    MyFilter(float cutOff, float gain, float resonance, int row) : cutoff{ cutoff }, gain{ gain }, resonance{ resonance } {
        sender = new MySender(tSection::filter);
        this->row = row;
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

    float getHertzFromCutoff() {
        return cutoff * 10000 / width;
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

    void setGain(float gain)  //float gain: range in [0, 1]
    {
        this->gain = std::min(std::max(gain, 0.0f), 1.0f); //noice
    }


    float getCutoff() 
    {
        return this->cutoff;
    }

    float getResonance() {
        return this->resonance;
    }
    float getGain() {
        return this->gain;
    }


    void mouseDown(const MouseEvent& event) override{

        Coordinate mousePos;
        mousePos.setCoordinates(event.getMouseDownX(), event.getMouseDownY());
        setCutoffFromHz(Converter::map(mousePos.getX(), 0, width, 20, 10000));
        setGain( -1 * (Converter::map(mousePos.getY(), 0, height, 0, 1) - 1 ));
    }
   
    void mouseWheelMove(const MouseEvent& mEvent, const MouseWheelDetails& wheelEvent)override {

        if (resonance + wheelEvent.deltaY < 1 && resonance + wheelEvent.deltaY > 0) {
            resonance += wheelEvent.deltaY;
        }

        if (slope + wheelEvent.deltaX < 1 && slope + wheelEvent.deltaX > 0) {
            slope += wheelEvent.deltaX;
        }
        
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
            setGain(0);
            isLegalY = false;
        }
        else {
            if (mousePos.getY() < 0) {
                setGain(1);
                isLegalY = false;
            }
        }

        if (isLegalX) {
            float xMapped = Converter::map(mousePos.getX(), 0, width, 20, 10000);
            setCutoffFromHz(xMapped);
            cutoffSendValue = convertLog(mousePos.getX());
        }
        if (isLegalY) {
            setGain(-1 * (Converter::map(mousePos.getY(), 0, height, 0, 1) - 1));
            gainSendValue = convertGain(mousePos.getY());
        }
        
        sendAllFilterData();
        
    }
    
    float computeZeroCrossingPointX(Point<float> cutPoint, filterType type) {
        float m = - std::tan(45);
        if (type == filterType::highpass) {
            m = Converter::map(slope, 0, 1, std::tan(45), std::tan(60));
        }
        else {
            if (type == filterType::lowpass){
                m = - Converter::map(slope, 0, 1, std::tan(45), std::tan(60));
            }
        } 
        float x2 = cutPoint.getX();
        float y2 = height - cutPoint.getY();
        float y1 = 0;
        float x1 = (y1 - y2) / m + x2;
        //y = mx + q
        //y - y' = m(x - x')
        return x1;
    }
   

    double getMagnitudeAtFrequency(double freq)
    {
        auto f2pi = 2.0 * M_PI * freq;

        std::complex<double> b0a0(0, 0);
        std::complex<double> b1a0(0, 0);
        std::complex<double> b2a0(0, 0);
        std::complex<double> a1a0(0, 0);
        std::complex<double> a2a0(4, 0);
        
        std::complex<double> z(cos(f2pi), sin(f2pi));
        std::complex<double> z2 = z * z;

        std::complex<double> h =
            (b0a0 * z2 + b1a0 * z + b2a0)
            /
            (1.0 * z2 + a1a0 * z + a2a0);

        return std::abs(h);
    }



    void computeFilter() {
        for (size_t i = 0; i < 24000; i+=4) {
            filter[i] = getMagnitudeAtFrequency(i);
        }

    }

    float convertLog(float ctf) {
        return std::log10(ctf) * 10000 / std::log10(width);
    }

    float convertGain(float gn) {
        return -gn * 2 / height;
    }

    void sendAllFilterData() {
        sender->send(sender->getSocketName() << "/Cutoff", row, cutoffSendValue);
        sender->send(sender->getSocketName() << "/Resonance", row, resonance);
        sender->send(sender->getSocketName() << "/Gain", row, gainSendValue);
    }

protected:

    float cutoff = 440 * width / 10000.0f;
    float cutoffSendValue = convertLog(cutoff);
    float resonance = 0.7f * height;
    float gain = 0.7f * height;
    float gainSendValue;
    filterType type;
    float slope = 0;
    float filter[24000/4];
    int row = 0;
    
    MySender* sender;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyFilter)
};


