#ifndef INPUT_HPP
#define INPUT_HPP
#include <termios.h>
#include <unistd.h>
#include <vector>

class IControls {
    public:
        virtual ~IControls() = default;
        virtual void Reset() = 0;
};

class AInputAction{
    private:
        const char _keyCode;
    public:
        AInputAction(char keyCode) : _keyCode(keyCode){};
        virtual ~AInputAction() = default;

        virtual void Pressed(std::unique_ptr<IControls>& data) const = 0;

        char GetKeyCode() const{
            return _keyCode;
        }
};

class Input{
    private:
        char _readedchar = '\0';
        std::vector<std::unique_ptr<AInputAction>> _inputActions;
        std::unique_ptr<IControls> _controls;
    public:
    Input() {
        struct termios raw;

        tcgetattr(STDIN_FILENO, &raw);
        raw.c_lflag &= ~(ECHO | ICANON);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }

    void SetupControls(std::unique_ptr<IControls> controls){
        _controls = std::move(controls);
    }

    void AddInputAction(std::unique_ptr<AInputAction> inputAction){
        _inputActions.push_back(std::move(inputAction));
    }

    bool ReadInput(){
        return read(STDIN_FILENO, &_readedchar, 1) > 0; 
    }

    char GetReadedChar(){
        return _readedchar;
    }

    std::unique_ptr<IControls>& GetControls(){
        return _controls;
    }

    bool PressedKey(const char keyCode){
        for (const auto& inputAction: _inputActions){
            if (inputAction->GetKeyCode() == keyCode){
                inputAction->Pressed(_controls);
                return true;
            }
        }
        return false;
    }

    void Reset(){
        _readedchar = '\0';
        _controls->Reset();
    }
};
#endif