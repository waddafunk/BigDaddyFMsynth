#include <JuceHeader.h>
#include "SquarePainter.h"

//==============================================================================
SquarePainter::SquarePainter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SquarePainter::SquarePainter(int x, int y)
{
    xPos = x;
    yPos = y;
    height = 40;
    width = 40;
}

SquarePainter::SquarePainter(int x, int y, int width, int height) {
    xPos = x;
    yPos = y;
    this->width = width;
    this->height = height;
}

SquarePainter::SquarePainter(int x, int y, int width, int height, float dutyCycle) {
    xPos = x;
    yPos = y;
    this->width = width;
    this->height = height;
    setDutyCycle(dutyCycle);
}


SquarePainter::~SquarePainter()
{
}

void SquarePainter::setDutyCycle(float dutyCycle)
{
    if(dutyCycle > 0 && dutyCycle < 1)
        this->dutyCycle = dutyCycle;
}

void SquarePainter::paint(Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::white);

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    auto numberOfDots = width; // [1]
    Path spinePath;         // [2]
    int amplitude = (height - 40) / 2;

    for (auto i = 0; i < numberOfDots; ++i) // [3]
    {   
        float pos = amplitude - getHeight() / 16;
        if(std::cos(i * freq + 8 * freq * getFrameCounter()) < dutyCycle - 0.5)
            pos = -pos;
        Point<float> p(i * getWidth() / (numberOfDots - 2), getHeight() / 2 + pos);

        if (i == 0)
            spinePath.startNewSubPath(p);  // if this is the first point, start a new path..
        else
            spinePath.lineTo(p);           // ...otherwise add the next point
    }



    // draw an outline around the path that we have created
    g.strokePath(spinePath, PathStrokeType(4.0f)); // [4]


}

void SquarePainter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}