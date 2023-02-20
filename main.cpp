
#include  <SFML\Graphics.hpp>
#include <iostream>

#define SCREEN_HIGHT 960
#define SCREEN_WIDTH 1200

class Circle
{
public:
    Circle(float posx, float posy, float velx, float vely, float accelerationx, float accelerationy);

    sf::Vector2f get_pos() {
        return pos;
    }
    void render(sf::RenderWindow& window) {
        s.setPosition(pos);
        //std::cout <<"posx: "<< pos.x << " posy: " << pos.y << " vely: " << vel.y << " accy: " << acc.y <<" velx: " <<vel.x<<" accx: "<<acc.x<< std::endl;
        window.draw(s);
    }
    void velocity() {
        pos.x += vel.x;
        pos.y += vel.y;
    }
    void acceleration() {
        vel.x += acc.x;
        vel.y += acc.y;
    }

    void collision() {
        if (pos.x <= 0) {
            vel.x = -vel.x;
            pos.x = 0;
        }
        if (pos.y <= 0) {
            vel.y = -vel.y;
            pos.y = 0;
        }
        if ((pos.x + radius * 2) >= SCREEN_WIDTH) {
            pos.x = SCREEN_WIDTH - radius*2;
            vel.x = -vel.x;
        }
        if ((pos.y + radius * 2) >= SCREEN_HIGHT) {
            pos.y = SCREEN_HIGHT - radius*2;
            vel.y = -vel.y;
        }
    }
    
    /*void move() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            pos.x = get_pos().x - 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            pos.x = get_pos().x + 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            pos.y = get_pos().y - 1;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            pos.y = get_pos().y + 1;
        }
    }*/


    ~Circle();

private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    sf::CircleShape s;
    int radius = 20;
}; 

Circle::Circle(float posx, float posy, float velx, float vely, float accelerationx, float accelerationy)
{
    pos.x = posx;
    pos.y = posy;

    vel.x = velx;
    vel.y = vely;

    acc.x = accelerationx;
    acc.y = accelerationy;
    
    s.setFillColor(sf::Color::Magenta);
    s.setRadius(radius);

}

Circle::~Circle()
{
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HIGHT), "title");
    window.setFramerateLimit(60);

    //CRICLE declaration
    Circle circle(240, 200, 5.7f, 8.6f, 2.2f, 4.4f);//posx posy velx vely accelerationx accelerationy

    sf::Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }

        }
        //render
        window.clear();//clear old frames
        
        //draw game
        
        circle.acceleration();
        circle.velocity();
        circle.collision();
        circle.render(window);

        window.display();


    }

    return 0;
}
