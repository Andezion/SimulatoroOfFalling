#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

class ball
{
public:
    float radius = 0;
    float height = 0;
    float speed = 0.0002;
    /*
    Если скорость отрицательна - значит кидаем мячик вверх
    Если скорость положительна - значит кидаем мячик вниз
    */
    float e = 0;

    CircleShape circle;

    float kinetic_energy = 0;
    float potential_energy = 0;

    bool is_moving = true;
    bool is_up;

    float speed_helper = 0;
    float height_helper = 0;

    float gravity_helper = 0.000098;

    ball(float n_radius, float n_height, float n_speed, float n_e)
    {
        radius = n_radius;
        height = n_height;
        speed = n_speed;
        e = n_e;

        if (speed >= 0)
        {
            is_up = false;
        }
        else
        {
            is_up = true;
        }

        speed_helper = speed;
        height_helper = height;

        circle.setRadius(radius);
        circle.setFillColor(Color::Red);
        circle.setPosition(400 - radius, height);
    }

    int is_speed = 1;
    void type_fall_up()
    {
        if (is_speed)
        {
            if (speed >= 0)
            {
                speed = speed - gravity_helper;
                height = height - speed;
            }
            else
            {
                is_speed = 0;
            }
        }
        else
        {
            if (height <= 580)
            {
                speed = speed + gravity_helper;
                height = height + speed;
            }
            else
            {
                speed = speed - 0.01;
                is_speed = 1;
            }
        }
        circle.setPosition(circle.getPosition().x, height);
    }

    int pointer = 0; // если 0 то падает вниз, если 1 - то летит вверх(отбился)
    void type_fall_down()
    {
        if (pointer)
        {
            if (speed >= 0)
            {
                speed = speed - gravity_helper;
                height = height - speed;
            }
            else
            {
                pointer = 0;
            }
        }
        else
        {
            if (height <= 580)
            {
                speed = speed + gravity_helper;
                height = height + speed;
            }
            else
            {
                speed = speed - 0.01;
                pointer = 1;
            }
        }
        circle.setPosition(circle.getPosition().x, height);
    }

    void draw(RenderWindow& window)
    {
        window.draw(circle);
    }
};

int main(void)
{
	RenderWindow window(VideoMode(800, 600), "Correct");

    ball b(10, 300, 0.1, 0.8); // Создаем мяч с начальной скоростью вверх

    Clock clock;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        b.type_fall_up();

        window.clear();
       
        b.draw(window);
        window.display();
    }

	return 0;
}
