#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Timer.h"
#include "Singleton.h"


using namespace std;

class Menu
{


public:

	 virtual bool Show() = 0;
};
