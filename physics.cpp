#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>


const int grav = 10;

struct Object{
    int num;
    sf::VideoMode size;
    int mass;
    float elasticity;
    float friction;
    sf::Vector2i pos;
    sf::Vector2i vel;

    sf::RenderWindow window;

    Object(int num, sf::VideoMode size, int mass, float elasticity, float friction, sf::Vector2i pos, sf::Vector2i vel):
        num(num),size(size), mass(mass), elasticity(elasticity), friction(friction), pos(pos), vel(vel), window(size, std::to_string(num), sf::Style::None){}

};

void move(sf::Vector2i& pos, char direction, int pixels){
    
    switch(direction){
        case 'x':
            pos.x += pixels;
            break;
        case 'y':
            pos.y += pixels;
            break;
    }

}

void mainLoop(Object& window){
    sf::Event event;
        while(window.window.pollEvent(event)){

            if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
                window.window.close();
            }
        }

        if(window.pos.x + window.window.getSize().x >= 1920){
            window.vel.x = -window.vel.x*window.elasticity;
            window.pos.x = 1920 - window.window.getSize().x -1;
        }

        if(window.pos.x <= 0){
            window.vel.x = -window.vel.x*window.elasticity;
            window.pos.x = 0 + 1;
        }

        window.vel.y += grav;
        move(window.pos, 'y', window.vel.y);
        move(window.pos, 'x', window.vel.x);

        if(window.pos.y + window.window.getSize().y >= 1080){
            window.vel.y = -window.vel.y*window.elasticity;
            window.pos.y = 1080 - window.window.getSize().y - 1;

            window.vel.x -= window.vel.x*window.friction;
        }
        if(window.pos.y <= 32){
            window.vel.y = -window.vel.y*window.elasticity;
            window.pos.y = 32;
        }

        window.window.setPosition(window.pos);
}

int main(){
    Object window1(1, sf::VideoMode(200, 300), 10, 0.5, 0.01, sf::Vector2i(200, 200), sf::Vector2i(100, 20));

    Object window2(1, sf::VideoMode(700, 200), 10, 0.1, 0.1, sf::Vector2i(500, 200), sf::Vector2i(20, 20));

    while(window1.window.isOpen()){

        mainLoop(window1);
        mainLoop(window2);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    return 0;
}