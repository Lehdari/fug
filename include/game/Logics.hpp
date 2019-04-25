//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGICS_HPP
#define ECSTESTGAME_LOGICS_HPP


#include <engine/Logic.hpp>
#include <SFML/Graphics.hpp>


LOGIC(Logic_Ball) {
    Logic_Ball(const EntityId& paddleId);

    void operator()(Ecs& ecs, const EntityId& eId);

    EntityId    _paddleId;
    bool        _followPaddle;
};

LOGIC(Logic_Paddle) {
    void operator()(Ecs& ecs, const EntityId& eId);
};

LOGIC(Logic_GameManager) {
    Logic_GameManager(sf::RenderWindow& window, sf::Texture& blockTexture);

    void operator()(Ecs& ecs, const EntityId& eId);

    static sf::Font     __font;
    static sf::Font initFont();

    sf::RenderWindow&   _window;
    sf::Texture&        _blockTexture;
    
    sf::Text            _text;

    int64_t             _points;
    int64_t             _lives;
};


#endif //ECSTESTGAME_LOGICS_HPP

