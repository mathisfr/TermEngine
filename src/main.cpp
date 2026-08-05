#include "engine/graphics.hpp"
#include "engine/input.hpp"
#include "engine/primitives.hpp"
#include "engine/physics.hpp"
#include "engine/event.hpp"

class MyCustomCollisionEvent:public IEvent{
    public:
        MyCustomCollisionEvent(void* data) : IEvent(data) {}
        void Trigged() override{
            if(!_data) return;
            Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>* graphics = static_cast<Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>*>(_data);
            graphics->Write("Collision Detected", 0, 7);
            graphics->Bell();
        }
};

int main(){
    Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y> graphics;
    Input input;
    EventManager em;

    em.Subscribe("mycustomcollision", std::make_unique<MyCustomCollisionEvent>(static_cast<void*>(&graphics)));

    graphics.CursorInvisible();
    graphics.MoveCursor(0,0);

    graphics.EnablesAlternativeBuffer();
    graphics.SetBackgroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::CYAN);
    graphics.SetForegroundColor(Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::RED);
    graphics.InitDrawFrame();
    
    Rectangle rectangle(graphics, 'X', 10, 5, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::BLACK, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::BLACK);
    rectangle.SetPos(0,0);
    Square square(graphics, 'X', 4, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Background::RED, Graphics<TERMINAL_SIZE_X,TERMINAL_SIZE_Y>::Color::Foreground::RED);
    square.SetPos(5,3);
    while (true){
        graphics.BeginDraw();
        if (input.ReadInput()){
            if (input.GetReadedChar() == 'q' || input.GetReadedChar() == 'Q'){
                break;
            }
        }

        rectangle.Draw();
        square.Draw();

        if (Physics::SimpleCollision(rectangle, square)){
            em.Notify("mycustomcollision");
        }

        graphics.Write("TermEngine", 0, 0);
        graphics.EndDraw();
    }
    graphics.DisablesAlternativeBuffer();
    return 0;
}