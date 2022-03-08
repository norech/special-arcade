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
     * @brief Close the window.
     */
    virtual void close() = 0;

    /**
     * @brief Refreshes and rerenders the window.
     */
    virtual void refresh() = 0;

    /**
     * @brief Destroy the display manager.
     */
    virtual void destroy() = 0;
};

}  // namespace arc