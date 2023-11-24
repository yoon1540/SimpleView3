/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */
#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"


class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];
	GLint face[4][4];
	GLfloat faceColor[4][3];
	Vector faceNormal[4];
	GLfloat vertexColor[5][3];
	GLfloat vertexNormal[5][3];
	GLfloat r, g, b;

public:
	Pyramid();
	void draw();
	void drawMC();
	bool isFrontface(int faceindex, Camera camera);
	GLfloat getFaceShade(int faceindex, Light light);
	GLfloat getVertexShade(int vertexindex, Light light);

private:
	void drawFace(GLint i);
};


#endif  /* PYRAMID_HPP_ */


