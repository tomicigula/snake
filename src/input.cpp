//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"


void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        // zapre okno
        if (event.type == Event::Closed) {
            window.close();
        }

        // tipkovnica input
        if (event.type == Event::KeyPressed) {
            // zapre okno
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }

            // Pauza
            if(event.key.code == Keyboard::Pause){
                togglePause();
            }

            // Nova igra
            if(currentGameState == GameState::GAMEOVER){
                if(event.key.code == Keyboard::Enter){
                    startTheGame();
                }
            }

            // smer
            if(event.key.code == Keyboard::Up){
                addDirection(Direction::UP);
            }
            else if(event.key.code == Keyboard::Down){
                addDirection(Direction::DOWN);
            }
            else if(event.key.code == Keyboard::Left){
                addDirection(Direction::LEFT);
            }
            else if(event.key.code == Keyboard::Right){
                addDirection(Direction::RIGHT);
            }

        }
    }
}

void Engine::addDirection(int newDirection) {
    if(directionQueue.empty()){
        directionQueue.emplace_back(newDirection);
    }else{
        if(directionQueue.back() != newDirection){
            directionQueue.emplace_back(newDirection);
        }
    }
}
