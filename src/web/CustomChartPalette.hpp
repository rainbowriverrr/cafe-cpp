//
//  CustomChartPalette.hpp
//

#ifndef CustomChartPalette_hpp
#define CustomChartPalette_hpp

#include <Wt/Chart/WChartPalette.h>
#include <Wt/WPen.h>
#include <Wt/WBrush.h>
#include <Wt/WColor.h>

/**
 * @brief Custom palette used by the chart on the sales page.
 *
 * Implementation of Wt::Chart::WChartPalette.
 *
 * @author Julian Koksal
 * @date 2022-11-14
 */
class CustomChartPalette : public Wt::Chart::WChartPalette
{
public:
    /**
     * @brief Constructor. Does nothing.
     */
    CustomChartPalette();
    
    /**
     * @brief Destructor. Does nothing.
     */
    ~CustomChartPalette();
    
    /**
     * @brief Returns the palette colour for the given index.
     *
     * @param index the vector index of the colour
     * @return the colour
     */
    static Wt::WColor getColour(int index);
    
    /**
     * @brief Returns the pen used to draw the chart border.
     *
     * Implemented with pen style none (no border).
     *
     * @param index not used, required for override
     * @return a pen with style none
     */
    virtual Wt::WPen borderPen(int index) const override;
    
    /**
     * @brief Returns a solid brush with the colour given by index.
     *
     * @param index the vector index of the colour
     * @return a solid brush with the colour given by index
     */
    virtual Wt::WBrush brush(int index) const override;
    
    /**
     * @brief Returns the font colour.
     *
     * Implemented as pure white (rgb: 255, 255, 255).
     *
     * @param index not used, required for override
     * @return white colour
     */
    virtual Wt::WColor fontColor(int index) const override;
    
    /**
     * @brief Returns a solid pen with the colour given by index.
     *
     * @param index the vector index of the colour
     * @return a solid pen with the colour given by index
     */
    virtual Wt::WPen strokePen(int index) const override;
    
private:
    /**
     * @brief The colours used by this palette.
     */
    static std::vector<Wt::WColor> colours;
};

#endif /* CustomChartPalette_hpp */
