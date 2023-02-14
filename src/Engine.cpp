//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
    resolution = Vector2f(800, 600);
    window.create(VideoMode(resolution.x, resolution.y), "snake", Style::Default);
    window.setFramerateLimit(fps);
    maxLevels = 0;
    checkLevelFiles();

    startTheGame();

}

void Engine::startTheGame() {
    speed = 2;
    snakeDirection = Direction::RIGHT;

    timeSinceLastMove = Time::Zero;

    sectionsToAdd = 0;
    directionQueue.clear();
    currentLevel = 1;
    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;
}

// zacetna kaca
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

void Engine::addSnake() {
    Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    // poisci lokacijo za jabolko
    // nesme biti v kaci ali v zidu

    // Divide the field into sections the size of the apple - remove 2 to exclude the exterior walls
    Vector2f  appleResolution = Vector2f(resolution.x / 20 -2,resolution.y / 20-2);
    Vector2f  newAppleLocation;
    bool badLocation = false;
    srand(time(nullptr));
    // zanka dokler ne najdemo dobre lokacije
    do{
        badLocation= false;
        // generira novo lokacijo
        newAppleLocation.x=(float)(1+rand() / ((RAND_MAX + 1u) / (int)appleResolution.x))*20;
        newAppleLocation.y=(float)(1+rand() / ((RAND_MAX + 1u) / (int)appleResolution.y))*20;

        // Preveri ce je v kaci
        for(auto & s:snake){
            if(s.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x,newAppleLocation.y,20,20))) {
                badLocation = true;
                break;
            }
        }


    // Preveri ce je v steni
    for(auto & w:wallSections){
        if(w.getShape().getGlobalBounds()
        .intersects(Rect<float>(newAppleLocation.x,newAppleLocation.y,20,20))){
            badLocation = true;
            break;
        }
    }

    } while (badLocation);
    apple.setPostion(newAppleLocation);
}

void Engine::togglePause() {
    if(currentGameState == GameState::RUNNING){
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if(currentGameState == GameState::PAUSED){
        currentGameState = lastGameState;
    }
}


//  Preveri level direktorij in preveri da se odpere vsak level file
//  Dodaj dobre level file imena v 'levels' vector in inkrementaj maxLevels;

void Engine::checkLevelFiles() {
    // loadaj Levele
    ifstream levelsManifest("../assets/levels/levels.txt");
    ifstream  testFile;
    for(string manifestLine; getline(levelsManifest, manifestLine);){
        // Preveri da lahko odperemo level file
        testFile.open("../assets/levels/" + manifestLine);
        if(testFile.is_open()){
            // ce ga lahko operemo, dodaj mo v listo obstojecih levelov
            levels.emplace_back("../assets/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

//  Zazeni level z file in preveri 'x' znak da dodas k wall (steni)
void Engine::loadLevel(int levelNumber) {
    string levelFile = levels[levelNumber-1];
    ifstream level(levelFile);
    string line;
    if(level.is_open()){
        for(int y = 0; y < 30; y++){
            getline(level,line);
            for(int x = 0; x<40;x++){
                if(line[x] == 'x'){
                    wallSections.emplace_back(Wall(Vector2f(x * 20,y * 20),Vector2f(20,20)));
                }
            }
        }
    }
    level.close();
}

void Engine::run() {

    Clock clock;

    // loop dela dokler je okno odprto
    while (window.isOpen()) {
        Time dt = clock.restart();

        if(currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER){
            // Ce je pauza, potem precekiramo input (da lahko nadaljujemo), nadaljujemo na neslednji loop
            input();

            //  Narisi konec igre ekran
            if(currentGameState == GameState::GAMEOVER){
                draw();
            }

            sleep(milliseconds(2)); // V spanju da ne obremenjujemo CPU
            continue;
        }
        timeSinceLastMove += dt;


        input();
        update();
        draw();
    }
}
