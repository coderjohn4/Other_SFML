//-lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
// #include <random>
using namespace std;


class MovingBox
{
    public:
        MovingBox(int posX, int posY){
            this->rect = new sf::RectangleShape();
            rect->setSize(sf::Vector2f(15,15));
            int red   = (rand() % 255);
            int green = (rand() % 255);
            int blue  = (rand() % 255);
            int alpha = (rand() % 255);
            rect->setFillColor(sf::Color(red,green,blue,alpha));
            rect->setPosition(posX, posY);
            velocityX = (rand() % 1000000) - 500000;
            velocityY = (rand() % 1000000) - 500000;
            velocityX = velocityX / 500000;
            velocityY = velocityY / 500000;
        };
    
        float velocityX;
        float velocityY;
        sf::RectangleShape* rect;
        void stepBox(){
            sf::Vector2f rectpos(rect->getPosition());
            rectpos.x += velocityX/5;
            rectpos.y += velocityY/5;
            if(rectpos.x > 350) velocityX = velocityX * -1;
            if(rectpos.x < 50 ) velocityX = velocityX * -1;    
            if(rectpos.y > 350) velocityY = velocityY * -1;    
            if(rectpos.y <  50) velocityY = velocityY * -1;

            rect->setPosition(rectpos);
        };
};

int main(){
    int boxcounter = 0;
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(400, 400), "0811");
    vector<MovingBox*> boxes;

    while(window.isOpen())  
    {
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {   
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                MovingBox* movbox = new MovingBox(mousePos.x, mousePos.y);
                
                
                if(boxcounter>20) boxcounter = 0;

                if(boxes.size() > 20){
                    MovingBox* mov = boxes[boxcounter];
                    delete mov;
                    boxes[boxcounter] = movbox;
                }
                else 
                    boxes.push_back(movbox);
                    
                boxcounter++;
            }
        }

        window.clear();
        for(int i = 0; i < boxes.size(); i++){
            boxes[i]->stepBox();
            window.draw(*boxes[i]->rect);
        }
        window.display();
    }
    return 0;
};