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

   
   // draw a point
   G_rgb (1.0, 0.0, 0.0) ; // red
   G_point (200, 580) ; // hard to see

   
   // draw a line
   int i = 0;
   int n = 0; //Number of row and columns
   double ox = 0;
   double oy = 0;





   G_rgb (0.0, 1.0, 0.0) ; // green
   while( n <= 4){
    G_rgb(1.0, 0.0, 0.0);
    ox = 200 * (n);
    if(n == 4){
    G_line(ox-1,0, ox-1, sheight-1); //Setting up the right most vertical line
    G_line(0,ox-1, sheight-1, ox-1);
    }
    G_line(ox,0, ox, sheight-1); //Setting up the vertical lines
    G_line(0,ox, sheight-1, ox); //Horzontial Lines
    n += 1;
   }
   
   //Lets draw a horizontal line

/*
   G_line(0,0, 0,800);
   G_line(200,0, 200,800-1);
   G_line(400,0, 400,800-1);
   G_line(600,0, 600,800-1);
   G_line(800-1,0, 800-1,800-1);

   G_line(0,200, 800-1,200);
   G_line(0,400, 800-1,400);

   G_line(0,600, 800-1,600);
   G_line(0,800-1, 800-1,800-1);


*/
   


   
   

   
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



/* David Ely Solution 

    Grid Problem: Make your own grid appear on the screen ( n x n , where n = 4 )

    


*/

