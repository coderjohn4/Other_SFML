//-lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MovingBox{
    public:
        MovingBox(sf::Time &ptimeCreated){
            timeCreated = ptimeCreated;
            this->entity = new sf::RectangleShape();
            entity->setPosition(75,75);
            entity->setSize(sf::Vector2f(30,30));
        };

        sf::Time timeCreated;
        sf::RectangleShape* entity;
        float velx = 1.f;
        float vely = 1.f;

        void stepBox(){
            sf::Vector2f entpos(entity->getPosition());
            entpos.x += velx / 10;
            entpos.y += vely / 10;
            if(entpos.x > 375) velx = velx * -1;
            if(entpos.x < 15 ) velx = velx * -1;    
            if(entpos.y > 200) vely = vely * -1;    
            if(entpos.y <  50) vely = vely * -1;
            entity->setPosition(entpos);
        };

        bool canDelete(sf::Time &timeNow){
            float milcreated = timeCreated.asMilliseconds();
            float milnow = timeNow.asMilliseconds();
            float mildiff = milnow - milcreated; 
            if(mildiff > 10000) return true;
            else return false;
        }
};

int main(){
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(400, 400), "0812");
    
    vector<MovingBox*> boxes;

    while(window.isOpen())  
    {
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
                sf::Time timeNow = clock.getElapsedTime(); 
                MovingBox* box = new MovingBox(timeNow);
                boxes.push_back(box);
            }
        }
    
        window.clear();
        sf::Time timeNow = clock.getElapsedTime(); 
        for(int i = 0; i < boxes.size(); i++){
            if(boxes[i] != nullptr){
                window.draw(*boxes[i]->entity);
                boxes[i]->stepBox();
                if(boxes[i]->canDelete(timeNow)){
                    delete(boxes[i]);
                    boxes[i] = nullptr;
                }
            }     
        };
        window.display();
    }
    return 0;
};
