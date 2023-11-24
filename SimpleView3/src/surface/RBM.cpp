#include "RBM.hpp"

#define Pi 3.141592653589793238462643

RBM::RBM() {
	reset();
}

RBM::~RBM() {
}

void RBM::reset() {
	R = 360;
	S = 5;
	T = 25;
	row = R / 5 + 1;
	col = T + 1;
}

// generate the mesh point and normal of rotation surface

void RBM::RotateCurve() {
	Point pts[col];
	Vector tangents[col];
	// your code
	// 1. call curve->computeBezPtTan function to fill up pts and tangents
	// 2. rotate curve to generate surface mesh point and normal data and store in Pts and Normal.


	curve->computeBezPtsTan(curve->nPts,pts,tangents);

	for (int i = 0; i < row; i++) {
	  for (int j = 0; j < col; j++) {
	    Pts[i][j].x = pts[j].x;
	    Pts[i][j].y = pts[j].y * cos((Pi / 180) * S * i);
	    Pts[i][j].z = pts[j].y * sin((Pi / 180) * S * i);

	    Normal[i][j].x = -tangents[j].y;
	    Normal[i][j].y =  tangents[j].x * cos(((S * i) * (Pi / 180)));
	    Normal[i][j].z =  tangents[j].x * sin(((S * i) * (Pi / 180)));
	  }
	}


}


void RBM::setRotationCurve(Bezier *curve1)
{
	curve = curve1;
}
