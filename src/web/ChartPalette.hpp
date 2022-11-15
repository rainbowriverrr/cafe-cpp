//
//  ChartPalette.hpp
//

#ifndef ChartPalette_hpp
#define ChartPalette_hpp

#include <Wt/Chart/WChartPalette.h>
#include <Wt/WPen.h>
#include <Wt/WBrush.h>
#include <Wt/WColor.h>

/**
 * @author Julian Koksal
 * @date 2022-11-14
 */
class ChartPalette : public Wt::Chart::WChartPalette
{
public:
    
    ChartPalette();
    
    ~ChartPalette();
    
    static Wt::WColor getColour(int index);
    
    virtual Wt::WPen borderPen(int index) const override;
    virtual Wt::WBrush brush(int index) const override;
    virtual Wt::WColor fontColor(int index) const override;
    virtual Wt::WPen strokePen(int index) const override;
private:
    static std::vector<Wt::WColor> colours;
};

#endif /* ChartPalette_hpp */
