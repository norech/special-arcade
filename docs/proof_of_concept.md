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
    Palette() { _colors.fill(nullptr); }

    ~Palette() = default;

    void setColor(int index, char symbol, ColorCode colorCode) override
    {
        _colors[index] = std::make_unique<Color>(colorCode, symbol);
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
