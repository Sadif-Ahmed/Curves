# include "iGraphics.h"
#include<math.h>
#include<conio.h>
/*
	function iDraw() is called again and again by the system.
*/
int  bx=0,b1y=0,b2y=0,b3y=0,b4y=0;//ball co-ordinates
float an=0;//trace angle
int r=255,g=255,b=255;//color variables
int r1=121,g1=121,b1=121;
int r2=255,g2=0,b2=0;
int r3=0,g3=255,b3=0;
int r4=255,g4=51,b4=253;
int s=0;//reverse tracing variable
int c=0,c1=0,c2=0,c3=0,c4=0;//curve and balls toggle
float a1=1.0,a2=1.0,a3=1.0,f=1.0;//amplitude and frequency variables
int t=2,gd=1;//speed and cover page variable
int ps[17]= {-720,-630,-540,-450,-360,-270,-180,-90,0,90,180,270,360,450,540,630,720},i=0,ts=8; //phase shifter and trace
int curvedrawer(int angle, int x,float a)
{
    int y;
    y=1000+a*x*sin(f*angle*3.141/180);
        return y;
}
void trace(void)
{
    //REVERSE TRACING CHECKER
    if(bx>=2000)
    {
        s=1;
    }
    else if(bx<=0)
    {
        s=0;
    }
    //PHASE SHIFTING
    if((ts>=0)&&(i==1))
    {
        an+=90;
        i=0;
    }
    if((ts>=0)&&(i==-1))
    {
        an-=90;
        i=0;
    }
    //TRACING
    if(s==0)
    {
        b1y=curvedrawer(an,200,a1);
        b2y=curvedrawer(an+90,200,a2);
        b3y=curvedrawer(an,400,a3);
        b4y=b1y+b2y+b3y-2000;
        bx+=t;
        an+=t;
    }
    else
    {
        b1y=curvedrawer(an,200,a1);
        b2y=curvedrawer(an+90,200,a2);
        b3y=curvedrawer(an,400,a3);
        b4y=b1y+b2y+b3y-2000;
        bx-=t;
        an-=t;
    }
}

void iDraw()
{
    //MAIN PAGE TOGGLER
    if(gd==0)
    {

        int dx=0,dy1,dy2,dy3,dy4;//curve points co-ordinates
        float angle=0;//curve point angles
        iClear();
        iLine(0,1000,2000,1000);
        iSetColor(r1,g1,b1);
        iFilledCircle(bx,b1y,10);
        iSetColor(r2,g2,b2);
        iFilledCircle(bx,b2y,10);
        iSetColor(r3,b3,g3);
        iFilledCircle(bx,b3y,10);
        iSetColor(r4,g4,b4);
        iFilledCircle(bx,b4y,10);
        //PHASE SHIFT
        angle=ps[ts];
        //CURVE DRAWING
        for(int i=0; i < 2000; i++)
        {
            iSetColor(r,g,b);
            dy1=curvedrawer(angle,200,a1);
            iPoint(dx,dy1,1);
            dy2=curvedrawer(angle+90,200,a2);
            iPoint(dx,dy2,1);
            dy3 =curvedrawer(angle,400,a3);
            iPoint(dx,dy3,1);
            dy4=dy1+dy2+dy3-2000;
            iPoint(dx,dy4,1);
            angle++;
            dx++;

        }
    }
    //MAIN PAGE
    else
    {
        iClear();
        iShowBMP(200,50,"help.bmp");
        iSetColor(0,0,0);
        iText(400,1550,"Toggle  Help  /  Main  Page  :  F1");
        iText(400,1450,"Toggle  Curve  Show  /  Hide :  s/S");
        iText(400,1350,"Toggle  Tracer  Show /  Hide :  <Curve no.>");
        iText(400,1250,"Pause  Animation  :  p/p");
        iText(400,1150,"Resume Animation  :  r/R");
        iText(400,1050,"Increase  Amplitude  :  a");
        iText(400,950,"Decrease   Amplitude  :  A");
        iText(400,850,"Increase  Frequency  :  f");
        iText(400,750,"Decrease  Frequency  :  F");
        iText(400,650,"Increase  Speed  :  +");
        iText(400,550,"Decrease  Speed  :  -");
        iText(400,450,"Phase Shift by 90 Degree: Right Movement Key" );
        iText(400,350,"Reverse Shift by 90 Degrees: Left Movement Key");
        iText(400,250,"Ball moving Direction reverse:Any Mouse Click");
        iText(400,150,"End              :   END");
    }


}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if(s==0)
        {
            s=1;
        }
        else
        {
            s=0;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if(s==0)
        {
            s=1;
        }
        else
        {
            s=0;
        }
    }

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    //PAUSE AND RESUME
    if((key== 'p')||(key=='P'))
    {
        iPauseTimer(0);
    }
    if((key=='r')||(key=='R'))

    {
        iResumeTimer(0);
    }
    //AMPLITUDE
    if(key=='A')
    {
        if(a1>0.0)
        {
            a1-=0.05;
        }
        if(a2>0.0)
        {
            a2-=0.05;
        }
        if(a3>0.0)
        {
            a3-=0.05;
        }
    }
    if(key=='a')
    {
       if(curvedrawer(90,200,a1)<=2000)
       {
           a1+=0.05;
       }
       if(curvedrawer(90,200,a2)<=2000)
       {
           a2+=0.05;
       }
       if(curvedrawer(90,400,a3)<=2000)
       {
           a3+=0.05;
       }
    }
    //FREQUENCY
    if(key=='f')
    {   if(f<4.5)
    {
        f+=0.75;
    }
    }
    if(key=='F')
    {
        if(f>0)
        {
            f-=0.25;
        }
    }
    //SPEED CHANGE
    if(key=='+')
    {
        t++;
    }
    if(key=='-')
    {
        if(t>1)
        {
            t--;
        }
    }
    //CURVE SHOW/HIDE
    if((key=='s')||(key=='S'))
    {
        if(c==0)
        {
            r=0;
            g=0;
            b=0;
            c=1;
        }
        else
        {
            r=255;
            g=255;
            b=255;
            c=0;
        }
    }
    //BALLS SHOW/HIDE
    if(key=='1')
    {
        if(c1==0)
        {
            r1=0;
            g1=0;
            b1=0;
            c1=1;
        }
        else
        {
            r1=121;
            g1=121;
            b1=121;
            c1=0;
        }
    }
    if(key=='2')
    {
        if(c2==0)
        {
            r2=0;
            g2=0;
            b2=0;
            c2=1;
        }
        else
        {
            r2=255;
            g2=0;
            b2=0;
            c2=0;
        }
    }
    if(key=='3')
    {
        if(c3==0)
        {
            r3=0;
            g3=0;
            b3=0;
            c3=1;
        }
        else
        {
            r3=0;
            g3=255;
            b3=0;
            c3=0;
        }
    }
    if(key=='4')
    {
        if(c4==0)
        {
            r4=0;
            g4=0;
            b4=0;
            c4=1;
        }
        else
        {
            r4=255;
            g4=51;
            b4=253;
            c4=0;
        }
    }
    //place your codes for other keys here

}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //MAIN PAGE TOGGLER
    if(key== GLUT_KEY_F1)
    {
        if(gd==1)
        {
            gd=0;
        }
        else
        {
            gd=1;
        }
    }
    //PHASE SHIFTING
    if(key== GLUT_KEY_RIGHT)
    {
        if(ts<16)
        {
            ts++;
            i=1;
        }
        else
        {
            i=0;
        }
    }
    if(key== GLUT_KEY_LEFT)
    {
        if(ts>0)
        {
            ts--;
            i=-1;
        }
        else
        {
            i=0;
        }
    }
    //place your codes for other keys here
}


int main()
{
    //place your own initialization codes here.
    //BALL TRACE SETTER
    iSetTimer(2,trace);
    iInitialize(2000, 2000, "MY CURVE ");

    return 0;
}
