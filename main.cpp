#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

const float g = 9.81f;

class object
{
public:
    float mass; // масса 
    float speed; // начальная скорость 
    float radius; // радиус 
    float uskor; // ускорение 
    float angle; // угол броска
    float heigth; // высота 
    float energy; // энергия объекта 

    CircleShape ball;

    object(float n_mass, float n_speed, float n_radius, float n_uskor, float n_angle, float n_heigth)
    {
        mass = n_mass;
        speed = n_speed;
        radius = n_radius;
        uskor = n_uskor;
        angle = n_angle;
        heigth = n_heigth;
         
        ball.setRadius(radius);
        ball.setFillColor(Color::Red);
        ball.setPosition(30, 545 - heigth * 10);
    }

    Vector2f getPos() const
    {
        return ball.getPosition();
    }

    void draw(RenderWindow& window)
    {
        window.draw(ball);
    }

    Vector2f handler1(float time) // случай свободного падения 
    {
        float temp = heigth + speed * time - 0.5f * time * time * g;
        speed -= g * 0.25f;

        if (temp < 0)
        {
            temp = 0;
            speed = 0;
        }

        float pos_new = 545 - temp * 10;
        ball.setPosition(ball.getPosition().x, pos_new);

        return ball.getPosition();
    }
};

bool isValidChar(char c, const string& currentInput) // это всё создано для проверки ввода 
{
    if (isdigit(c) || c == '.') 
    {
        if (c == '.' && currentInput.find('.') != string::npos) 
        {
            return false;
        }
        return true;
    }
    if (c == '-' && currentInput.empty()) 
    {
        return true;
    }
    return false;
}

void generator(RenderWindow &window, int pole[60][40]) // ну тут наш красивый фон 
{
    int size = 15;
    RectangleShape cell(Vector2f(size, size));
    
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            cell.setPosition(i * size, j * size);

            if (i == 1 || j == 38)
            {
                cell.setFillColor(Color(0, 0, 0));
            }
            else
            {
                switch (pole[i][j])
                {
                case 0:
                    cell.setFillColor(Color(255, 248, 220));
                    break;
                case 1:
                    cell.setFillColor(Color(255, 235, 205));
                    break;
                case 2:
                    cell.setFillColor(Color(255, 228, 196));
                    break;
                case 3:
                    cell.setFillColor(Color(255, 222, 173));
                    break;
                case 4:
                    cell.setFillColor(Color(245, 222, 179));
                    break;
                case 5:
                    cell.setFillColor(Color(255, 228, 181));
                    break;
                default:
                    cell.setFillColor(Color(255, 250, 205));
                    break;
                }
            }

            window.draw(cell);

            cell.setOutlineThickness(1);
            cell.setOutlineColor(Color(0, 0, 0));

            window.draw(cell);
        }
    }
}

enum TYPE {INPUT, SIMULATOR};

int main()
{
    RenderWindow window(VideoMode(900, 600), "Simulator");

    Font font;
    if (!font.loadFromFile("tested.ttf"))
    {
        return -1;
    }

    vector<string> inputs(6);
    vector<Text> texts(6);
    vector<RectangleShape> boxes(6);
    vector<Text> description(6);
    vector<Text> type(6);

    description[0].setString("Enter mass of object: ");
    description[1].setString("Enter speed of object: ");
    description[2].setString("Enter radius of object: ");
    description[3].setString("Enter quickening of object: ");
    description[4].setString("Enter angle of object: ");
    description[5].setString("Enter heigth of object: ");

    type[0].setString("gr.");
    type[1].setString("m/s");
    type[2].setString("m.");
    type[3].setString("m/s^2");
    type[4].setString("-");
    type[5].setString("m.");

    Text logo;
    logo.setFont(font);
    logo.setCharacterSize(35);
    logo.setFillColor(Color::Blue);
    logo.setPosition(280, 50);
    logo.setOutlineColor(Color::Green);
    logo.setOutlineThickness(2);
    logo.setString("This is my little simulator of falling!");

    vector<Text> profile(6);

    for (int i = 0; i < 6; i++)
    {
        profile[i].setFont(font);
        profile[i].setCharacterSize(30);
        profile[i].setFillColor(Color::Blue);
        profile[i].setOutlineColor(Color::Green);
        profile[i].setOutlineThickness(2);
    }

    profile[0].setString("Hello! This is Andezion!");
    profile[0].setPosition(70, 150);

    profile[1].setString("There you can try my simulator,\n"
                         "on the rigth side you should enter\n"
                         "your values. If you don't want to\n"
                         "enter value - just enter 0!");
    profile[1].setPosition(45, 200);

    profile[2].setString("- The dimension is written near the entry");
    profile[2].setPosition(35, 340);

    profile[3].setString("- Description of what to enter near the input");
    profile[3].setPosition(35, 380);

    profile[4].setString("- You can only enter numbers");
    profile[4].setPosition(35, 420);

    profile[5].setString("- If you don't enter everything in order, it breaks");
    profile[5].setPosition(35, 460);

    for (int i = 0; i < 6; i++)
    {
        texts[i].setFont(font);
        texts[i].setCharacterSize(25);
        texts[i].setFillColor(Color::Black);
        texts[i].setPosition(12 + 700, 11 + i * 70 + 150);

        boxes[i].setSize(Vector2f(100, 40));
        boxes[i].setPosition(10 + 700, 10 + i * 70 + 150);
        boxes[i].setFillColor(Color(200, 200, 200));
        boxes[i].setOutlineColor(Color::Blue);
        boxes[i].setOutlineThickness(2);

        description[i].setFont(font);
        description[i].setCharacterSize(25);
        description[i].setFillColor(Color::Green);
        description[i].setPosition(520, 10 + i * 70 + 150);
        description[i].setOutlineColor(Color::Blue);
        description[i].setOutlineThickness(2);

        type[i].setFont(font);
        type[i].setCharacterSize(20);
        type[i].setFillColor(Color::Green);
        type[i].setPosition(820, 10 + i * 70 + 165);
        type[i].setOutlineColor(Color::Blue);
        type[i].setOutlineThickness(2);
    }

    int pole[60][40];
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            pole[i][j] = rand() % 6 + 1;
        }
    }

    int index = 0;
    int pointer = 0;
    object* ball = nullptr;
    Clock clock;

    float lastTime = clock.getElapsedTime().asSeconds();

    TYPE what = INPUT;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }

            if (what == INPUT)
            {
                if (event.type == Event::TextEntered)
                {
                    if (event.text.unicode == 8) // Backspace
                    {
                        if (!inputs[index].empty())
                        {
                            inputs[index].pop_back();
                        }
                    }

                    if (event.text.unicode == 13) // Enter
                    {
                        if (index < 5)
                        {
                            index++;
                        }
                        else
                        {
                            pointer = 1;

                            float mass = stof(inputs[0]);
                            float speed = stof(inputs[1]);
                            float radius = stof(inputs[2]);
                            float uskor = stof(inputs[3]);
                            float angle = stof(inputs[4]);
                            float heigth = stof(inputs[5]);

                            ball = new object(mass, speed, radius, uskor, angle, heigth);
                            what = SIMULATOR;
                        }
                    }

                    if (event.text.unicode >= 32 && event.text.unicode < 128) // Проверка печатных символов
                    {
                        char enteredChar = static_cast<char>(event.text.unicode);
                        if (isValidChar(enteredChar, inputs[index]))
                        {
                            inputs[index] += enteredChar;
                        }
                    }

                    texts[index].setString(inputs[index]);
                }
            }
            else
            {
                float currentTime = clock.getElapsedTime().asSeconds();
                float deltaTime = currentTime - lastTime;
                lastTime = currentTime;
                
                ball->handler1(deltaTime);
            }
           
        }

        window.clear();

        if (what == INPUT)
        {
            window.draw(logo);

            for (int i = 0; i < 6; i++)
            {
                window.draw(boxes[i]);
                window.draw(texts[i]);
                window.draw(description[i]);
                window.draw(type[i]);
            }

            for (int i = 0; i < 6; i++)
            {
                window.draw(profile[i]);
            }
        }
        else
        {
            generator(window, pole);
            ball->draw(window);
        }

        window.display();
    }  

    if (ball)
    {
        delete ball;
    }

    return 0;
}
