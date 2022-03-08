/**
 * @version 0.1
 * @date 2022-03-08
 */

#pragma once

class IDisplayManager;

namespace arc {

class IGame {
public:
    virtual ~IGame() = default;

    /**
     * Trigger the initialization of the game logic.
     * This method is called once at the beginning of the game.
     *
     * You should call `loadDisplay` before calling this method.
     *
     * @brief Initialize the game.
     * @note Behaviour is undefined if `init` is called when no
     * display manager is loaded.
     */
    virtual void init() = 0;

    /**
     * It is called every time the game is updated (input trigger, clock update,
     * etc.).
     *
     * @brief Update the game.
     * @param dt Delta time.
     * @note Behaviour is undefined if `update` is called when no
     * display manager is loaded.
     */
    virtual void update(float dt) = 0;

    /**
     * It is called every frame.
     *
     * @brief Render the game.
     * @note Behaviour is undefined if `render` is called when no
     * display manager is loaded.
     */
    virtual void render() = 0;

    /**
     * @brief Loads the specified display manager.
     * @throw std::exception if a display is already loaded.
     */
    virtual void loadDisplay(const IDisplayManager& displayManager) = 0;

    /**
     * @brief Unloads the currently loaded display manager.
     */
    virtual void unloadDisplay() = 0;

    /**
     * Triggers any last operations before the game is destroyed.
     *
     * @brief Destroy the game.
     */
    virtual void destroy() = 0;
};

}  // namespace arc
