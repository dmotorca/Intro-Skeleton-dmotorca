#include  "FPToolkit.c"

/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c 
    Copyright (C) 2018  Ely

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/





/*

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and 
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :
       
sudo  apt-get  install  libx11-dev     

sudo  apt-get  install  xorg-dev

*/




/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,  
do the following :

cc  FPToolkitDemoB.c   -lm  -lX11

note : the 'X' in -X11 is capitalized
*/


#include  "FPToolkit.c"




int main()
{
   int    swidth, sheight ;
   double lowleftx, lowlefty, width, height ;
   double x[10], y[10] ;
   double numxy ;
   double a[20], b[20] ;
   double numab ;

   
   // must do this before you do 'almost' any other graphical tasks 
   swidth = 800 ;  sheight = 800;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color
   G_rgb (0.0, 0.0, 0.0) ; // black
   G_clear () ;
   
   //Draw our own G_line

   //y = mx + b 



double x1 = 0.0;
double y1 = 0.0;
double x2 = 0.0;
double y2 = 0.0;


printf("x1: ");
scanf("%lf", &x1);
printf("y1: ");
scanf("%lf", &y1);
printf("x2: ");
scanf("%lf", &x2);
printf("y2: ");
scanf("%lf", &y2);

double dx = x2 - x1;
double dy = y2 - y1; 
double diff = (2 * dy) - dx;
double y_mine = y1;
double x_mine = x1;

for(int i = 0; i < dx; i++){

    G_rgb(0.0, 0.9, 0.3);
    G_point(x_mine,y_mine);
    if(diff > 0 ){
        y_mine = y_mine + 1;
        diff = diff - (2*dx);
    }
    diff = diff + (2 * dy);

}
   //===============================================
   
   double p[2], q[2] ;

   G_rgb(1,0,0) ;
   
   G_wait_click(p) ;
   G_fill_circle(p[0],p[1],2) ;

   G_wait_click(q) ;
   G_fill_circle(q[0],q[1],2) ;   

   G_rgb(0,1,0.5) ;
   G_line(p[0],p[1], q[0],q[1]) ;
   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results

   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("demo.bmp") ;

}



/* Ely Solution

Parametric Approach ? 
 A = Initial , B = Terminal 
 A = (-2,3)  , B = (3,6)

 x = a1 + wt 
 y = b1 + zt
 when t = 0 , x = -2 , y = 3
 when t = 1 , x = 3  , y = 6

 3 = -2 + w(1)
 w = 5
 x = -2 + 5t

 6 = 3 + z(1)
 z = 3 
 y = 3 + 3t

*/


