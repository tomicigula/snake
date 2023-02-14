//
// Created by Filip Potočnik on 08/02/2023.
//

#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "../headers/Snake.h"
#include "apple.h"
#include "wall.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include "fstream"

using namespace sf;
using namespace std;

class Engine {
private:
    // Okno
    Vector2f resolution;
    RenderWindow window;
    const unsigned int fps = 60;
    static const Time TimePerFrame;

    vector<Snake> snake;

    int snakeDirection;
    int speed;
    int sectionsToAdd; // koliko repov dodati kaci

    Apple apple;

    vector<Wall>wallSections;
    int currentLevel;
    int maxLevels;
    vector<String> levels;

    Time timeSinceLastMove;
    deque<int> directionQueue; //vrsta pritisnjene tipke

    int currentGameState;
    int lastGameState;  // For starting the last state the game was in when pausing

public:
    enum Direction{UP, RIGHT, DOWN, LEFT};
    enum GameState {RUNNING, PAUSED, GAMEOVER};

    Engine();

    void input();

    void addDirection(int newDirection);

    void update();

    void draw();

    void newSnake();

    void addSnake();

    void moveApple();

    void checkLevelFiles();

    void loadLevel(int levelNumber);

    void startTheGame();

    void togglePause();

    void run();
};


#endif //SNAKE_ENGINE_H
