#include "button.hpp"

namespace rendering
{
    Button::Button()
    {
    }
    void Button::setCallback(CallbackFunction callbackFunction)
    {
        callback = callbackFunction;
    }
    void Button::click()
    {
        callback();
    }
    sf::Text &Button::getText()
    {
        return text;
    }
    bool Button::handleClick(const sf::Event::MouseButtonEvent &mouseButton)
    {
        if (mouseButton.button == sf::Mouse::Button::Left && isInside(mouseButton.x, mouseButton.y))
        {
            click();
            return true;
        }

        return false;
    }
    bool Button::isInside(int x, int y)
    {
        auto pos = getPosition();
        auto sz = getSize();

        return (x >= pos.x && x <= pos.x + sz.x && y >= pos.y && y <= pos.y + sz.y);
    }
    // void Button::renderButton()
    // {
    //     SDL_SetRenderDrawColor(gRenderer, 128, 128, 128, 255);
    //     SDL_RenderFillRect(gRenderer, &position);
    //     SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    //     SDL_RenderDrawRect(gRenderer, &position);

    //     SDL_Rect textRectangle = {position.x + position.w / 2 - textW / 2, position.y + position.h / 2 - textH / 2, textW,
    //                               textH};

    //     SDL_RenderCopy(gRenderer, texture, NULL, &textRectangle);
    // }

    // bool Button::isInside(const SDL_Point &p)
    // {
    //     return (p.x >= position.x && p.x <= position.x + position.w && p.y >= position.y && p.y <= position.y + position.h);
    // }

} // namespace rendering