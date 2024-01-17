#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Paint");
    window.clear(sf::Color::White);
    window.display();

    std::vector<sf::Vertex> lines;

    sf::Vector2i* positionDrawingStart = nullptr;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                std::cout << position.x << ',' << position.y << std::endl;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                positionDrawingStart = new sf::Vector2i();
                *positionDrawingStart = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (positionDrawingStart != nullptr) {
                    std::cout << "Drawing line" << std::endl;
                    sf::Vector2i positionDrawingEnd = sf::Mouse::getPosition(window);

                    sf::Vector2f startPos(static_cast<float>(positionDrawingStart->x), static_cast<float>(positionDrawingStart->y));
                    sf::Vector2f endPos(static_cast<float>(positionDrawingEnd.x), static_cast<float>(positionDrawingEnd.y));

                    lines.push_back(sf::Vertex(startPos, sf::Color::Black));
                    lines.push_back(sf::Vertex(endPos, sf::Color::Black));

                    delete positionDrawingStart;
                    positionDrawingStart = nullptr;
                }
            }
        }

        window.clear(sf::Color::White);
        // Draw your shapes or content here
        window.draw(lines.data(), lines.size(), sf::Lines);
        window.display();
    }

    return EXIT_SUCCESS;
}