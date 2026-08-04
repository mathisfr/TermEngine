#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include <cstdlib>
#include "engine/graphics.hpp"

class Primitives
{
protected:
    Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& _graphicsContext;
    Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Pixel _pixel;
    bool _isVisible {true};
public:
    Primitives(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext): _graphicsContext(graphicsContext), _pixel(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Pixel()) {};
    Primitives(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, char character): _graphicsContext(graphicsContext), _pixel(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Pixel(character)) {};
    Primitives(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, char character, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background back_color, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground character_color): _graphicsContext(graphicsContext), _pixel(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Pixel(character, back_color, character_color)) {};
    virtual void Draw() = 0;

    bool GetVisibilty(){
        return _isVisible;
    }
    bool SetVisiblility(bool visibility){
        return _isVisible = visibility;
    }

    virtual ~Primitives() = default;
};

class Square: public Primitives{
    private:
        std::size_t _size;

        std::size_t _posX;
        std::size_t _posY;
    public:
        Square(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, std::size_t size = 10): Primitives(graphicsContext), _size(size){};
        Square(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, char character, std::size_t size = 10): Primitives(graphicsContext, character), _size(size){};
        Square(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, char character, std::size_t size = 10, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background back_color = Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::DEFAULT, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground character_color = Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::DEFAULT): Primitives(graphicsContext, character, back_color, character_color), _size(size){};
        virtual void Draw() override{
            if (!_isVisible) return;
            for (std::size_t y = 0; y < _size; y++){
                for (std::size_t x = 0; x < _size; x++){
                    _graphicsContext.PutPixel(_pixel, x + _posX, y + _posY);
                }
            }
        }

        void SetPos(std::size_t x, std::size_t y){
            _posX = x;
            _posY = y;
        }
        std::size_t GetPosX(){
            return _posX;
        }
        std::size_t GetPosY(){
            return _posY;
        }
        void SetSize(std::size_t size){
            _size = size;
        }
        std::size_t GetSize(){
            return _size;
        }
};

class Rectangle: public Primitives{
    private:
        std::size_t _sizeX;
        std::size_t _sizeY;

        std::size_t _posX;
        std::size_t _posY;
    public:
        Rectangle(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, std::size_t sizeX = 10, std::size_t sizeY = 10): Primitives(graphicsContext), _sizeX(sizeX), _sizeY(sizeY){};
        Rectangle(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, char character, std::size_t sizeX = 10, std::size_t sizeY = 10): Primitives(graphicsContext, character), _sizeX(sizeX), _sizeY(sizeY){};
        Rectangle(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>& graphicsContext, char character, std::size_t sizeX = 10, std::size_t sizeY = 10, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background back_color = Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::DEFAULT, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground character_color = Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::DEFAULT): Primitives(graphicsContext, character, back_color, character_color), _sizeX(sizeX), _sizeY(sizeY){};
        virtual void Draw() override{
            if (!_isVisible) return;
            for (std::size_t y = 0; y < _sizeY; y++){
                for (std::size_t x = 0; x < _sizeX; x++){
                    _graphicsContext.PutPixel(_pixel, x + _posX, y + _posY);
                }
            }
        }

        void SetPos(std::size_t x, std::size_t y){
            _posX = x;
            _posY = y;
        }
        std::size_t GetPosX(){
            return _posX;
        }
        std::size_t GetPosY(){
            return _posY;
        }
        void SetSizeXY(std::size_t sizeX, std::size_t sizeY){
            _sizeX = sizeX;
            _sizeY = sizeY;
        }
        std::size_t GetSizeX(){
            return _sizeX;
        }
        std::size_t GetSizeY(){
            return _sizeY;
        }
};

#endif