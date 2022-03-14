/**
 * @version 0.1
 * @date 2022-03-09
 */
#pragma once

#include "IColor.hpp"
#include "IGraphic.hpp"

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
     * @brief Start the drawing of the canvas.
     */
    virtual void startDraw();

    /**
     * @brief Stop the drawing of the canvas.
     */
    virtual void endDraw();

    /**
     * @brief Loads the new graphic library.
     */
    virtual void loadGraphic(const IGraphic& graphic);

    /**
     * @brief Unloads the previous graphic library.
     */
    virtual void unloadGraphic();

    /**
     * Draws a point on the canvas.
     * A point may represent a single pixel or any other single unit in a
     * grid.
     */
    virtual void drawPoint(int x, int y, const IColor& color);
};

}  // namespace arc
