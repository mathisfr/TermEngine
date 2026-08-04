#ifndef EVENT_HPP
#define EVENT_HPP
#include <map>
#include <string>
class IEvent{
    protected:
        void* _data {nullptr};
    public:
        IEvent(){};
        virtual ~IEvent() = default;
        IEvent(void* data) : _data(data) {}
        virtual void Trigged() = 0;
};

class EventManager{
    private:
        std::map<std::string, std::unique_ptr<IEvent>> _events;
    public:
        void Subscribe(std::string key_notify, std::unique_ptr<IEvent> event){
            _events.emplace(key_notify, std::move(event));
        }
        void Unsubscibe(std::string key_notify){
            _events.erase(key_notify);
        }
        void Notify(std::string key_notify) const {
            if (auto it = _events.find(key_notify); it != _events.end()) {
                it->second->Trigged();
            }
        }
};
#endif