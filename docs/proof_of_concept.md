# Proof of concepts

## `Color` class

```cpp
namespace arc {

class Color : public IColor {
private:
    ColorCode _code;
    char symbol;

public:
    Color(ColorCode code, char symbol) : _code(code), symbol(symbol) {}
    ~Color() = default;

    ColorCode getColorCode() const override {
        return _code;
    }

    char getSymbol() const override {
        return symbol;
    }
};

}  // namespace arc
```


## `Palette` class
```cpp
namespace arc::grph {

class Palette : public IPalette {
 private:
    std::array<std::unique_ptr<Color>, 16> _colors; // 16 colors per palette

 public:
    Palette() = default;
    ~Palette() = default;

    void setColor(int index, char symbol, ColorCode colorCode) override
    {
        _colors[index].reset(new Color(colorCode, symbol));
    }

    const IColor& operator[](int index) const override
    {
        if (_colors[index]) {
            return *_colors[index];
        } else {
            throw std::out_of_range("Color not found");
        }
    }
};

}  // namespace arc
```

## `Canvas` class

```cpp
namespace arc::grph {

class Canvas : public ICanvas {
    // ... common abstract implementation between all graphic libraries
};

class SfmlCanvas : public Canvas {
private:
    SfmlGraphic* _graphic; // IGraphic implementation
public:
    SfmlCanvas(IGraphic* graphic) {
        _graphic = dynamic_cast<SfmlGraphic*>(&graphic);

        if (_graphic == nullptr) {
            throw std::runtime_error("Graphic is not an SfmlGraphic!");
        }
    }

    ~SfmlCanvas() = default;

    void startDraw() override {
        // clear the canvas of the previous frame...
        // e.g.  _internalSprite.clear();
    }

    void endDraw() override {
        // additional operations...
    }

    void drawPoint(int x, int y, const IColor &color) {
        // for example, we can have a drawPoint(x, y, color) method
        // in MyGraphic that will draw the point.
        // Or we can use a sprite to draw the point.
        // e.g. _internalSprite.drawPoint(x, y, color);
    }
};

}  // namespace arc
```

## Partial `IGraphic` class

```cpp
namespace arc::grph {

class SfmlGraphic : public IGraphic {
private:
    sfml::Window _window;
public:
    SfmlGraphic() {}

    ~SfmlGraphic() = default;

    // ...

    bool pollEvent(Event &event) override {
        sfml::Event sfmlEvent;

        // poll the event, and if there is no event, return false
        if (!_window.pollEvent(sfmlEvent)) return false;

        // handle window close
        if (sfmlEvent.type == sfml::Event::Closed) {
            event.type = Event::QUIT;
            return true;
        }

        // handle keyboard press
        if (sfmlEvent.type == sfml::Event::KeyPressed) {
            if (sfmlEvent.key.code < sf::Keyboard::A ||
                sfmlEvent.key.code > sf::Keyboard::Z) {
                // unknown key, ignore
                return false;
            }
            event.type = Event::KEY_PRESSED;
            event.keyboardInput.keyCode
                = (sfmlEvent.key.code - sf::Keyboard::A) + arc::KeyCode::A;
            return true;
        }

        // unknown event return false
        return false;
    }

    void loadCanvas(std::shared_ptr<ICanvas> &canvas) override {
        canvas = std::make_shared<SfmlCanvas>(this);
    }

    void unloadCanvas(std::shared_ptr<ICanvas> &canvas) override {
        delete canvas;
    };
};

}  // namespace arc
```

# Core loader (deprecated)

```cpp
int main(void)
{
    IGame* game = GameLoader::openAndGetExpose("./lib/arcade_pacman.so");
    IGraphic* graphic = GraphicLoader::openAndGetExpose("./lib/arcade_sdl.so");

    game->init();
    graphic->init();

    game->loadGraphic(graphic);
    while (graphic->isOpen()) {
        game->update(graphic->tick());
        game->render();
    }
    game->unloadGraphic();

    graphic->destroy();
    game->destroy();

    GraphicLoader::unexposeAndClose(graphic);
    GameLoader::unexposeAndClose(game);
    return 0;
}
```

# Basic core loader with graphical library switch (deprecated)

```cpp
int main(void)
{
    std:array<std::string> graphics = {
        "./lib/arcade_sdl.so",
        "./lib/arcade_sfml.so"
    };
    int currentGraphicId = 0;

    IGame* game = GameLoader::openAndGetExpose("./lib/arcade_pacman.so");
    IGraphic* graphic = GraphicLoader::openAndGetExpose(graphics[currentGraphicId]);

    game->init();
    graphic->init();

    game->loadGraphic(graphic);

    while (graphic->isOpen()) {
        game->update(graphic->tick());
        game->render();

        if (game->mustLoadAnotherGraphic()) {
            game->unloadGraphic();
            graphic->destroy();
            GraphicLoader::unexposeAndClose(graphic);

            // switch to the next library
            currentGraphicId = (currentGraphicId + 1) % graphics.size();
            graphic = GraphicLoader::openAndGetExpose(graphics[currentGraphicId]);
            graphic->init();
            game->loadGraphic(graphic);
        }
    }

    game->unloadGraphic();

    graphic->destroy();
    game->destroy();

    GraphicLoader::unexposeAndClose(graphic);
    GameLoader::unexposeAndClose(game);
    return 0;
}
```

# Basic core loader with a manager

```cpp
int main(void)
{
    MyManager manager; // manager implements IManager

    manager.loadGame("./lib/arcade_pacman.so");
    manager.loadGraphic("./lib/arcade_sdl.so");

    // init the game then the graphic, then load the graphic lib into the game
    manager.init();

    // loop until the graphic is closed
    while (manager.canUpdate()) {
        // update the game, handle the events and render the graphic
        // switches the graphic library if needed
        manager.update();
    }

    // unloads the graphic from the game and
    // destroys both the graphic and the game
    manager.destroy();
    return 0;
}
```
