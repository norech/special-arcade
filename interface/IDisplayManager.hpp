/**
 * @version 0.1
 * @date 2022-03-08
 */

#pragma once

namespace arc {

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
     * All sprites are drawn in the order they are added.
     * The last sprite added is drawn on top of the others.
     *
     * @brief Refreshes and redraw the sprites on the window.
     */
    virtual void display() = 0;

    /**
     * @brief Destroy the display manager.
     */
    virtual void destroy() = 0;
};

}  // namespace arc
