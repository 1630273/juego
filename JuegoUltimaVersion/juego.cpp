#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>

//---------------LIBRERIAS PARA AGREGAR SONIDO (NO TOCAR) --------------------
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>
//----Headers de audio---
#include <AL/al.h>
#include <AL/alc.h>
#ifdef LIBAUDIO
#include <audio/wave.h>
#define BACKEND "libaudio"
#else
#include <AL/alut.h>
#define BACKEND "alut"
#endif
#include <AL/al.h>
#include <AL/alc.h>
#ifdef LIBAUDIO
#include <audio/wave.h>
#define BACKEND "libaudio"
#else
#include <AL/alut.h>
#define BACKEND "alut"
#endif

//----------------------------------------------------------------------------------


#define AlturaVentana 500
#define AnchuraVentana 500
#define PI 3.14159265358979324

using namespace std;



// --------INICIO: Variables para reproducción de SONIDO (no tocar) ----------------------
ALboolean enumeration;
const ALCchar *devices;
const ALCchar *defaultDeviceName = "";
int ret;
#ifdef LIBAUDIO
WaveInfo *wave;
#endif
char *bufferData;
ALCdevice *device;
ALvoid *data;
ALCcontext *context;
ALsizei size, freq;
ALenum format;
ALuint buffer, source;
ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
ALboolean loop = AL_FALSE;
ALCenum error;
ALint source_state;


char sonidos[3][30]={"SonidoColision.wav","SonidoEspacio.wav","SonidoMovimiento.wav"};

//------------------- FIN: Variables para reproducción de SONIDO----------------



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
bool bandera=true;

static float R = 4.0; // Radius of circle.
static int numVertices = 80; // Number of vertices on circle.

static int ran;
static float X ,Y, X1,Y1;



// ------------------Funciones Específicas para AUDIO (no tocar)-----------------------
static void list_audio_devices(const ALCchar *devices)
{
  const ALCchar *device = devices, *next = devices + 1;
  size_t len = 0;

  fprintf(stdout, "Devices list:\n");
  fprintf(stdout, "----------\n");
  while (device && *device != '\0' && next && *next != '\0') {
    fprintf(stdout, "%s\n", device);
    len = strlen(device);
    device += (len + 1);
    next += (len + 2);
  }
  fprintf(stdout, "----------\n");
}

#define TEST_ERROR(_msg)    \
  error = alGetError();   \
  if (error != AL_NO_ERROR) { \
    fprintf(stderr, _msg "\n"); \
    return -1;    \
  }

static inline ALenum to_al_format(short channels, short samples)
{
  bool stereo = (channels > 1);

  switch (samples) {
  case 16:
    if (stereo)
      return AL_FORMAT_STEREO16;
    else
      return AL_FORMAT_MONO16;
  case 8:
    if (stereo)
      return AL_FORMAT_STEREO8;
    else
      return AL_FORMAT_MONO8;
  default:
    return -1;
  }
}

void cargarSonido(int num){
  alListener3f(AL_POSITION, 0, 0, 1.0f);
  TEST_ERROR("listener position");
  alListener3f(AL_VELOCITY, 0, 0, 0);
  TEST_ERROR("listener velocity");
  alListenerfv(AL_ORIENTATION, listenerOri);
  TEST_ERROR("listener orientation");
  alGenSources((ALuint)1, &source);
  TEST_ERROR("source generation");
  alSourcef(source, AL_PITCH, 1);
  TEST_ERROR("source pitch");
  alSourcef(source, AL_GAIN, 1);
  TEST_ERROR("source gain");
  alSource3f(source, AL_POSITION, 0, 0, 0);
  TEST_ERROR("source position");
  alSource3f(source, AL_VELOCITY, 0, 0, 0);
  TEST_ERROR("source velocity");
  alSourcei(source, AL_LOOPING, AL_FALSE);
  TEST_ERROR("source looping");
  alGenBuffers(1, &buffer);
  TEST_ERROR("buffer generation");
  alutLoadWAVFile(sonidos[num], &format, &data, &size, &freq, &loop);
  TEST_ERROR("loading wav file");
  alBufferData(buffer, format, data, size, freq);
  TEST_ERROR("buffer copy");

  alSourcei(source, AL_BUFFER, buffer);
  TEST_ERROR("buffer binding");
}

int Inicializar() 
{
fprintf(stdout, "Using " BACKEND " as audio backend\n");

  enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
  if (enumeration == AL_FALSE)
    fprintf(stderr, "enumeration extension not available\n");

  list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

  if (!defaultDeviceName)
    defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

  device = alcOpenDevice(defaultDeviceName);
  if (!device) {
    fprintf(stderr, "unable to open default device\n");
    return -1;
  }

  fprintf(stdout, "Device: %s\n", alcGetString(device, ALC_DEVICE_SPECIFIER));

  alGetError();

  context = alcCreateContext(device, NULL);
  if (!alcMakeContextCurrent(context)) {
    fprintf(stderr, "failed to make default context\n");
    return -1;
  }
  TEST_ERROR("make default context");

        cargarSonido(0);  
}

int ReproducirSonido(){
  alSourcePlay(source);
  TEST_ERROR("source playing");
  return 0;
}

int Finalizar() {
/* exit context */
  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  device = alcGetContextsDevice(context);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

// -----TERMINA: Funciones Específicas para AUDIO-----------------------








void nivel1(void){

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
   glEnd();  glRasterPos3f(-45.0, 150.0, 0.0);
  
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


void nivel2(void){
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

void meta(){
      float t = 0; // Angle parameter.
   int i;

   glBegin(GL_LINE_LOOP);
      glColor3f(0.0, 1.0, 0.0);
         for(i = 0; i < numVertices; ++i)
     {
          
         glVertex3f(X1 + R * cos(t), Y1 + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
    }
   glEnd();


}




void linel2(void){

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

      glVertex3f(49.0,87.0, 0.0);
      glVertex3f(13.0, 87.0, 0.0);
   glEnd();
   //col2
    glBegin(GL_LINES);

      glVertex3f(49.0,75.0, 0.0);
      glVertex3f(25.0, 75.0, 0.0);
   glEnd();

   //col3

     glBegin(GL_LINES);

      glVertex3f(73.0,63.0, 0.0);
      glVertex3f(85.0, 63.0, 0.0);
   glEnd();
      glBegin(GL_LINES);

      glVertex3f(25.0,63.0, 0.0);
      glVertex3f(61.0, 63.0, 0.0);
   glEnd();

  
   
   //col4
      glBegin(GL_LINES);

      glVertex3f(13.0,51.0, 0.0);
      glVertex3f(49.0, 51.0, 0.0);
   glEnd();

      glBegin(GL_LINES);
      glVertex3f(73.0,51.0, 0.0);
      glVertex3f(99.0, 51.0, 0.0);
   glEnd();

//col5
    glBegin(GL_LINES);

      glVertex3f(1.0,39.0, 0.0);
      glVertex3f(13.0, 39.0, 0.0);
   glEnd();

     glBegin(GL_LINES);

      glVertex3f(49.0,39.0, 0.0);
      glVertex3f(85.0, 39.0, 0.0);
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
      glVertex3f(49.0, 15.0, 0.0);
   glEnd();


     glBegin(GL_LINES);

      glVertex3f(61.0,15.0, 0.0);
      glVertex3f(85.0, 15.0, 0.0);
   glEnd();


//vertical
    glBegin(GL_LINES);

      glVertex3f(13.0,87.0, 0.0);
      glVertex3f(13.0, 51.0, 0.0);
   glEnd();


     glBegin(GL_LINES);

      glVertex3f(13.0,63.0, 0.0);
      glVertex3f(13.0, 39.0, 0.0);
   glEnd();

//col 2
    glBegin(GL_LINES);

      glVertex3f(25.0,75.0, 0.0);
      glVertex3f(25.0, 63.0, 0.0);
   glEnd();


    glBegin(GL_LINES);

      glVertex3f(25.0,39.0, 0.0);
      glVertex3f(25.0, 15.0, 0.0);
   glEnd();


   

   //col3
   

     glBegin(GL_LINES);

      glVertex3f(37.0,51.0, 0.0);
      glVertex3f(37.0, 39.0, 0.0);
   glEnd();

    glBegin(GL_LINES);

      glVertex3f(37.0,27.0, 0.0);
      glVertex3f(37.0, 15.0, 0.0);
   glEnd();


   

    //col4
    

      glBegin(GL_LINES);

      glVertex3f(49.0,39.0, 0.0);
      glVertex3f(49.0, 27.0, 0.0);
   glEnd();
  
//col 5

 
   glBegin(GL_LINES);

      glVertex3f(61.0,87.0, 0.0);
      glVertex3f(61.0, 39.0, 0.0);
   glEnd();





//col 6
   
      glBegin(GL_LINES);

      glVertex3f(73.0,99.0, 0.0);
      glVertex3f(73.0, 63.0, 0.0);
   glEnd();

      glBegin(GL_LINES);

      glVertex3f(73.0,15.0, 0.0);
      glVertex3f(73.0, 1.0, 0.0);
   glEnd();
   
      glBegin(GL_LINES);

      glVertex3f(73.0,39.0, 0.0);
      glVertex3f(73.0, 27.0, 0.0);
   glEnd();
//col7
      


      glBegin(GL_LINES);

      glVertex3f(85.0,87.0, 0.0);
      glVertex3f(85.0, 63.0, 0.0);
   glEnd();


 glBegin(GL_LINES);

      glVertex3f(85.0,15.0, 0.0);
      glVertex3f(85.0, 39.0, 0.0);
   glEnd();
}



void nivel3(void){

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
      glVertex3f(1.0,87.0, 0.0);
      glVertex3f(37.0, 87.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(49.0,87.0, 0.0);
      glVertex3f(73.0, 87.0, 0.0);
   glEnd();

   //col2
   glBegin(GL_LINES);
      glVertex3f(61.0,75.0, 0.0);
      glVertex3f(13.0, 75.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(85.0,75.0, 0.0);
      glVertex3f(99.0, 75.0, 0.0);
   glEnd();
   //col3

   glBegin(GL_LINES);
      glVertex3f(25.0,63.0, 0.0);
      glVertex3f(37.0, 63.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(49.0,63.0, 0.0);
      glVertex3f(61.0, 63.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(85.0,63.0, 0.0);
      glVertex3f(73.0, 63.0, 0.0);
   glEnd();

   //col4
   glBegin(GL_LINES);
      glVertex3f(13.0,51.0, 0.0);
      glVertex3f(25.0, 51.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(49.0,51.0, 0.0);
      glVertex3f(85.0, 51.0, 0.0);
   glEnd();
//col5
   glBegin(GL_LINES);
      glVertex3f(13.0,39.0, 0.0);
      glVertex3f(1.0, 39.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(25.0,39.0, 0.0);
      glVertex3f(49.0, 39.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(73.0,39.0, 0.0);
      glVertex3f(99.0, 39.0, 0.0);
   glEnd();

//col6
   glBegin(GL_LINES);
      glVertex3f(13.0,27.0, 0.0);
      glVertex3f(61.0, 27.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(73.0,27.0, 0.0);
      glVertex3f(85.0, 27.0, 0.0);
   glEnd();


//col 7

  glBegin(GL_LINES);
      glVertex3f(13.0,15.0, 0.0);
      glVertex3f(25.0, 15.0, 0.0);
   glEnd();


  glBegin(GL_LINES);
      glVertex3f(61.0,15.0, 0.0);
      glVertex3f(73.0, 15.0, 0.0);
   glEnd();



  glBegin(GL_LINES);
      glVertex3f(99.0,15.0, 0.0);
      glVertex3f(85.0, 15.0, 0.0);
   glEnd();


//vertical
    glBegin(GL_LINES);

      glVertex3f(13.0,51.0, 0.0);
      glVertex3f(13.0, 63.0, 0.0);
   glEnd();


     glBegin(GL_LINES);

      glVertex3f(13.0,27.0, 0.0);
      glVertex3f(13.0, 15.0, 0.0);
   glEnd();


//col 2
   glBegin(GL_LINES);
      glVertex3f(25.0,51.0, 0.0);
      glVertex3f(25.0, 75.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(25.0,1.0, 0.0);
      glVertex3f(25.0, 15.0, 0.0);
   glEnd();

   //col3
   glBegin(GL_LINES);
      glVertex3f(37.0,63.0, 0.0);
      glVertex3f(37.0, 51.0, 0.0);
   glEnd();

  glBegin(GL_LINES);
      glVertex3f(37.0,27.0, 0.0);
      glVertex3f(37.0, 15.0, 0.0);
   glEnd();
    //col4
   glBegin(GL_LINES);
      glVertex3f(49.0,75.0, 0.0);
      glVertex3f(49.0, 87.0, 0.0);
   glEnd();
   
   glBegin(GL_LINES);
      glVertex3f(49.0,63.0, 0.0);
      glVertex3f(49.0, 39.0, 0.0);
   glEnd();
  
   glBegin(GL_LINES);
      glVertex3f(49.0,15.0, 0.0);
      glVertex3f(49.0, 1.0, 0.0);
   glEnd();
//col 5

   glBegin(GL_LINES);
      glVertex3f(61.0,51.0, 0.0);
      glVertex3f(61.0, 15.0, 0.0);
   glEnd();


//col 6
   
   glBegin(GL_LINES);
      glVertex3f(73.0,87.0, 0.0);
      glVertex3f(73.0, 63.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(73.0,27.0, 0.0);
      glVertex3f(73.0, 39.0, 0.0);
   glEnd();



//col7
      
   glBegin(GL_LINES);
      glVertex3f(85.0,99.0, 0.0);
      glVertex3f(85.0, 87.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(85.0,63.0, 0.0);
      glVertex3f(85.0, 51.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(85.0,27.0, 0.0);
      glVertex3f(85.0,15.0, 0.0);
   glEnd();
}


void nivel4(void){

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
      glVertex3f(73.0,87.0, 0.0);
      glVertex3f(99.0, 87.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(13.0,87.0, 0.0);
      glVertex3f(25.0, 87.0, 0.0);
   glEnd();

   //col2
   glBegin(GL_LINES);
      glVertex3f(85.0,75.0, 0.0);
      glVertex3f(13.0, 75.0, 0.0);
   glEnd();

   //col3

   glBegin(GL_LINES);
      glVertex3f(25.0,63.0, 0.0);
      glVertex3f(61.0, 63.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(85.0,63.0, 0.0);
      glVertex3f(73.0, 63.0, 0.0);
   glEnd();

   //col4
   glBegin(GL_LINES);
      glVertex3f(25.0,51.0, 0.0);
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
      glVertex3f(85.0,27.0, 0.0);
      glVertex3f(25.0, 27.0, 0.0);
   glEnd();


//col 7

  glBegin(GL_LINES);

      glVertex3f(13.0,15.0, 0.0);
      glVertex3f(61.0, 15.0, 0.0);
   glEnd();



//vertical
    glBegin(GL_LINES);

      glVertex3f(13.0,75.0, 0.0);
      glVertex3f(13.0, 51.0, 0.0);
   glEnd();


     glBegin(GL_LINES);

      glVertex3f(13.0,39.0, 0.0);
      glVertex3f(13.0, 15.0, 0.0);
   glEnd();


//col 2
   glBegin(GL_LINES);
      glVertex3f(25.0,99.0, 0.0);
      glVertex3f(25.0, 87.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(25.0,63.0, 0.0);
      glVertex3f(25.0, 51.0, 0.0);
   glEnd();

   //col3
   glBegin(GL_LINES);
      glVertex3f(37.0,87.0, 0.0);
      glVertex3f(37.0, 75.0, 0.0);
   glEnd();

  glBegin(GL_LINES);
      glVertex3f(37.0,27.0, 0.0);
      glVertex3f(37.0, 15.0, 0.0);
   glEnd();
    //col4
   glBegin(GL_LINES);
      glVertex3f(49.0,99.0, 0.0);
      glVertex3f(49.0, 87.0, 0.0);
   glEnd();
   
   glBegin(GL_LINES);
      glVertex3f(49.0,51.0, 0.0);
      glVertex3f(49.0, 39.0, 0.0);
   glEnd();
  
//col 5

   glBegin(GL_LINES);
      glVertex3f(61.0,87.0, 0.0);
      glVertex3f(61.0, 75.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(61.0,39.0, 0.0);
      glVertex3f(61.0, 27.0, 0.0);
   glEnd();

//col 6
   
   glBegin(GL_LINES);
      glVertex3f(73.0,51.0, 0.0);
      glVertex3f(73.0, 39.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(73.0,27.0, 0.0);
      glVertex3f(73.0, 15.0, 0.0);
   glEnd();



//col7
      
   glBegin(GL_LINES);
      glVertex3f(85.0,75.0, 0.0);
      glVertex3f(85.0, 51.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(85.0,39.0, 0.0);
      glVertex3f(85.0, 27.0, 0.0);
   glEnd();


   glBegin(GL_LINES);
      glVertex3f(85.0,1.0, 0.0);
      glVertex3f(85.0,15.0, 0.0);
   glEnd();
}

// Callback routine for non-ASCII key entry.
void specialKeyInputL1(int key, int x, int y)
{
   
   if(key == GLUT_KEY_DOWN){	//ABAJO
   	  if (derecha==7 && abajo==4 && izquierda==-7 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==3 && izquierda==-6 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==2 && izquierda==-5 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==2 && izquierda==-4 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==1 && izquierda==-1 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==1 && izquierda==-2 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==1 && izquierda==-3 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==0 && izquierda==-1 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==0 && izquierda==-2 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==0 && izquierda==-3 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==0 && izquierda==-4 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==5 && izquierda==0 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==5 && izquierda==-1 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==2 && izquierda==-1 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==3 && izquierda==-2 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==3 && izquierda==-3 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==5 && izquierda==-5 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==4 && izquierda==-3 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==4 && izquierda==-2 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==4 && izquierda==-1 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==6 && izquierda==-4 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==6 && izquierda==-3 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==6 && izquierda==-5 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==5 && izquierda==-3 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==7 && izquierda==-2 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==7 && izquierda==-1 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==7 && izquierda==0 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==6 && izquierda==-1 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==7 && izquierda==-3 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==7 && izquierda==-4 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==7 && izquierda==-5 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==7 && izquierda==-6 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==7 && izquierda==-7 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}

      Y= Y-12.0;
      abajo++;
      arriba--;
   }

   if(key == GLUT_KEY_UP){		//ARRIBA
        if (derecha==4 && abajo==1 && izquierda==-4 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==1 && izquierda==-3 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==1 && izquierda==-2 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==1 && izquierda==-1 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==0 && izquierda==0 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==0 && izquierda==-1 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==0 && izquierda==-2 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==0 && izquierda==-3 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==0 && izquierda==-4 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==0 && izquierda==-5 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==0 && izquierda==-6 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==0 && izquierda==-7 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==5 && izquierda==-1 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==2 && izquierda==-1 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==2 && izquierda==-2 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==2 && izquierda==-3 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==3 && izquierda==-4 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==3 && izquierda==-5 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==4 && izquierda==-3 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==4 && izquierda==-2 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==3 && izquierda==-1 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==6 && izquierda==-3 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==6 && izquierda==-5 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==5 && izquierda==-2 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==5 && izquierda==-3 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==7 && izquierda==-1 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==6 && izquierda==0 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==6 && izquierda==-1 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==4 && izquierda==-6 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==7 && izquierda==-5 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==7 && izquierda==-4 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==7 && izquierda==-3 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==5 && izquierda==-7 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}

   	  arriba++;
   	  abajo--;
      Y=Y+12.0;
   }

   if(key == GLUT_KEY_RIGHT){	//DERECHA
   	  if (derecha==7 && abajo==4 && izquierda==-7 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}	
        if (derecha==7 && abajo==3 && izquierda==-7 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==2 && izquierda==-7 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==1 && izquierda==-7 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==0 && izquierda==-7 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==3 && izquierda==-6 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==2 && izquierda==-6 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==1 && izquierda==-6 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==1 && izquierda==-5 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==2 && izquierda==-5 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==1 && izquierda==-4 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==5 && izquierda==-1 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==3 && izquierda==0 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==4 && izquierda==0 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==1 && izquierda==0 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==2 && izquierda==-2 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==2 && izquierda==-3 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==3 && izquierda==-5 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==4 && izquierda==-5 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==5 && izquierda==-5 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==4 && izquierda==-4 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==3 && izquierda==-1 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==5 && izquierda==-4 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==5 && izquierda==-3 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==7 && izquierda==-2 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==6 && izquierda==-1 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==6 && izquierda==-6 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==4 && izquierda==-6 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==7 && izquierda==-6 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==5 && izquierda==-7 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==6 && izquierda==-7 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==7 && izquierda==-7 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}


   	  derecha++;
   	  izquierda--;
      X=X+12.0;
   	  
      
   }

   if(key == GLUT_KEY_LEFT){	//IZQUIERDA
   	  if (derecha==7 && abajo==4 && izquierda==-7 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}  
        if (derecha==7 && abajo==3 && izquierda==-7 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==2 && izquierda==-7 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==1 && izquierda==-7 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==3 && izquierda==-6 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==2 && izquierda==-6 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==1 && izquierda==-6 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==1 && izquierda==-5 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==2 && izquierda==-4 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==1 && izquierda==-1 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==0 && izquierda==0 && arriba==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==1 && izquierda==0 && arriba==-1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==2 && izquierda==0 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==3 && izquierda==0 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==4 && izquierda==0 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==5 && izquierda==0 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==3 && izquierda==-2 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==2 && izquierda==-3 && arriba==-2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==4 && izquierda==-5 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==5 && abajo==5 && izquierda==-5 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==4 && izquierda==-1 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==1 && abajo==3 && izquierda==-1 && arriba==-3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==4 && abajo==5 && izquierda==-4 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==6 && izquierda==-2 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==2 && abajo==5 && izquierda==-2 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==7 && izquierda==0 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==0 && abajo==6 && izquierda==0 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==5 && izquierda==-6 && arriba==-5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==6 && abajo==4 && izquierda==-6 && arriba==-4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==3 && abajo==7 && izquierda==-3 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==6 && izquierda==-7 && arriba==-6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
        if (derecha==7 && abajo==7 && izquierda==-7 && arriba==-7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}

      izquierda++;
      derecha--;
      X=X-12.0;
   }
  cargarSonido(2);
  ReproducirSonido();
   glutPostRedisplay();


}



// Callback routine for non-ASCII key entry.
void specialKeyInputL2(int key, int x, int y)
{
     if(key == GLUT_KEY_DOWN)   //ABAJO
   {
      if (derecha==0 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}

     Y= Y-12.0;
     abajo++;
     arriba--;
      
   }
   if(key == GLUT_KEY_UP)   //ARRIBA
   {

      if (derecha==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}

     Y=Y+12.0;
     arriba++;
     abajo--;
  }

   if(key == GLUT_KEY_RIGHT)    //DERECHA
   {
      if (derecha==0 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}

      X=X+12.0;
      derecha++;
      izquierda--;

   }
   if(key == GLUT_KEY_LEFT)   //IZQUIERDA
   {
      if (derecha==0 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==5 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==0){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==5){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==7 && abajo==6){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==7){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==2 && abajo==6){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==6){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==3 && abajo==6){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==0 && abajo==7){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==4 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
      if (derecha==6 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
      X=X-12.0;
      izquierda++;
      derecha--;

   }
    cargarSonido(2);
  ReproducirSonido();
   glutPostRedisplay();

}




// Callback routine for non-ASCII key entry.
void specialKeyInputL3(int key, int x, int y)
{
   if(key == GLUT_KEY_DOWN)   //ABAJO
   {

    if (izquierda==4 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==0 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-4 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==4 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==4 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==3 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==3 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==3 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==2 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==2 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==1 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==0 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==0 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==0 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==0 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==0 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==1 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==1 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==2 && arriba==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==3 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (derecha==3 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}


     Y= Y-12.0;
     abajo++;
     arriba--;
      
   }
   if(key == GLUT_KEY_UP)   //ARRIBA
   {
    if (izquierda == 0 && arriba == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==4 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==1 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	if (izquierda==0 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-3 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-2 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==-1 && arriba==4){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==4 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==4 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==3 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==2 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==1 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==0 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==0 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==0 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (izquierda==0 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==1 && arriba==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==2 && arriba==0){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
   	if (derecha==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}



     Y=Y+12.0;
     arriba++;
     abajo--;
  }

   if(key == GLUT_KEY_RIGHT)    //DERECHA
   {
     
     if (izquierda == 0 && arriba == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == 4){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == -4){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == -1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == -2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 3 && arriba == -3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 4 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 4 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 3 && abajo == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 3 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 3 && arriba == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 2 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 2 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 1 && abajo == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 1 && abajo == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 1 && abajo == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 1 && arriba == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 1 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 0 && abajo == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 0 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 1 && abajo == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 1 && arriba == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 1 && arriba == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 2 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 2 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (derecha == 2 && arriba == 4){    cargarSonido(0);
  ReproducirSonido();return ;}


      X=X+12.0;
      derecha++;
      izquierda--;

   }
   if(key == GLUT_KEY_LEFT)   //IZQUIERDA
   {
     if (izquierda == 0 && arriba == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
     if (izquierda == 4 && arriba == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == 4){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == -1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == -2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == -3){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 4 && arriba == -4){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 3 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 3 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 2 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 2 && arriba == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 2 && abajo == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 1 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 1 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 0 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 0 && arriba == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (izquierda == 0 && abajo == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 1 && abajo == 0){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 1 && abajo == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 1 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 2 && abajo == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 2 && arriba == 2){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 2 && arriba == 3){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 3 && arriba == 1){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 3 && arriba == 4){    cargarSonido(0);
  ReproducirSonido();return ;}
	 if (derecha == 3 && abajo == 2){    cargarSonido(0);
  ReproducirSonido();return ;}


      X=X-12.0;
      izquierda++;
      derecha--;

   }
    cargarSonido(2);
  ReproducirSonido();
   glutPostRedisplay();
}



// Callback routine for non-ASCII key entry.
void specialKeyInputL4(int key, int x, int y)
{
   if(key == GLUT_KEY_DOWN)   //ABAJO
   {
	   	if (izquierda==4 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==1 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==3 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==3 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && arriba==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==1 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}


     Y= Y-12.0;
     abajo++;
     arriba--;
      
   }
   if(key == GLUT_KEY_UP)   //ARRIBA
   {
	   	if (izquierda==4 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==1 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==0 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==1 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==3 && arriba==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==3 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==1 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==3 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}


     Y=Y+12.0;
     arriba++;
     abajo--;
  }

   if(key == GLUT_KEY_RIGHT)    //DERECHA
   {
	   	if (derecha==3 && arriba==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (derecha==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==4 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==4 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==4 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==4 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==3 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (izquierda==0 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==1 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
		if (derecha==2 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	

   	      

      X=X+12.0;
      derecha++;
      izquierda--;

   }
   if(key == GLUT_KEY_LEFT)   //IZQUIERDA
   {
	    if (izquierda==4 && arriba==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==4 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}     
	   	if (izquierda==4 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	   	if (izquierda==4 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==4 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==4 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==4 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==4 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==3 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==3 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==2 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==2 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==1 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==1 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==0 && arriba==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (izquierda==0 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==1 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==1 && arriba==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==2 && abajo==2){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==2 && abajo==4){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==3 && abajo==0){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==3 && abajo==1){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==3 && abajo==3){    cargarSonido(0);
  ReproducirSonido();return ;}
	    if (derecha==3 && abajo==5){    cargarSonido(0);
  ReproducirSonido();return ;}
     

      X=X-12.0;
      izquierda++;
      derecha--;

   }
    cargarSonido(2);
  ReproducirSonido();
   glutPostRedisplay();
}


int aleatorio(){
  arriba = 0;
  abajo = 0;
  derecha = 0;
  izquierda = 0;
    srand(time(NULL));
  
        ran = 1 + rand() % (5 - 1);

        
   if(ran==1){
            
            X = 7.0; 
            Y = 93.0;
            X1= 91.0; 
            Y1= 9.0; 
         

      }

      
      if(ran==2){
            X = 7.0; 
            Y = 93.0;
            X1= 67.0; 
            Y1= 33.0; 
        
      }

      
      if(ran==3){
            X = 55.0; 
            Y = 45.0;
            X1= 31.0; 
            Y1= 21.0; 
         
      }

      
      if(ran==4){
            X = 55.0; 
            Y = 69.0;
            X1= 31.0; 
            Y1= 21.0; 
         
      }
}  
  



void serpiente(float X, float Y){
      float t = 0; // Angle parameter.

   glBegin(GL_POLYGON);
      glColor3f(0.0, 1.0, 0.0);
         for(int i = 0; i < numVertices; ++i)
	   {
          
         glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
	  }
   glEnd();


}


void meta(float X1, float Y1){
   float t = 0; // Angle parameter.

   glBegin(GL_LINE_LOOP);
      glColor3f(0.0, 1.0, 0.0);
         for(int i = 0; i < numVertices; ++i)
     {
          
         glVertex3f(X1 + R * cos(t), Y1 + R * sin(t), 0.0);
         t += 2 * PI / numVertices;
    }
   glEnd();


}


// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string){  
   
   char *c;
   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}


void portada(){
   glColor3f(1.0,1.0,1.0);

   
   glRasterPos3f(25.0, 85.0, 0.0);
   writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "MAZES & MORE (Classic)");

   glRasterPos3f(25.0, 65.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Preciona espacio para continuar");

   glRasterPos3f(45.0, 35.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Integrantes:");
   
   glRasterPos3f(35.0, 30.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Brian Alejandro Mireles Ortiz");
      
   glRasterPos3f(35.0, 25.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Jose Rafael Perez Rodriguez");

   
   glRasterPos3f(35.0, 20.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Jari Alberto Martinez Gonzalez");

   
   glRasterPos3f(35.0, 15.0, 0.0);
   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Yashub Armando Guzaman Espinoza");




}

void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      case ' ':
        cargarSonido(1);
  ReproducirSonido();
         bandera=false;
         aleatorio();
         
  
         break;

      default:
         break;
   }
      glutPostRedisplay();
}



// Drawing routine.
void displayMe(void)
{  


   glClear (GL_COLOR_BUFFER_BIT);
   glLoadIdentity();



   if (bandera==true){
   portada();
   }  else
   {
      
   if(ran==1){
      
           glutSpecialFunc(specialKeyInputL1);
            nivel1();

      }

      
      if(ran==2){
         
            glutSpecialFunc(specialKeyInputL1);
            nivel1();
      }

      
      if(ran==3){
        
            glutSpecialFunc(specialKeyInputL3);
            nivel3();
      }

      
      if(ran==4){
         
            glutSpecialFunc(specialKeyInputL4);
            nivel4();
      }

   serpiente(X,Y);
   meta(X1,Y1);

   if(X==X1&&Y==Y1){
      aleatorio();
         
      
   }
   }
   

   
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
    Inicializar();
   	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
	   glutInitWindowSize(AnchuraVentana, AlturaVentana);   
	   glutCreateWindow("juego.cpp");
   	init(); 
   	glutDisplayFunc(displayMe); 
   	glutReshapeFunc(resize);  
      glutKeyboardFunc(keyInput);
   	
   	glutMainLoop(); 


   	return 0;  
}