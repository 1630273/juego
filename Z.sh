
NombreProgramaFuente=JuegoNivel3
rm $NombreProgramaFuente
g++ $NombreProgramaFuente.cpp -o $NombreProgramaFuente -lGL -lglut -lGLEW -lGLU -lm
./$NombreProgramaFuente
