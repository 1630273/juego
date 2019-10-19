#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glut.h>


#define AlturaVentana 500
#define AnchuraVentana 500
#define PI 3.14159265358979324

using namespace std;

//--Contadores de colisión
int arriba = 0;
int abajo = 0;
int derecha = 0;
int izquierda = 0;
bool puntoPrincipal = true;
bool paredArriba = false;
bool paredAbajo = false;
bool paredIzquierda = false;
bool paredDerecha = false;

static float R = 4.0; // Radius of circle.
static float X = 7.0; // X-coordinate of center of circle.
static float Y = 93.0; // Y-coordinate of center of circle.
static int numVertices = 80; // Number of vertices on circle.

void line(void){

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(4.0f);
      
   glBegin(GL_LINES);

      glVertex3f(1.0, 1.0, 0.0);
      glVertex3f(99.0, 1.0, 0.0);
   glEnd();

   
   glBegin(GL_LINES);
      glVertex3f(1.0,1.0, 0.0);
      glVertex3f(1.0, 99.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(1.0,99.0, 0.0);
      glVertex3f(99.0, 99.0, 0.0);
   glEnd();
   
   glBegin(GL_LINES);
      glVertex3f(99.0,99.0, 0.0);
      glVertex3f(99.0, 1.0, 0.0);
   glEnd();

//fin marcos   

//horizontal
  
//col1
   glBegin(GL_LINES);

      glVertex3f(61.0,87.0, 0.0);
      glVertex3f(13.0, 87.0, 0.0);
   glEnd();
   //col2
    glBegin(GL_LINES);

      glVertex3f(49.0,75.0, 0.0);
      glVertex3f(13.0, 75.0, 0.0);
   glEnd();

   //col3

     glBegin(GL_LINES);

      glVertex3f(13.0,63.0, 0.0);
      glVertex3f(25.0, 63.0, 0.0);
   glEnd();
      glBegin(GL_LINES);

      glVertex3f(49.0,63.0, 0.0);
      glVertex3f(73.0, 63.0, 0.0);
   glEnd();

  
   
   //col4
      glBegin(GL_LINES);

      glVertex3f(25.0,51.0, 0.0);
      glVertex3f(49.0, 51.0, 0.0);
   glEnd();

      glBegin(GL_LINES);
      glVertex3f(73.0,51.0, 0.0);
      glVertex3f(85.0, 51.0, 0.0);
   glEnd();

//col5
    glBegin(GL_LINES);

      glVertex3f(13.0,39.0, 0.0);
      glVertex3f(49.0, 39.0, 0.0);
   glEnd();

     glBegin(GL_LINES);

      glVertex3f(85.0,39.0, 0.0);
      glVertex3f(99.0, 39.0, 0.0);
   glEnd();

//col6
    glBegin(GL_LINES);

      glVertex3f(1.0,27.0, 0.0);
      glVertex3f(25.0, 27.0, 0.0);
   glEnd();


    glBegin(GL_LINES);

      glVertex3f(37.0,27.0, 0.0);
      glVertex3f(49.0, 27.0, 0.0);
   glEnd();
     glBegin(GL_LINES);

      glVertex3f(61.0,27.0, 0.0);
      glVertex3f(73.0, 27.0, 0.0);
   glEnd();
//col 7

  glBegin(GL_LINES);

      glVertex3f(13.0,15.0, 0.0);
      glVertex3f(25.0, 15.0, 0.0);
   glEnd();


     glBegin(GL_LINES);

      glVertex3f(37.0,15.0, 0.0);
      glVertex3f(75.0, 15.0, 0.0);
   glEnd();
//vertical
    glBegin(GL_LINES);

      glVertex3f(13.0,87.0, 0.0);
      glVertex3f(13.0, 75.0, 0.0);
   glEnd();


     glBegin(GL_LINES);

      glVertex3f(13.0,63.0, 0.0);
      glVertex3f(13.0, 39.0, 0.0);
   glEnd();

//col 2
    glBegin(GL_LINES);

      glVertex3f(25.0,63.0, 0.0);
      glVertex3f(25.0, 51.0, 0.0);
   glEnd();


    glBegin(GL_LINES);

      glVertex3f(25.0,39.0, 0.0);
      glVertex3f(25.0, 15.0, 0.0);
   glEnd();

   //col3
    glBegin(GL_LINES);

      glVertex3f(37.0,75.0, 0.0);
      glVertex3f(37.0, 63.0, 0.0);
   glEnd();

     glBegin(GL_LINES);

      glVertex3f(37.0,15.0, 0.0);
      glVertex3f(37.0, 1.0, 0.0);
   glEnd();

    //col4
    glBegin(GL_LINES);

      glVertex3f(49.0,75.0, 0.0);
      glVertex3f(49.0, 63.0, 0.0);
   glEnd();


      glBegin(GL_LINES);

      glVertex3f(49.0,39.0, 0.0);
      glVertex3f(49.0, 27.0, 0.0);
   glEnd();
  
//col 5

    glBegin(GL_LINES);

      glVertex3f(61.0,51.0, 0.0);
      glVertex3f(61.0, 27.0, 0.0);
   glEnd();


   glBegin(GL_LINES);

      glVertex3f(61.0,87.0, 0.0);
      glVertex3f(61.0, 75.0, 0.0);
   glEnd();

//col 6
   
      glBegin(GL_LINES);

      glVertex3f(73.0,87.0, 0.0);
      glVertex3f(73.0, 27.0, 0.0);
   glEnd();
//col7
      
      glBegin(GL_LINES);

      glVertex3f(85.0,87.0, 0.0);
      glVertex3f(85.0, 39.0, 0.0);
   glEnd();


 glBegin(GL_LINES);

      glVertex3f(85.0,27.0, 0.0);
      glVertex3f(85.0, 1.0, 0.0);
   glEnd();

}



void serpiente(){
      float t = 0; // Angle parameter.
   int i;

   glBegin(GL_POLYGON);
      glColor3f(0.0, 1.0, 0.0);
         for(i = 0; i < numVertices; ++i)
	   {
          
         glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
	  }
   glEnd();


}


// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
   if(key == GLUT_KEY_DOWN){	//ABAJO
   	  if (derecha==7 && abajo==4 && izquierda==-7 && arriba==-4){return ;}
        if (derecha==6 && abajo==3 && izquierda==-6 && arriba==-3){return ;}
        if (derecha==5 && abajo==2 && izquierda==-5 && arriba==-2){return ;}
        if (derecha==4 && abajo==2 && izquierda==-4 && arriba==-2){return ;}
        if (derecha==1 && abajo==1 && izquierda==-1 && arriba==-1){return ;}
        if (derecha==2 && abajo==1 && izquierda==-2 && arriba==-1){return ;}
        if (derecha==3 && abajo==1 && izquierda==-3 && arriba==-1){return ;}
        if (derecha==1 && abajo==0 && izquierda==-1 && arriba==0){return ;}
        if (derecha==2 && abajo==0 && izquierda==-2 && arriba==0){return ;}
        if (derecha==3 && abajo==0 && izquierda==-3 && arriba==0){return ;}
        if (derecha==4 && abajo==0 && izquierda==-4 && arriba==0){return ;}
        if (derecha==0 && abajo==5 && izquierda==0 && arriba==-5){return ;}
        if (derecha==1 && abajo==5 && izquierda==-1 && arriba==-5){return ;}
        if (derecha==1 && abajo==2 && izquierda==-1 && arriba==-2){return ;}
        if (derecha==2 && abajo==3 && izquierda==-2 && arriba==-3){return ;}
        if (derecha==3 && abajo==3 && izquierda==-3 && arriba==-3){return ;}
        if (derecha==5 && abajo==5 && izquierda==-5 && arriba==-5){return ;}
        if (derecha==3 && abajo==4 && izquierda==-3 && arriba==-4){return ;}
        if (derecha==2 && abajo==4 && izquierda==-2 && arriba==-4){return ;}
        if (derecha==1 && abajo==4 && izquierda==-1 && arriba==-4){return ;}
        if (derecha==4 && abajo==6 && izquierda==-4 && arriba==-6){return ;}
        if (derecha==3 && abajo==6 && izquierda==-3 && arriba==-6){return ;}
        if (derecha==5 && abajo==6 && izquierda==-5 && arriba==-6){return ;}
        if (derecha==3 && abajo==5 && izquierda==-3 && arriba==-5){return ;}
        if (derecha==2 && abajo==7 && izquierda==-2 && arriba==-7){return ;}
        if (derecha==1 && abajo==7 && izquierda==-1 && arriba==-7){return ;}
        if (derecha==0 && abajo==7 && izquierda==0 && arriba==-7){return ;}
        if (derecha==1 && abajo==6 && izquierda==-1 && arriba==-6){return ;}
        if (derecha==3 && abajo==7 && izquierda==-3 && arriba==-7){return ;}
        if (derecha==4 && abajo==7 && izquierda==-4 && arriba==-7){return ;}
        if (derecha==5 && abajo==7 && izquierda==-5 && arriba==-7){return ;}
        if (derecha==6 && abajo==7 && izquierda==-6 && arriba==-7){return ;}
        if (derecha==7 && abajo==7 && izquierda==-7 && arriba==-7){return ;}

      Y= Y-12.0;
      abajo++;
      arriba--;
   }

   if(key == GLUT_KEY_UP){		//ARRIBA
        if (derecha==4 && abajo==1 && izquierda==-4 && arriba==-1){return ;}
        if (derecha==3 && abajo==1 && izquierda==-3 && arriba==-1){return ;}
        if (derecha==2 && abajo==1 && izquierda==-2 && arriba==-1){return ;}
        if (derecha==1 && abajo==1 && izquierda==-1 && arriba==-1){return ;}
        if (derecha==0 && abajo==0 && izquierda==0 && arriba==0){return ;}
        if (derecha==1 && abajo==0 && izquierda==-1 && arriba==0){return ;}
        if (derecha==2 && abajo==0 && izquierda==-2 && arriba==0){return ;}
        if (derecha==3 && abajo==0 && izquierda==-3 && arriba==0){return ;}
        if (derecha==4 && abajo==0 && izquierda==-4 && arriba==0){return ;}
        if (derecha==5 && abajo==0 && izquierda==-5 && arriba==0){return ;}
        if (derecha==6 && abajo==0 && izquierda==-6 && arriba==0){return ;}
        if (derecha==7 && abajo==0 && izquierda==-7 && arriba==0){return ;}
        if (derecha==1 && abajo==5 && izquierda==-1 && arriba==-5){return ;}
        if (derecha==1 && abajo==2 && izquierda==-1 && arriba==-2){return ;}
        if (derecha==2 && abajo==2 && izquierda==-2 && arriba==-2){return ;}
        if (derecha==3 && abajo==2 && izquierda==-3 && arriba==-2){return ;}
        if (derecha==4 && abajo==3 && izquierda==-4 && arriba==-3){return ;}
        if (derecha==5 && abajo==3 && izquierda==-5 && arriba==-3){return ;}
        if (derecha==3 && abajo==4 && izquierda==-3 && arriba==-4){return ;}
        if (derecha==2 && abajo==4 && izquierda==-2 && arriba==-4){return ;}
        if (derecha==1 && abajo==3 && izquierda==-1 && arriba==-3){return ;}
        if (derecha==3 && abajo==6 && izquierda==-3 && arriba==-6){return ;}
        if (derecha==5 && abajo==6 && izquierda==-5 && arriba==-6){return ;}
        if (derecha==2 && abajo==5 && izquierda==-2 && arriba==-5){return ;}
        if (derecha==3 && abajo==5 && izquierda==-3 && arriba==-5){return ;}
        if (derecha==1 && abajo==7 && izquierda==-1 && arriba==-7){return ;}
        if (derecha==0 && abajo==6 && izquierda==0 && arriba==-6){return ;}
        if (derecha==1 && abajo==6 && izquierda==-1 && arriba==-6){return ;}
        if (derecha==6 && abajo==4 && izquierda==-6 && arriba==-4){return ;}
        if (derecha==5 && abajo==7 && izquierda==-5 && arriba==-7){return ;}
        if (derecha==4 && abajo==7 && izquierda==-4 && arriba==-7){return ;}
        if (derecha==3 && abajo==7 && izquierda==-3 && arriba==-7){return ;}
        if (derecha==7 && abajo==5 && izquierda==-7 && arriba==-5){return ;}

   	  arriba++;
   	  abajo--;
      Y=Y+12.0;
   }

   if(key == GLUT_KEY_RIGHT){	//DERECHA
   	  if (derecha==7 && abajo==4 && izquierda==-7 && arriba==-4){return ;}	
        if (derecha==7 && abajo==3 && izquierda==-7 && arriba==-3){return ;}
        if (derecha==7 && abajo==2 && izquierda==-7 && arriba==-2){return ;}
        if (derecha==7 && abajo==1 && izquierda==-7 && arriba==-1){return ;}
        if (derecha==7 && abajo==0 && izquierda==-7 && arriba==0){return ;}
        if (derecha==6 && abajo==3 && izquierda==-6 && arriba==-3){return ;}
        if (derecha==6 && abajo==2 && izquierda==-6 && arriba==-2){return ;}
        if (derecha==6 && abajo==1 && izquierda==-6 && arriba==-1){return ;}
        if (derecha==5 && abajo==1 && izquierda==-5 && arriba==-1){return ;}
        if (derecha==5 && abajo==2 && izquierda==-5 && arriba==-2){return ;}
        if (derecha==4 && abajo==1 && izquierda==-4 && arriba==-1){return ;}
        if (derecha==1 && abajo==5 && izquierda==-1 && arriba==-5){return ;}
        if (derecha==0 && abajo==3 && izquierda==0 && arriba==-3){return ;}
        if (derecha==0 && abajo==4 && izquierda==0 && arriba==-4){return ;}
        if (derecha==0 && abajo==1 && izquierda==0 && arriba==-1){return ;}
        if (derecha==2 && abajo==2 && izquierda==-2 && arriba==-2){return ;}
        if (derecha==3 && abajo==2 && izquierda==-3 && arriba==-2){return ;}
        if (derecha==5 && abajo==3 && izquierda==-5 && arriba==-3){return ;}
        if (derecha==5 && abajo==4 && izquierda==-5 && arriba==-4){return ;}
        if (derecha==5 && abajo==5 && izquierda==-5 && arriba==-5){return ;}
        if (derecha==4 && abajo==4 && izquierda==-4 && arriba==-4){return ;}
        if (derecha==1 && abajo==3 && izquierda==-1 && arriba==-3){return ;}
        if (derecha==4 && abajo==5 && izquierda==-4 && arriba==-5){return ;}
        if (derecha==3 && abajo==5 && izquierda==-3 && arriba==-5){return ;}
        if (derecha==2 && abajo==7 && izquierda==-2 && arriba==-7){return ;}
        if (derecha==1 && abajo==6 && izquierda==-1 && arriba==-6){return ;}
        if (derecha==6 && abajo==6 && izquierda==-6 && arriba==-6){return ;}
        if (derecha==6 && abajo==4 && izquierda==-6 && arriba==-4){return ;}
        if (derecha==6 && abajo==7 && izquierda==-6 && arriba==-7){return ;}
        if (derecha==7 && abajo==5 && izquierda==-7 && arriba==-5){return ;}
        if (derecha==7 && abajo==6 && izquierda==-7 && arriba==-6){return ;}
        if (derecha==7 && abajo==7 && izquierda==-7 && arriba==-7){return ;}


   	  derecha++;
   	  izquierda--;
      X=X+12.0;
   	  
      
   }

   if(key == GLUT_KEY_LEFT){	//IZQUIERDA
   	  if (derecha==7 && abajo==4 && izquierda==-7 && arriba==-4){return ;}  
        if (derecha==7 && abajo==3 && izquierda==-7 && arriba==-3){return ;}
        if (derecha==7 && abajo==2 && izquierda==-7 && arriba==-2){return ;}
        if (derecha==7 && abajo==1 && izquierda==-7 && arriba==-1){return ;}
        if (derecha==6 && abajo==3 && izquierda==-6 && arriba==-3){return ;}
        if (derecha==6 && abajo==2 && izquierda==-6 && arriba==-2){return ;}
        if (derecha==6 && abajo==1 && izquierda==-6 && arriba==-1){return ;}
        if (derecha==5 && abajo==1 && izquierda==-5 && arriba==-1){return ;}
        if (derecha==4 && abajo==2 && izquierda==-4 && arriba==-2){return ;}
        if (derecha==1 && abajo==1 && izquierda==-1 && arriba==-1){return ;}
        if (derecha==0 && abajo==0 && izquierda==0 && arriba==0){return ;}
        if (derecha==0 && abajo==1 && izquierda==0 && arriba==-1){return ;}
        if (derecha==0 && abajo==2 && izquierda==0 && arriba==-2){return ;}
        if (derecha==0 && abajo==3 && izquierda==0 && arriba==-3){return ;}
        if (derecha==0 && abajo==4 && izquierda==0 && arriba==-4){return ;}
        if (derecha==0 && abajo==5 && izquierda==0 && arriba==-5){return ;}
        if (derecha==2 && abajo==3 && izquierda==-2 && arriba==-3){return ;}
        if (derecha==3 && abajo==2 && izquierda==-3 && arriba==-2){return ;}
        if (derecha==5 && abajo==4 && izquierda==-5 && arriba==-4){return ;}
        if (derecha==5 && abajo==5 && izquierda==-5 && arriba==-5){return ;}
        if (derecha==1 && abajo==4 && izquierda==-1 && arriba==-4){return ;}
        if (derecha==1 && abajo==3 && izquierda==-1 && arriba==-3){return ;}
        if (derecha==4 && abajo==5 && izquierda==-4 && arriba==-5){return ;}
        if (derecha==2 && abajo==6 && izquierda==-2 && arriba==-6){return ;}
        if (derecha==2 && abajo==5 && izquierda==-2 && arriba==-5){return ;}
        if (derecha==0 && abajo==7 && izquierda==0 && arriba==-7){return ;}
        if (derecha==0 && abajo==6 && izquierda==0 && arriba==-6){return ;}
        if (derecha==6 && abajo==5 && izquierda==-6 && arriba==-5){return ;}
        if (derecha==6 && abajo==4 && izquierda==-6 && arriba==-4){return ;}
        if (derecha==3 && abajo==7 && izquierda==-3 && arriba==-7){return ;}
        if (derecha==7 && abajo==6 && izquierda==-7 && arriba==-6){return ;}
        if (derecha==7 && abajo==7 && izquierda==-7 && arriba==-7){return ;}

      izquierda++;
      derecha--;
      X=X-12.0;
   }

   glutPostRedisplay();


}

// Drawing routine.
void displayMe(void)
{  

   glClear(GL_COLOR_BUFFER_BIT);
   line();
   serpiente();
   glFlush();
}

// Initialization routine.
void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;

      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press +/- to increase/decrease the number of vertices on the circle." << endl;  
   cout << "Press [ESCAPE] to finish." << endl; 
}

// Main routine.
int main(int argc, char **argv) 
{
   	printInteraction();
   	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	   glutInitWindowSize(AnchuraVentana, AlturaVentana);   
	   glutCreateWindow("juego.cpp");
   	init(); 
   	glutDisplayFunc(displayMe); 
   	glutReshapeFunc(resize);  
   	glutKeyboardFunc(keyInput);
      
      glutSpecialFunc(specialKeyInput);
    
   	glutMainLoop(); 

   	return 0;  
}