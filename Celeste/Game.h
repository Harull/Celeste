#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player;
class Hud;

enum GameState
{
    ST_MENU, ST_VILLAGE, ST_ATTACK
};

enum ViewState
{
    VS_DEFAULT, VS_UNSCOPED, VS_SCOPED
};

class Game
{
    static RenderWindow mainWindow;
    static GameState state;
    static Player* player;
    static View* currentView;
    static View unscopedView;
    static View scopedView;
    static ViewState viewState;

    Hud* hud;

public:
    static void SetGameState(const GameState& _state)
    {
        state = _state;
    }
    static GameState GetGameState()
    {
        return state;
    }

    static Vector2f GetWindowsSize()
    {
        return Vector2f(mainWindow.getSize());
    }
    static RenderWindow& GetWindow()
    {
        return mainWindow;
    }
    static Player* GetPlayer()
    {
        return player;
    }

    static View* GetCurrentView()
    {
        return currentView;
    }
    static void SetViewState(const ViewState& _viewState)
    {
        viewState = _viewState;
        UpdateCurrentView();
        UpdateViewPosition();
    }

public:
    Game();
    ~Game();

public:
    void Launch();

private:
    void Start();
    void InitUnscopedView();
    void InitScopedView();
    static void UpdateCurrentView();
    static void UpdateViewPosition();
    void Update();
    void Stop();
    void UpdateWindow();
};
