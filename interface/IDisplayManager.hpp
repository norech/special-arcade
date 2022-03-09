/**
 * @version 0.1
 * @date 2022-03-08
 */

#pragma once

#include "Event.hpp"
#include "ICanvas.hpp"

namespace arc {

/**
 * @brief The display manager interface.
 * @details This interface is used to represent and manage a display and its
 * events.
 */

class IDisplayManager {
public:
    virtual ~IDisplayManager() = default;

    /**
     * @brief Initialize the display manager.
     */
    virtual void init() = 0;

    /**
     * @brief Is the window opened?
     */
    virtual bool isOpen() = 0;

    /**
     * Triggers any last operations and marks the window as closed.
     * The next call to `isOpen` will return `false`.
     *
     * @brief Close the window.
     */
    virtual void close() = 0;

    /**
     * Draws the canvas on the screen buffer.
     */
    virtual void draw(ICanvas& canvas) = 0;

    /**
     * Render the screen buffer on the screen.
     */
    virtual void render() = 0;

    /**
     * @brief Polls the events.
     * @param input An event to fill.
     *
     * @return true An input was found since the last call to this method.
     * The input is then available in the `getLastInput` method.
     * @return false No input was found since the last call to this method.
     */
    virtual bool pollEvent(Event& input) = 0;

    /**
     * @brief Destroy the display manager.
     */
    virtual void destroy() = 0;
};

}  // namespace arc
