
#include "../headers/Engine.h"

void Engine::update() {
   // Posodobi pozicijo kace
    if(timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()){
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f  lastSectionPosition = thisSectionPosition;

        // Preveri ce je kaj v inputu
        if(!directionQueue.empty()){
            // Pazimo da ne zamenjamo smeri

            switch (snakeDirection) {
                case Direction::UP:
                    if(directionQueue.front() != Direction::DOWN){
                        snakeDirection = directionQueue.front();
                    }
                break;
                case Direction::DOWN:
                    if(directionQueue.front() != Direction::UP){
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::LEFT:
                    if(directionQueue.front() != Direction::RIGHT){
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::RIGHT:
                    if(directionQueue.front() != Direction::LEFT){
                        snakeDirection = directionQueue.front();
                    }
                    break;

            }
            directionQueue.pop_front();
        }

        // ali moramo povecati kaco
        if(sectionsToAdd ){
            addSnake();
            sectionsToAdd--;
        }

        // Update pozicijo kacje glave
        switch (snakeDirection) {
            case Direction::RIGHT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::DOWN:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
            case Direction::LEFT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;
        }

        // Update pozicijo rep kace
        for(int s = 1; s<snake.size();s++){
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // Zaženi funkcijo posodabljanja razdelka kača
        for(auto & s:snake){
            s.update();
        }

        // Collision dection - Apple
        if(snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())){
            // pojedli smo jabolko, dodaj rep in dodaj hitrost, premakni jabolko

            sectionsToAdd += 4;
            speed++;
            moveApple();
        }

        // Telo kace
        for(int s = 1;s < snake.size();s++){
            if(snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())){
                //  Konec igre
                currentGameState = GameState::GAMEOVER;
            }
        }

        // stena
        for(auto & w:wallSections){
            if(snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())){
                //  Konec igre
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Resetiraj zadnjo potezo(premik)
        timeSinceLastMove = Time::Zero;


    }// KONEC update pozicije kace

}