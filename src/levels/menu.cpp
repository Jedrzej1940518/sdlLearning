
#include "menu.hpp"

#include <SFML/Window/Event.hpp>

namespace levels
{
    void setButton(rendering::Button &button, sf::FloatRect rect, sf::Font &font, std::string &&str, rendering::Button::CallbackFunction callback)
    {

        button.setSize({rect.width, rect.height});
        button.setPosition({rect.left, rect.top});
        button.setFillColor(globals::GREY);
        button.setOutlineColor(sf::Color::Black);
        button.setOutlineThickness(2);
        button.setCallback(callback);

        auto &text = button.getText();
        text.setString(str);
        text.setPosition(rect.left, rect.top);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color::Black);
    }
    Menu::Menu(LevelType &level) : Level{level}
    {
        if (!font.loadFromFile(getDataPath("graphics/fonts/TiltNeon-Regular.ttf")))
            std::cerr << "Error loading font" << std::endl;

        buttons.push_back(&newGameButton);
        buttons.push_back(&continueButton);
        buttons.push_back(&quitButton);

        setButton(newGameButton, {buttonX, buttonY, buttonW, buttonH}, font, "New Game", [&level]()
                  { level = LevelType::ARENA; });

        setButton(continueButton, {buttonX, buttonY + buttonH + 50, buttonW, buttonH}, font, "Continue", [&level]()
                  { level = LevelType::ARENA; });

        setButton(quitButton, {buttonX, buttonY + (buttonH + 50) * 2, buttonW, buttonH}, font, "Quit", []()
                  { globals::WINDOW->close(); });
    }

    void Menu::handleEvents(const sf::Event &event)
    {
        if (event.type == sf::Event::Closed)
            globals::WINDOW->close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            for (auto &button : buttons)
                if (button->handleClick(event.mouseButton))
                    break;
        }
    }

    void Menu::render()
    {
        globals::WINDOW->clear(sf::Color::White);
        globals::WINDOW->draw(background.getSprite());

        for (auto &button : buttons)
        {
            globals::WINDOW->draw(*button);
            globals::WINDOW->draw(button->getText());
        }

        globals::WINDOW->display();
    }
} // namespace levels
