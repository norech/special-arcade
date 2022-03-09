/**
 * @version 0.1
 * @date 2022-03-09
 */
#pragma once

#include "IColor.hpp"

namespace arc {

/**
 * @brief The canvas interface.
 * @details This interface is used to represent a canvas,
 * where basic shapes can be drawn.
 */
class ICanvas {
public:
    virtual ~ICanvas() = default;

    /**
     * Clear the canvas. Fills the canvas with a transparent color.
     */
    void clear();

    /**
     * Draws a point on the canvas.
     * A point may represent a single pixel or any other single unit in a
     * grid.
     */
    void drawPoint(int x, int y, const IColor &color);
};

}  // namespace arc
