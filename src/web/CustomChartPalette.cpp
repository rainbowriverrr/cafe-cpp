//
//  CustomChartPalette.cpp
//
//  Created by Julian Koksal on 2022-11-14.
//

#include "CustomChartPalette.hpp"

std::vector<Wt::WColor> CustomChartPalette::colours = {
    Wt::WColor(230, 0, 230),  // ANSI bright magenta
    Wt::WColor(0, 230, 230),  // ANSI bright cyan
    Wt::WColor(230, 0, 0),    // ANSI bright red
    Wt::WColor(0, 217, 0),    // ANSI bright green
    Wt::WColor(230, 230, 0),  // ANSI bright yellow
    Wt::WColor(0, 0, 255),    // ANSI bright blue
    Wt::WColor(255, 128, 0),  // orange
    Wt::WColor(128, 0, 255),  // purple
    Wt::WColor(0, 128, 255),  // light blue
    Wt::WColor(0, 100, 0)     // dark green
};

CustomChartPalette::CustomChartPalette()
{
    
}

CustomChartPalette::~CustomChartPalette()
{
    
}

Wt::WColor CustomChartPalette::getColour(int index)
{
    return colours[index % colours.size()];
}

Wt::WPen CustomChartPalette::borderPen(int index) const
{
    Wt::WPen pen = Wt::WPen(Wt::PenStyle::None);
    
    return pen;
}

Wt::WBrush CustomChartPalette::brush(int index) const
{
    Wt::WBrush brush = Wt::WBrush(getColour(index));
    
    return brush;
}

Wt::WColor CustomChartPalette::fontColor(int index) const
{
    return Wt::WColor(255, 255, 255);
}

Wt::WPen CustomChartPalette::strokePen(int index) const
{
    Wt::WPen pen = Wt::WPen(getColour(index));
    pen.setWidth(2);
    
    return pen;
}
