//
//  ChartPalette.cpp
//
//  Created by Julian Koksal on 2022-11-14.
//

#include "ChartPalette.hpp"

std::vector<Wt::WColor> ChartPalette::colours = {
    Wt::WColor(230, 0, 230),  // ANSI bright magenta
    Wt::WColor(0, 230, 230),  // ANSI bright cyan
    Wt::WColor(230, 0, 0),    // ANSI bright red
    Wt::WColor(0, 217, 0),    // ANSI bright green
    Wt::WColor(230, 230, 0),  // ANSI bright yellow
    Wt::WColor(0, 0, 255),    // ANSI bright blue
    Wt::WColor(255, 128, 0),  // orange
    Wt::WColor(128, 0, 255),  // purple
    Wt::WColor(0, 128, 255),  // light blue
    Wt::WColor(255, 128, 128) // pale orange/pink
};

ChartPalette::ChartPalette()
{
    
}

ChartPalette::~ChartPalette()
{
    
}

Wt::WColor ChartPalette::getColour(int index)
{
    return colours[index % colours.size()];
}

Wt::WPen ChartPalette::borderPen(int index) const
{
    return Wt::WPen(Wt::PenStyle::None);
}

Wt::WBrush ChartPalette::brush(int index) const
{
    Wt::WBrush brush = Wt::WBrush(getColour(index));
    
    return brush;
}

Wt::WColor ChartPalette::fontColor(int index) const
{
    return Wt::WColor(255, 255, 255);
}

Wt::WPen ChartPalette::strokePen(int index) const
{
    Wt::WPen pen = Wt::WPen(getColour(index));
    pen.setWidth(2);
    
    return pen;
}
