/**
 * @version 0.1
 * @date 2022-03-28
 */

#pragma once

#include <memory>

#include "../common/Event.hpp"
#include "../common/IColor.hpp"
#include "../common/IntRect.hpp"
#include "./CanvasCapacity.hpp"

namespace arc::grph {

class ICanvas;

/**
 * @brief Graphic - The sprite interface.
 * @details This interface is used to represent and manage a sprite
 */

class ISprite {
    virtual ~ISprite() = default;

    virtual void init();

    virtual void destroy();

    virtual void setRect(const IntRect& rect) = 0;

    virtual void setFallbackColor(const IColor& color) = 0;

    virtual void setTexturePath(const std::string& texturePath) = 0;

    virtual const std::string& getTexturePath();

    virtual const IntRect& getRect();

    virtual const IColor& getFallbackColor();

    virtual void draw(ICanvas* canvas);
};

}  // namespace arc::grph
