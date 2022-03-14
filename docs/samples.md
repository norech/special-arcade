# Sample game

> Note: Code displayed here might not be valid.
> It is just an example of possible game code.

## Draw points

```cpp
// namespace arc

class Game : public IGame {
private:
    IGraphic *_graphic;
    // ...

    Canvas _canvas; // ICanvas implementation
    Palette _palette; // IPalette implementation

public:
    Game() = default;
    ~Game() = default;

    void init() override {
        _palette.setColor(0, 'A', RED);
        _palette.setColor(1, 'E', GREEN);
    }

    void update(float dt) override {
        Event event;

        while (_display->pollEvent(event)) {
            if (event.type == Event::QUIT) {
                _display->close();
            }
        }
    }

    void render() override {
        // remove all points from the previous frame
        // fills the canvas with transparent color
        _canvas.clear();

        // on ncurses, a red 'A' and a green 'E' will be displayed
        // on graphical, both a red and a green square will be displayed
        _canvas.drawPoint(0, 0, _palette[0]);
        _canvas.drawPoint(1, 1, _palette[1]);

        // draw the canvas on the screen
        _display->draw(_canvas);

        // ensure the display is rendered and do all the necessary
        // operations to display everything drawn on the display
        _display->render();
    }

    void destroy() override {
        // Destroy game here
    }

    void loadGraphic(IGraphic* graphic) override {
        _graphic = graphic;
    }

    void unloadDisplay() override {
        _graphic = nullptr;
    }

}

```
