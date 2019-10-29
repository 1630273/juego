Arc=juego
rm $Arc
g++ -g3 $Arc.cpp -o $Arc -I/usr/X11R/include -L/usr/X11R/lib -lglut -lGL -lGLU -lm -lopenal -lalut -fpermissive -pthread -std=c++11
#g++ -g3 $Arc.c -o $Arc -I/usr/X11R/include -L/usr/X11R/lib -lXi -lXmu -lglut -lGL -lGLU -lm  
./$Arc
