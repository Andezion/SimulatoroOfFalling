#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class ball
{
public:
    float radius; // ðàäèóñ 
    float height; // âûñîòà 
    float speed; // ñêîðîñòü 
    float e; // óïðóãîñòü 

    float kinetic_energy = 0; // êèíåòè÷åñêàÿ ýíåðãèÿ ìÿ÷à
    float potencial_energy = 0; // ïîòåíöèàëüíàÿ ýíåðãèÿ ìÿ÷à 
    float initial_height; // íà÷àëüíàÿ âûñîòà
    float initial_speed; // íà÷àëüíàÿ ñêîðîñòü 

    CircleShape circle;

    bool where_to_move; // ïåðåìåííàÿ äëÿ îòñëåæèâàíèÿ íàïðàâëåíèÿ äâèæåíèÿ
    bool is_moving; // ïåðåìåííàÿ äëÿ îòñëåæèâàíèÿ äâèæåíèÿ â öåëîì 

    ball(float n_radius, float n_height, float n_speed, float n_e) // íàø êîíñòðóêòîð 
    {
        radius = n_radius; // ðàäèóñ íàøåãî øàðà 

        height = n_height; // âûñîòà òåêóùàÿ 
        initial_height = n_height; // ñîõðàíÿåì íà÷àëüíóþ âûñîòó

        speed = n_speed; // ñêîðîñòü ìåíÿåìàÿ 
        initial_speed = speed; // ñêîðîñòü íà÷àëüíàÿ

        e = n_e; // êîåôèöèåíò óïðóãîñòè 

        where_to_move = false; // íà÷àëüíîå íàïðàâëåíèå äâèæåíèÿ âíèç
        is_moving = true; // íà÷àëüíîå äâèæåíèå åñòü 

        circle.setRadius(radius);
        circle.setFillColor(Color::Red);
        circle.setPosition(300, height);
    }

    void draw(RenderWindow& window) // îòðèñîâêà 
    {
        window.draw(circle);
    }

    void path()
    {
        float gravity = 0.000098;

        if (initial_height < 20.0f)
        {
            is_moving = false;
            return;
        }
        if (is_moving)
        {
            if (where_to_move)
            {
                speed = speed - gravity;
                height -= speed;
                if (height <= initial_height)
                {
                    height = initial_height;
                    speed = 0;
                    where_to_move = false; // ìåíÿåì íàïðàâëåíèå íà âíèç
                }
            }
            else
            {
                speed = speed + gravity;
                height += speed;
                if (height >= 580.0f)
                {
                    height = 580.0f;

                    if (e * e == 1)
                    {
                        initial_height = initial_height;
                    }
                    else
                    {
                        initial_height = initial_height * e * e;
                    }
                    if (initial_height > 580.0f)
                    {
                        initial_height = 580.0f;
                    }

                    where_to_move = true; // ìåíÿåì íàïðàâëåíèå íà ââåðõ
                }
            }
        }

        circle.setPosition(circle.getPosition().x, height);
    }
};

void energy_law(float speed, float heigth)
{
    float potencial = 1 * heigth * 0.098;
    float kinetic = 1 * speed * speed / 2;
}

int main()
{
    RenderWindow window(VideoMode(900, 600), "Tested");

    ball test(10, 50, 0.0001, 1.3544);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }
        }

        test.path();

        window.clear();

        test.draw(window);

        window.display();
    }

    return 0;
}
