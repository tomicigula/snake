
#include "../headers/apple.h"

Apple::Apple() {
    Vector2f  startingPosition (400,300);
    sprite.setSize(Vector2f(20,20));
    sprite.setFillColor((Color::Red));
    sprite.setPosition(startingPosition);
}

void Apple::setPostion(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

RectangleShape Apple::getSprite() {
    return sprite;
}