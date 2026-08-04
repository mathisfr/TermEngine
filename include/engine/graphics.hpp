#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#define TERMINAL_SIZE_X 100
#define TERMINAL_SIZE_Y 30

#include <string>
#include <string_view>
#include <array>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "engine/engineTime.hpp"

template <std::size_t WIDTH = TERMINAL_SIZE_X, std::size_t HEIGHT = TERMINAL_SIZE_Y>
class Graphics {
    public:
        struct Color {
            enum class Background {
                BLACK = 40,
                RED,
                GREEN,
                YELLOW,
                BLUE,
                MAGENTA,
                CYAN,
                WHITE,
                DEFAULT
            };
            enum class Foreground {
                BLACK = 30,
                RED,
                GREEN,
                YELLOW,
                BLUE,
                MAGENTA,
                CYAN,
                WHITE,
                DEFAULT
            };
        };

        struct Pixel {
            char _character;
            Graphics::Color::Background _back_color;
            Graphics::Color::Foreground _character_color;
            Pixel(): _character(' '), _back_color(Graphics::Color::Background::BLACK), _character_color(Graphics::Color::Foreground::WHITE){};
            Pixel(char character): _character(character), _back_color(Graphics::Color::Background::BLACK), _character_color(Graphics::Color::Foreground::WHITE){};
            Pixel(char character, Graphics::Color::Background back_color, Graphics::Color::Foreground character_color): _character(character), _back_color(back_color), _character_color(character_color){};
            bool operator==(const Pixel& other) const{
                return _character == other._character && _back_color == other._back_color && _character_color == other._character_color;
            }
            bool operator!=(const Pixel& other) const{
                return _character != other._character || _back_color != other._back_color || _character_color != other._character_color;
            }
        };
        using FrameBuffer = std::array<std::array<Pixel, WIDTH>, HEIGHT>;
        const static constexpr std::size_t _WIDTH = WIDTH;
        const static constexpr std::size_t _HEIGHT = HEIGHT;

    private:
        static constexpr std::string_view _esc = "\x1b";

        FrameBuffer _currentFrameBuffer{};
        FrameBuffer _lastFrameBuffer{};

        double _frameRate{1000.0/60.0};
        double _beginFrameRateTime{0};
        EngineTime _engineTime;

        Graphics::Color::Background _backgroundColor{Graphics::Color::Background::DEFAULT};
        Graphics::Color::Foreground _foregroundColor{Graphics::Color::Foreground::DEFAULT};

        void CSI(std::string_view csi) {
            std::cout << std::string(_esc) + '[' + std::string(csi);
        }

    public:
        Graphics() {
            CSI("8;" + std::to_string(HEIGHT) + ";" + std::to_string(WIDTH) + "t");
        }

        ~Graphics() = default;
        Graphics(const Graphics&) = delete;
        Graphics& operator=(const Graphics&) = delete;

        FrameBuffer GetCurrentFrameBuffer(){
            return _currentFrameBuffer;
        }
        FrameBuffer GetLastFrameBuffer(){
            return _lastFrameBuffer;
        }

        void ClearFrameBuffer(FrameBuffer&& fb) {
            Pixel empty;
            empty._back_color = _backgroundColor;
            empty._character_color = _foregroundColor;
            for (auto& row : fb) {
                row.fill(empty);
            }
        }

        void ClearFrameBuffer(FrameBuffer& fb) {
            Pixel empty;
            empty._back_color = _backgroundColor;
            empty._character_color = _foregroundColor;
            for (auto& row : fb) {
                row.fill(empty);
            }
        }

        void InitDrawFrame() {
            ClearFrameBuffer(_currentFrameBuffer);
            ClearFrameBuffer(_lastFrameBuffer);
            SaveCursorPosition();
            for (std::size_t y = 0; y < HEIGHT; y++) {
                for (std::size_t x = 0; x < WIDTH; x++) {
                    Pixel pixel_current = _currentFrameBuffer[y][x];
                    MoveCursor(x + 1, y + 1);
                    if (pixel_current._character == '\0')
                        ApplyEmptyPixel(pixel_current);
                    else
                        ApplyPixel(pixel_current);
                }   
            }
            RestoreCursorPosition();
        }

        void EraseDisplay() {
            CSI("2J");
        }

        Graphics::Color::Background GetBackgroundColor(){
            return _backgroundColor;
        }

        void SetBackgroundColor(Graphics::Color::Background color){
            _backgroundColor = color;
            //CSI("1;" + std::to_string(static_cast<int>(color)) + "m");
        }

        Graphics::Color::Background GetForegroundColor(){
            return _foregroundColor;
        }

        void SetForegroundColor(Graphics::Color::Foreground color){
            _foregroundColor = color;
            //CSI("1;" + std::to_string(static_cast<int>(color)) + "m");
        }

        void ApplyPixel(Pixel &pixel){
            std::cout << std::string(_esc) + "[1;" + std::to_string(static_cast<int>(pixel._character_color)) + ';' + std::to_string(static_cast<int>(pixel._back_color)) + 'm' + pixel._character;
        }


        void ApplyEmptyPixel(Pixel &pixel){
            std::cout << std::string(_esc) + "[1;" + std::to_string(static_cast<int>(pixel._character_color)) + ';' + std::to_string(static_cast<int>(pixel._back_color)) + 'm' + ' ';
        }

        void CursorVisible() {
            CSI("?25h");
        }

        void CursorInvisible() {
            CSI("?25l");
        }

        void MoveCursor(std::size_t x, std::size_t y) {
            CSI(std::to_string(y) + ";" + std::to_string(x) + "H");
        }

        void SaveCursorPosition() {
            CSI("s");
        }

        void RestoreCursorPosition() {
            CSI("u");
        }

        static void Bell(){
            std::cout << "\x07";
        }

        void PutChar(char c, std::size_t x, std::size_t y) {
            if (x < WIDTH && y < HEIGHT) {
                Pixel pixel;
                pixel._character = c;
                pixel._back_color = _backgroundColor;
                pixel._character_color = _foregroundColor;
                _currentFrameBuffer[y][x] = pixel;
            }
        }

        void PutPixel(Pixel pixel, std::size_t x, std::size_t y) {
            if (x < WIDTH && y < HEIGHT) {
                _currentFrameBuffer[y][x] = pixel;
            }
        }

        void Write(std::string_view str, std::size_t x, std::size_t y) {
            std::size_t xIncrement = 0;
            for (char c : str) {
                PutChar(c, x + xIncrement, y);
                xIncrement++;
            }
        }

        void BeginDraw(){
            ClearFrameBuffer(_currentFrameBuffer);
            _beginFrameRateTime = _engineTime.GetTimePassedInMilli();
        }
        void EndDraw() {
            SaveCursorPosition();
            for (std::size_t y = 0; y < HEIGHT; y++) {
                for (std::size_t x = 0; x < WIDTH; x++) {
                    Pixel pixel_current = _currentFrameBuffer[y][x];
                    Pixel pixel_last = _lastFrameBuffer[y][x];
                    if (pixel_current == pixel_last) continue;
                    int xinc = 0;
                    while ((xinc + x) < WIDTH && pixel_current != pixel_last){
                        xinc++;
                    }
                    
                    MoveCursor(x + 1, y + 1);
                    
                    int offset = 0;
                    while (offset < xinc){
                        pixel_current = _currentFrameBuffer[y][x + offset];
                        _lastFrameBuffer[y][x + offset] = pixel_current;
                        if (pixel_current._character == '\0')
                            ApplyEmptyPixel(pixel_current);
                        else
                            ApplyPixel(pixel_current);
                        offset++;
                    }
                    x = x + offset;
                }   
            }
            RestoreCursorPosition();

            double endFrameRateTime = _engineTime.GetTimePassedInMilli();
            double diffFrameRateTime = endFrameRateTime - _beginFrameRateTime;
            std::cout << std::flush;
            if (diffFrameRateTime < _frameRate){
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(_frameRate - diffFrameRateTime));
            }
        }
};

#endif // Graphics_HPP