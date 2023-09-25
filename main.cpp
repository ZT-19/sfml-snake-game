#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
 
int sWidth = 400;
int sHeight = 533;
 
int maxPlat = 20;
 
class point
{ 
  public:
    int x,y;
};
int main()
{
    srand(time(0));//random seed from time
 
    RenderWindow window(VideoMode(sWidth, sHeight), "Doodle Jump");
    window.setFramerateLimit(60);
 
    Texture t1,t2,t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");
 
    Sprite sBackground(t1), sPlat(t2), sPers(t3);
 
    point platforms[maxPlat];//initializing 20 platforms to fit in frame
    for (int i=0;i<maxPlat / 2;i++)//safest to only initialize half of max possible platforms
    {
       platforms[i].x=rand()%sWidth;
       platforms[i].y=rand()%sHeight;
      for(int j=0;j<i;j++){
       if(platforms[i].x == platforms[j].x || platforms[i].y == platforms[j].y){
          platforms[i].x=rand()%sWidth;
          platforms[i].y=rand()%sHeight;
        }

      }
    }

    int x=100,y=100,h=200; //player variables
    float dy=0; // 

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        //left and right movement
        if (Keyboard::isKeyPressed(Keyboard::Right) && x < 370) x+=3;
        if (Keyboard::isKeyPressed(Keyboard::Left) && x > 0) x-=3;

        dy+=0.2;
        y+=dy;
        if (y>500){//quit game if off map
            window.close();
            dy=-10;
        }

        if (y<h){
          for (int i=0;i<10;i++){
            y=h;
            platforms[i].y=platforms[i].y-dy;
            if (platforms[i].y>sHeight){ //generate new platforms if they move out of frame
              platforms[i].y=0; 
              platforms[i].x=rand()%sWidth;
            }
          }
        }

        //for each platform, check if player is colliding within range of values
        for (int i=0;i<10;i++){
          if ((x+50>platforms[i].x) && (x+20<platforms[i].x+68) && 
          (y+70>platforms[i].y) && (y+70<platforms[i].y+14) && (dy>0)){
              dy=-10;
          }
        }

        //------DRAWING CODE-------//
        window.clear();

        sPers.setPosition(x,y);
        window.draw(sBackground);
        window.draw(sPers);
        for (int i=0;i<10;i++)
        {
          sPlat.setPosition(platforms[i].x,platforms[i].y);
          window.draw(sPlat);
        }

        window.display();
        //------DRAWING CODE-------//
    }

    return 0;
}