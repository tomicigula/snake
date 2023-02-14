//
// Created by Filip Potočnik on 08/02/2023.
//

#include "../headers/Engine.h"

int main() {

    Engine engine;
    engine.run();

    return 0;

    /*
    auto window = sf::RenderWindow{ { 800, 600 }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
     */
}