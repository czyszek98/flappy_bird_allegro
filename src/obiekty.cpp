

#include "obiekty.h"
#include "config.h"


void position::set_value(int x_,int y_,int height_,int width_)
{
    x=x_;
    y=y_;
    height=height_;
    width=width_;
}


void wait::set_time(int ms)
{
    sleep = ms * CLOCKS_PER_SEC / 1000;
}

void wait::restart()
{
    time=clock();

}
bool wait::ready()
{
    if(clock() > time + sleep) return 1;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
void object::load(BITMAP * src_,BITMAP * dest_,int src_x,int src_y,int height_,int width_,int x_,int y_)
{
    width=width_;
    height=height_;
    dest=dest_;
    shape = create_bitmap(height,width);
    x=x_;
    y=y_;
    blit(src_,shape,src_x,src_y,0,0,height,width);
}


void object::draw()
{
    masked_blit(shape,dest,0,0,x,y,height,width);
}


position object::xyz()
{
    position xyz;
    xyz.set_value(x,y,height,width);
    return xyz;

}

//_______________________________BIRD___________________________________________________

void bird::set_var(int jump_,float a_,float b_,float c_,int x_,int y_)
{
    speed_y.set_time(35);
    speed_y.restart();
    jump_interval.set_time(100);
    jump_interval.restart();
    time_fly.set_time(jump_);
    jump=1;
    a=a_;
    b=b_;
    c=c_;
    x=x_;
    y=y_;
    t=0;
    onclick=0;
}

void bird::physic( bool alive)
{
    if(!alive) jump_interval.sleep=time_fly.sleep+1;
    if(key[KEY_SPACE] && jump_interval.ready() && !onclick)
    {
        onclick=1;
        jump_interval.restart();
        time_fly.restart();
        jump_suma=0;
        jump=1;
        t=0;
        t2=0.4;
    }
    if(!key[KEY_SPACE])onclick=0;
    if(jump && jump_interval.ready())
    {
        jump=0;
        t=0;
        t2=0.4;
    }
    if(speed_y.ready())
    {



            t+=0.1;
            if(t>2.5)t=2.5;

        if(!time_fly.ready() && alive)
        {
            if(time_fly.time > clock() && t>=1)t=-1;

            if(t>0)y+=a*pow(t,2)+b*t + c;
            if(t<0)y-=a*pow(t,2)+b*(-t) + c;
        }
        else
        {
             t2+=0.1;
             if(t2>2)t=1;
             y-=-4.9*pow(t2,2)+0*t + 2.06;
        }


        speed_y.restart();

    }

    if(y>401-shape->h)y=401-shape->h;
    if(y<0)y=0;
}
//_______________________________BACKGROUND___________________________________________________

void background::set_var(int speed_,int x_,int y_)
{
    speed.set_time(speed_);
    speed.restart();

    x=x_;
    y=y_;
}


void background::draw()
{
    masked_blit(shape,dest,0,0,x,y,height,width);
    if(speed.ready())
    {
        x--;
        if(x==-(shape->w-288))x=0;
        speed.restart();
    }
}
//__________________________________PIPE_________________________________________________________
void fbpipe::load(BITMAP * src_,BITMAP * dest_,int src_x,int src_y,int width_,int height_,int interspace_)
{

    width=width_;
    height=height_;
    dest=dest_;
    interspace=interspace_;
    shape = create_bitmap(width*2+interspace,height_);

    blit(src_,shape,src_x,src_y,0,0,shape->w,shape->h);

}
void fbpipe::set_var(int speed_,int x_,int y_,int window_)
{
    srand( time( NULL ) );
    speed.set_time(speed_);
    speed.restart();
    x=x_;
    y_top=y_;
    window=window_;
    y_bottom=y_top+window_;
    punkty=0;
}
void fbpipe::draw()
{
    masked_blit(shape,dest,0,0,x,-320+y_top,width,height);
    masked_blit(shape,dest,interspace,0,x,y_bottom,width,height);
    textprintf_ex(dest,font, 0, 0, 1000, -1,"score: %d",punkty);
    if(speed.ready())
    {
        x--;
        if(x==118)punkty++;
        if(x==-(width))
        {
            x=288;
            y_top=std::rand() % 250  + 7;
            y_bottom=y_top+window;
        }
        speed.restart();
    }
}
position fbpipe::xyz_top()
{
    position xyz;
    xyz.set_value(x,y_top,height,width);
    return xyz;

}
position fbpipe::xyz_bottom()
{
    position xyz;
    xyz.set_value(x,y_bottom,height,width);
    return xyz;

}
//_________________________________________COLLISION_________________________________________
bool collision(position a,position b)
{

    if( ((a.x + a.width > b.x && a.x + a.width < b.x + b.width) && (a.y  < b.y )) || ((a.x + a.width > b.x && a.x + a.width < b.x + b.width) && (a.y + 24  > b.y +100 )))
    return 0;
    else return 1;

}
