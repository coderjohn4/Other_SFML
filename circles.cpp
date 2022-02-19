//-lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

class MovingBox{
    public:
        MovingBox(float pcenterX, float pcenterY, float pdegrees, float pradius){
            this->entity = new sf::RectangleShape();
            entity->setPosition(pcenterX, pcenterY);
            entity->setSize(sf::Vector2f(10,10));
            entity->setOrigin(15,15);
            this->degrees = pdegrees;
            this->centerX = pcenterX;
            this->centerY = pcenterY;
            this->radius = pradius;
        };

        sf::RectangleShape* entity;
        
        float centerX;
        float centerY;
        float degrees;
        float radius;
        
        void stepBox(){
            this->degrees+=0.1;
            float radians = degrees*M_PI/180;
            sf::Vector2f entpos(entity->getPosition());
            entpos.x = centerX + cos(radians) * radius;
            entpos.y = centerY + sin(radians) * radius;            
            entity->setPosition(entpos);
            entity->rotate(0.5);
        };
};


int main(){

    sf::RenderWindow window(sf::VideoMode(400, 400), "0812");
    MovingBox* box = new MovingBox(200,200,0,100);

    vector<MovingBox*> boxes;
    vector<MovingBox*> boxes_two;
    
    bool red = true;

    for(int i = 0; i < 100; i++){
        MovingBox* box = new MovingBox(200,200,i*1.5,100+i*1.5);    

        if(red == true){
            box->entity->setFillColor(sf::Color::Red);
            red = false;
        }
        else{
            box->entity->setFillColor(sf::Color::White);
            red = true;
        }
        boxes_two.push_back(box);
    }

    for(int i = 0; i < 100; i++){
        if(red == true){
            box->entity->setFillColor(sf::Color::Red);
            red = false;
        }
        else{
            box->entity->setFillColor(sf::Color::White);
            red = true;
        }
        boxes.push_back(box);
    }

    while(window.isOpen())  
    {
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();
            // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            // {   
           
            // }
        }

        window.clear();

        window.draw(*box->entity);
        box->stepBox();


        for(int i = 0; i < boxes.size(); i++){
            window.draw(*boxes[i]->entity);
            boxes[i]->stepBox();
        }

        window.display();
    }
    return 0;
};
