#include "Menu.h"

void Menu::TransitionUnFill()
{
	const std::function<void()>& _callback2 = [&]() {
		Fade(backgroundShape, (unsigned int)currentAlpha);
		MultiFade(levelTexts, (unsigned int)currentAlpha);

		currentAlpha += alphaFactor;
		if (currentAlpha <= 0 || currentAlpha >= 255)
		{
			timer->Pause();
			timer->Reset();
			canClick = true;
		}};
	timer = new Timer("FadeTimer2", _callback2, sf::seconds(0.01f), true, true);
}

void Menu::ShowOptions(sf::RenderWindow& window)
{
	bool isSoundMuted = false;
	int _currentVolume;

    sf::Font _font;
    if (!_font.loadFromFile("Assets/Fonts/Renogare.otf")) {
        cerr << "ERROR - Font not loaded" << endl;
        return;
    }

    sf::Texture _backgroundTexture;
    if (!_backgroundTexture.loadFromFile("Assets/Background/options_background.png")) {
        std::cerr << "ERROR - Texture du fond d'écran non chargée" << std::endl;
    }

    sf::Sprite _backgroundSprite(_backgroundTexture);
    _backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / _backgroundSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / _backgroundSprite.getLocalBounds().height
    );

	sf::Text _muteSound("Mute Sound :", _font, 50);
	_muteSound.setPosition(700, 500);

	sf::RectangleShape _checkbox(sf::Vector2f(40, 40));
	_checkbox.setPosition(1080, 510);

    sf::Text _title("Options", _font, 80);
    _title.setPosition(180, 100);

    sf::Text _musicVolumeLabel("Music volume : ", _font, 50);
    _musicVolumeLabel.setPosition(700, 400);

    sf::Text _volumeLevel("10", _font, 50);
    _volumeLevel.setPosition(1200, 400);

    sf::Text _decreaseVolume("<", _font, 50);
    _decreaseVolume.setPosition(1160, 400);

    sf::Text _increaseVolume(">", _font, 50);
    _increaseVolume.setPosition(1275, 400);

    sf::Text _back("Back", _font, 50);
    _back.setPosition(1700, 950);



    while (window.isOpen())
    {
        sf::Event _event;
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                window.close();

            if (_event.type == sf::Event::MouseButtonPressed)
            {
                if (_event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f _mousePosition(sf::Mouse::getPosition(window));

                    if (_decreaseVolume.getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
                    {
                        _currentVolume = std::stoi(_volumeLevel.getString().toAnsiString());
                        if (_currentVolume > 1)
                            _volumeLevel.setString(std::to_string(_currentVolume - 1));
                        MusicManager::GetInstance().DecreaseVolume();
                    }
                    else if (_increaseVolume.getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
                    {
                        _currentVolume = std::stoi(_volumeLevel.getString().toAnsiString());
                        if (_currentVolume < 10)
                            _volumeLevel.setString(std::to_string(_currentVolume + 1));
                        MusicManager::GetInstance().IncreaseVolume(); 
                    }
                    else if (_back.getGlobalBounds().contains((float)_mousePosition.x, (float)_mousePosition.y))
                    {
                        return;
                    }
					else if (_checkbox.getGlobalBounds().contains(_mousePosition.x, _mousePosition.y))
					{
						isSoundMuted = !isSoundMuted; 

						if (isSoundMuted)
						{
							MusicManager::GetInstance().MuteVolume();
						}
						else
						{
							_currentVolume = std::stoi(_volumeLevel.getString().toAnsiString());
							MusicManager::GetInstance().UnmuteVolume(_currentVolume);
						}
					}
                }
            }
        }

        window.clear();
        window.draw(_backgroundSprite);
        window.draw(_title);
        window.draw(_back);
        window.draw(_musicVolumeLabel);
		window.draw(_muteSound);
		window.draw(_checkbox);
        window.draw(_decreaseVolume);
        window.draw(_volumeLevel);
        window.draw(_increaseVolume);
        window.display();
    }
}


