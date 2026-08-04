#include "engine/graphics.hpp"
#include "engine/input.hpp"

int main(){
    Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y> graphics;
    Input input;

    graphics.CursorInvisible();
    graphics.MoveCursor(0,0);

    graphics.EnablesAlternativeBuffer();
    graphics.SetBackgroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::CYAN);
    graphics.SetForegroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::RED);
    graphics.InitDrawFrame();
    
    while (true){
        graphics.BeginDraw();
        if (input.ReadInput()){
            if (input.GetReadedChar() == 'q' || input.GetReadedChar() == 'Q'){
                break;
            }
        }
        graphics.Write("TermEngine", 0, 0);
        graphics.EndDraw();
    }
    graphics.DisablesAlternativeBuffer();
    return 0;
}