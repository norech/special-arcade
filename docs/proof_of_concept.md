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
    std::array<Color, 16> _colors; // 16 colors per palette
    std::array<bool, 16> _hasColor; // 16 colors per palette

public:
    Palette() {
        _hasColor.fill(false);
    }

    ~Palette() = default;

    void setColor(int index, char symbol, ColorCode colorCode) override {
        _colors[index] = Color(colorCode, symbol);
        _hasColor[index] = true;
    }

    const IColor& operator[](int index) const override {
        if (_hasColor[index]) {
            return _colors[index];
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
