#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Timer.h"

#include <SFML/System.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class TimerManager : public Singleton<TimerManager>, public IManager<string, Timer>
{
    // Clock pour avoir accès à toutes les données de temps
    Clock clock;

    // Temps en seconde depuis le début du programme
    float time;

    // Mettre à jour les timers
    float lastTime;

    // Mettre à jour les compteurs de FPS
    float lastFrameTime;

    // Temps en seconde depuis la dernière image rendue
    float elapsedTime;

    // Vitesse à laquelle le temps s'écoule
    float timeScale;

    // Temps en seconde depuis la dernière image rendue avec le time scale
    float deltaTime;

    // Nombre d'images qui ont été rendu depuis le début
    unsigned int framesCount;

    // Maximum d'image à rendre par seconde
    unsigned int maxFrameRate;

    // Nombre d'image rendu par seconde
    float fps;

    function<void()> renderCallback;

public:
    void SetTimeScale(const float _timeScale)
    {
        timeScale = _timeScale;
    }
    void SetMaxFrameRate(const unsigned int _maxFrameRate)
    {
        maxFrameRate = _maxFrameRate;
    }
    float GetDeltaTime() const
    {
        return deltaTime;
    }
    float GetFPS() const
    {
        return fps;
    }
    void ComputeFPS()
    {
        fps = 1000.0f / (time - lastFrameTime);
    }
    bool Render()
    {
        if (lastFrameTime == 0 || time - lastFrameTime >= 1000.0f / maxFrameRate)
        {
            ComputeFPS();
            lastFrameTime = time;
            return true;
        }

        return false;
    }


    void SetRenderCallBack(function<void()> _callback)
    {
        renderCallback = _callback;
    }

public:
    TimerManager();

private:
    void UpdateTimers();

public:
    void Update();
};

