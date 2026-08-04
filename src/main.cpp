#include <iostream>
#include "engine/graphics.hpp"
#include "engine/engineTime.hpp"
#include "engine/input.hpp"
#include "engine/primitives.hpp"
#include "engine/physics.hpp"
#include <unistd.h>
#include <vector>
#include <cmath>

int main(){
    Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y> graphics;

    graphics.CursorInvisible();
    graphics.MoveCursor(0,0);

    graphics.EraseDisplay();
    graphics.SetBackgroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::CYAN);
    graphics.SetForegroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::RED);
    graphics.ClearFrameBuffer(graphics.GetCurrentFrameBuffer());
    graphics.ClearFrameBuffer(graphics.GetLastFrameBuffer());
    graphics.InitDrawFrame();
    
    while (true){
        graphics.BeginDraw();

        graphics.Write("Terminal Engine V1", 0, 0);

        graphics.EndDraw();
    }
    return 0;
}