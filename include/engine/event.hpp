#ifndef EVENT_HPP
#define EVENT_HPP
#include <map>
#include <string>
class IEvent{
    protected:
        void* _data {nullptr};
    public:
        IEvent() = default;
        IEvent(void* data) : _data(data) {}
        virtual ~IEvent() = default;
        IEvent(const IEvent& other) = delete;
        IEvent(IEvent&& other) noexcept = delete;
        IEvent& operator=(const IEvent& other) = delete;
        IEvent& operator=(IEvent&& other) noexcept = delete;

        virtual void Trigged() = 0;
};

class EventManager{
    private:
        std::map<std::string, std::unique_ptr<IEvent>> _events;
    public:
        EventManager() = default;
        ~EventManager() = default;
        EventManager(const EventManager& other) = delete;
        EventManager(EventManager&& other) noexcept = delete;
        EventManager& operator=(const EventManager& other) = delete;
        EventManager& operator=(EventManager&& other) noexcept = delete;

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