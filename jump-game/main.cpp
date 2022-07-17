#include <SFML/Graphics.hpp>
#include <time.h>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

using namespace sf;

struct point
{int x,y;};

int main()
{
    // Get a new unpredicatable seed for generating the random numbers.
    // time(0) gives the time in seconds since the Unix epox, which is an unpredictable seed
    // (you're guaranteed your seed will be the same only once, unless you start your program multiple times within the same second).
    srand(time(0));
    
    
    // Window that can serve as a target for 2D drawing.
    RenderWindow app(VideoMode(400,533), "Jump Game");
    app.setFramerateLimit(60);
    
    
    // sf::Texture stores pixels that can be drawn, with a sprite for example.
    Texture t1, t2, t3;
    t1.loadFromFile(resourcePath()+"background.png");
    t2.loadFromFile(resourcePath()+"platform.png");
    t3.loadFromFile(resourcePath()+"doodle.png");
    
    Sprite sBackground(t1), sPlat(t2), sPers(t3);
    
    // Generate 20 random platforms.
    point plat[20];
    
    for (int i=0; i<10; i++)
    {
        plat[i].x = rand()%400;
        plat[i].y = rand()%533;
    }
    
    // Initialize to make character jump when reaching bottom of screen.
    int x=100,y=100,h=200;
    float dx=0,dy=0;
    
    
    while (app.isOpen())
    {
        // Event instances are filled by the pollEvent (or waitEvent) function of the sf::Window class. Only these two functions can produce valid events.
        Event e;
        
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
        
        // Move left/right when keyboard is pressed
        if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;
        
        // Change the coordinates for the position of the character.
        dy+=0.2;
        y+=dy;
        if (y>500) dy=-10;
        
        // Move the background up as the character bounces off a platform.
        if (y<h)
            for (int i=0; i<10;i++)
            {
                y=h;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y>533)
                    {
                        plat[i].y=0;
                        plat[i].x=rand()%400;
                    }
            }
        
        
        // Make character bounce off the platforms.
        for (int i=0;i<10;i++)
         if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
          && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))  dy=-10;
        
        // Set the position of the character.
        sPers.setPosition(x,y);
        
        app.draw(sBackground);
        app.draw(sPers);
        
        // Set initial position of the platforms.
        for (int i=0;i<10;i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            app.draw(sPlat);
        }
        
        app.display();
    }
    
    return 0;
    
}

