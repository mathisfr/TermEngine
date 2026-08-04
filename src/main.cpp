#include "engine/graphics.hpp"

int main(){
    Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y> graphics;

    graphics.CursorInvisible();
    graphics.MoveCursor(0,0);

    graphics.EraseDisplay();
    graphics.SetBackgroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::CYAN);
    graphics.SetForegroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::RED);
    graphics.InitDrawFrame();
    
    while (true){
        graphics.BeginDraw();

        graphics.Write("Terminal Engine V1", 0, 0);

        graphics.EndDraw();
    }
    return 0;
}