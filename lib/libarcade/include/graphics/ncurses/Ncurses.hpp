#include "Arcade/display.hpp"
#include <ncurses.h>

class NcursesGraphic : public Arcade::IDisplay {

public:
    void open() override;

    void close() noexcept override;

    bool isOpen() const noexcept override;

    void clear() override;

    void display() override;

    void draw(const Arcade::Shapes::Point& point) override;

    void draw(const Arcade::Shapes::Rectangle& rect) override;

    void draw(const Arcade::Text& text) override;

    std::optional<Arcade::Event> pollEvent() override;

    std::pair<Arcade::Coordinate, Arcade::Coordinate> mousePosition() const override;

    std::pair<Arcade::Coordinate, Arcade::Coordinate> size() const noexcept override;

    std::string_view libraryName() const noexcept override;

    void setIsWinOpen(bool);

    bool getIsWinOpen() const;

    std::optional<Arcade::Event> switchCaseKey(int);

    WINDOW *_window;

private:
    bool _isWinOpen = false;
};
