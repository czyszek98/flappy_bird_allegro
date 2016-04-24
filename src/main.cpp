#include "obiekty.h"

volatile int speed;

void increment_speed()
{
	speed++;
}
END_OF_FUNCTION( increment_speed );
LOCK_VARIABLE( speed );
LOCK_FUNCTION( increment_speed );

inline void init()
{
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 288, 512, 0, 0);

	install_timer();
	install_int_ex( increment_speed, BPS_TO_TIMER( 300 ) );
	install_keyboard();
	install_mouse();


}

inline void deinit()
{
	clear_keybuf();
	allegro_exit();
}

int main()
{
	init();
	restart:

	BITMAP * flapy = load_pcx("../assets/flapy.pcx",default_palette);
	BITMAP * bufor = create_bitmap(288,512);
	BITMAP * cp_bufor = create_bitmap(288,512);



    bird ptok;
    object tlo;
    tlo.load(flapy,bufor,0,0,288,512,0,0);
    ptok.load(flapy,bufor,62,982,34,24,0,0);



    background tlo2;
    tlo2.load(flapy,bufor,584,0,336,111,0,0);
    tlo2.set_var(8,0,401);

    fbpipe rura;
    rura.load(flapy,bufor,112,646,52,320,56);


    object koniec;
    koniec.load(flapy,bufor,790,118,192,42,48,214);




    ptok.set_var(250,-4.78,16.2,-11.1,127,200);
    rura.set_var(8,288,100,100);

    bool pause=1;
    wait press;
    press.set_time(150);
    press.restart();
	while (!key[KEY_ESC]  && collision(ptok.xyz(),rura.xyz_top()))
	{

		if (speed > 0) {
		    if(key[KEY_P] && press.ready())
		    {
		        pause=1;
		        press.restart();
		    }
			ptok.physic(1);
		    tlo.draw();
		    ptok.draw();
		    rura.draw();

		    tlo2.draw();
			speed--;




	    if(key[KEY_R]) goto restart;


	    masked_blit(bufor,screen,0,0,0,0,288,512);
		while(pause)
	    {
			if (speed > 0) {
				if(key[KEY_R]) goto restart;
				if(key[KEY_ESC]) goto exit;
		        if(key[KEY_P] && press.ready() || key[KEY_SPACE])
		        {
		          pause=0;
		          press.restart();
		        }

		        masked_blit(flapy,screen,242,612,50,50,26,28);
				speed--;
			}
	    }
}
	}

    tlo.draw();
    rura.draw();
    tlo2.draw();
    blit(bufor,cp_bufor,0,0,0,0,288,512);

	while (!key[KEY_ESC])
    {

		if (speed > 0) {
			masked_blit(cp_bufor,bufor,0,0,0,0,288,512);
	        ptok.physic(0);
	        ptok.draw();


	        koniec.draw();

	        masked_blit(bufor,screen,0,0,0,0,288,512);
	        if(key[KEY_R]) goto restart;
			speed--;
		}


    }
	exit:
	deinit();
	return 0;
}
END_OF_MAIN()










