#pragma once
#include "IManageable.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

using namespace std;
using namespace sf;

class Timer : public IManageable<string>
{
    function<void()> callback;
    float currentDuration;
    float duration;
    bool isRunning;
    bool isLoop;

public:
    bool IsRunning() const
    {
        return isRunning;
    }

public:
    template <class Class, typename... Args>
    Timer(const string& _id, Class* _owner, void (Class::* _callback)(Args...), const Time& _time,
        const bool _startRunning = true, const bool _isLoop = false, const Args&... _args) : IManageable(_id)
    {
        Register();

        callback = [_owner, _callback, _args...]()
            {
                (_owner->*_callback)(_args...);
            };
        currentDuration = 0.0f;
        duration = static_cast<float>(_time.asMilliseconds());
        isRunning = _startRunning;
        isLoop = _isLoop;

        //const function<void()>& _callbackWithArgs = bind(_callback, _owner, _args...);
    }

    Timer(const string& _id, const function<void()>& _callback, const Time& _time,
        const bool _startRunning = true, const bool _isLoop = false);

private:
    virtual void Register() override;

public:
    void Update(const float _deltaTime);
    void Start();
    void Pause();
    void Reset();
    void Stop();
};

