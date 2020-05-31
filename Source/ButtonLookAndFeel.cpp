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
        bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
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


ToggleButtonLookAndFeel::ToggleButtonLookAndFeel()
{
    img1 = ImageCache::getFromMemory(BinaryData::switch_toggle_png, BinaryData::switch_toggle_pngSize);
}

void ToggleButtonLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown)

{


    const int tickWidth = jmin(20, button.getHeight() - 4);

    drawTickBox(g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
        (float)tickWidth, (float)tickWidth,
        button.getToggleState(),
        button.isEnabled(),
        isMouseOverButton,
        isButtonDown);

    g.setColour(button.findColour(ToggleButton::textColourId));
    g.setFont(jmin(15.0f, button.getHeight() * 0.6f));

    if (!button.isEnabled())
        g.setOpacity(0.5f);

    const int textX = tickWidth + 5;

    g.drawFittedText(button.getButtonText(),
        textX, 4,
        button.getWidth() - textX - 2, button.getHeight() - 8,
        Justification::centredLeft, 10);
}

void ToggleButtonLookAndFeel::drawTickBox(Graphics& g, Component& component,
    float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
    auto boxSize = w * 0.7f;
    auto isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());

    if (img1.isValid()) {
        int selector = (int)ticked;
        const int frames = int(img1.getHeight() / img1.getWidth());
        const int frameId = (int)ceil(selector * ((double)frames - 1.0));
        
        g.drawImage(img1, x, y-h/2, w*2, h*2,
            0, frameId * img1.getWidth(), img1.getWidth(), img1.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + w * (1.0f - textPpercent) / 2.0f,
            0.5f * h, w * textPpercent, 0.5f * h);
        g.setColour(Colours::white);
        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}