#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Singleton.h"

using namespace sf;
using namespace std;

class FirstMenu : public Menu, public Singleton<FirstMenu>
{
private:
    Text* play;
    Text* options;
    Text* exit;
    Sprite* background;
    Font* font;



    void HandleMouseClick(Mouse::Button _button, const Vector2i& _mousePosition, RenderWindow& _window);
    void HandleEvents(RenderWindow& _window);

public:

    vector<Drawable*>& GetDrawables()  {

        vector<Drawable*> drawables;
        drawables.push_back(background);
        drawables.push_back(play);
        drawables.push_back(options);
        drawables.push_back(exit);
        return drawables;
    }

    FirstMenu();
    ~FirstMenu();

    void Init();
    virtual bool Show() override;

};