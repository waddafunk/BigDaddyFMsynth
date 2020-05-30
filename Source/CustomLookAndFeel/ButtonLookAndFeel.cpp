#include <JuceHeader.h>
#include "ButtonLookAndFeel.h"



//==============================================================================
ButtonLookAndFeel::ButtonLookAndFeel()
{
}

void ButtonLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
    bool isMouseOverButton, bool isButtonDown)
{
    auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
        .withMultipliedAlpha(button.isEnabled() ? 0.9f : 0.5f);

    if (isButtonDown || isMouseOverButton)
        baseColour = baseColour.contrasting(isButtonDown ? 0.2f : 0.1f);

    auto width = button.getWidth() - 1.0f;
    auto height = button.getHeight() - 1.0f;

    if (width > 0 && height > 0)
    {
        g.setGradientFill(ColourGradient::vertical(baseColour, 0.0f,
            baseColour.darker(0.1f), height));

        g.fillRect(button.getLocalBounds());
    }
}

void ButtonLookAndFeel::drawTickBox(Graphics & g, Component & component,
        float x, float y, float w, float h,
        bool ticked,
        bool isEnabled,
        bool isMouseOverButton,
        bool isButtonDown)
    {
        auto boxSize = w * 0.7f;

        auto isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());

        auto colour = component.findColour(TextButton::buttonOnColourId)
            .withMultipliedSaturation((component.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
            .withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.7f);

        g.setColour(colour);

        Rectangle<float> r(x, y + (h - boxSize) * 0.5f, boxSize, boxSize);
        g.fillRect(r);

        if (ticked)
        {
            auto tickPath = LookAndFeel_V4::getTickShape(6.0f);
            g.setColour(isEnabled ? findColour(TextButton::buttonColourId) : Colours::grey);

            auto transform = RectanglePlacement(RectanglePlacement::centred)
                .getTransformToFit(tickPath.getBounds(),
                    r.reduced(r.getHeight() * 0.05f));

            g.fillPath(tickPath, transform);
        }
    }