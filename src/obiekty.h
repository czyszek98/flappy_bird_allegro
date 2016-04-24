#ifndef OBIEKTY_H_INCLUDED
#define OBIEKTY_H_INCLUDED

#include <allegro.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <math.h>



struct wait
{
    clock_t time;
    int sleep;

    void set_time(int sleep_);
    void restart();
    bool ready();
};
struct position
{
    int x;
    int y;
    int height;
    int width;
    void set_value(int x_,int y_,int height_,int width_);
};

class object
{
protected:

    int x;
    int y;
    int height;
    int width;

    BITMAP * shape = NULL;
    BITMAP * dest = NULL;

public:
    void load(BITMAP * src_,BITMAP * dest_,int src_x,int src_y,int height_,int width_,int x_,int y_);
    void draw();
    position xyz();
};
////////////////////////////////////////////////////////////////////////////////////////////////

class bird
        :public object
{

    int jump_suma;
    float a,b,c,t,t2;    // Funkcja kwadratowa
    wait speed_y;
    wait jump_interval;
    wait time_fly;
    bool jump;
    bool onclick;


public:
    void set_var(int jump_,float a_,float b_,float c_,int x_,int y_);
    void physic(bool alive);

};
////////////////////////////////////////////////////////////////////////////////////////////////
class background
    :public object
{

    wait speed;
    public:
    void set_var(int speed_,int x_,int y_);
    void draw();
};
////////////////////////////////////////////////////////////////////////////////////////////////

class fbpipe
{
    int x;
    int y_top;
    int y_bottom;
    int punkty;
    int interspace;

    int window;
    int width;
    int height;


    wait speed;

    BITMAP * shape;
    BITMAP * dest;

public:
    void load(BITMAP * src_,BITMAP * dest_,int src_x,int src_y,int width_,int height_,int interspace);
    void set_var(int speed_,int x_,int y_,int window_);
    void draw();
    position xyz_top();
    position xyz_bottom();



};
//_______________________________________COLLISION_______________________________________________

bool collision(position a,position b);
#endif // OBIEKTY_H_INCLUDED
