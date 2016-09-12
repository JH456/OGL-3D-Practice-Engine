// g++ engine.cpp -lglut -lGL -lGLU -lSDL -o ddd
// g++ engine.cpp -lglut -lGL -o ddd also works
// dependencies: mesa-common-dev and freeglut3-dev

#include "lib3d.cpp"

int main(int argc, char** argv) {
   square = new polygon;
   polygonColor(square, 1.0f, 0.0f, 0.0f);
   addVertex(square, 0.0f, 10.0f, 0.0f);
   addVertex(square, 0.6f, 10.0f, 0.0f);
   addVertex(square, 0.6f, 10.0f, 0.6f);
   addVertex(square, 0.0f, 10.0f, 0.6f);
   square2 = new polygon;
   polygonColor(square2, 0.0f, 0.0f, 1.0f);
   addVertex(square2, 0.0f, 10.6f, 0.0f);
   addVertex(square2, 0.6f, 10.6f, 0.0f);
   addVertex(square2, 0.6f, 10.6f, 0.6f);
   addVertex(square2, 0.0f, 10.6f, 0.6f);
   glutInit(&argc, argv);
   initGL();
   glutMainLoop();
   destroyPolygon(square);
   destroyPolygon(square2);
   return 0;
}
