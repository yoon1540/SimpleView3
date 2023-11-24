#include "Bezier.hpp"


extern GLint winWidth, winHeight;

Bezier::Bezier() {
	reset();
}

void Bezier::reset() {
	nCtrlPts = 0;
	nPts = 26;
}

/*  Compute binomial coefficients C[n] for given value of n, output in GLint C[] */
void Bezier::binomialCoeffs(GLint n, GLint C[]) {
	// your code, using O(n) algorithm for C_{n, i), i = 0, 1, ..., n
	C[0] = 1;
	for (int i = 0; i < n; ++i){
		C[i+1] = C[i]*(n-i)/(i+1);
	}
}

/*  Compute Bezier point at u, and output in Point *bezPt */
void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt)
{
  // your code
	double be[nCtrlPts];
	int n = nCtrlPts - 1;
	double ra;
	if (nCtrlPts > 0 && u >= 0 && u <= 1) {
		if (1-u >= 0.0001) {
			ra = u / (1.0-u);
			be[0] = pow(1.0-u,n);
			for (int i = 1; i <= n; ++i) {
				be[i] = be[i-1] * (n-i+1) / i * ra;
			}
			for (int i = 0; i < nCtrlPts; ++i){
				bezPt->x += ctrlPts[i].x * be[i];
				bezPt->y += ctrlPts[i].y * be[i];
				bezPt->z += ctrlPts[i].z * be[i];
			}
		}
		else{
			bezPt->x = ctrlPts[n].x;
			bezPt->y = ctrlPts[n].y;
			bezPt->z = ctrlPts[n].z;
		}
	}else{
		bezPt->x = ctrlPts[0].x;
		bezPt->y = ctrlPts[0].y;
		bezPt->z = ctrlPts[0].z;
	}
}

/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt, Vector *bezTan)
{
// your code
	double be[nCtrlPts];
	double ra;
	int n = nCtrlPts - 1;
	if (nCtrlPts > 1 && u >= 0 && u <= 1) {
		if (u >= 0.001) {
			if (1-u >= 0.001) {
				ra = u/(1.0-u);
				be[0] = pow(1.-u, n);
				for (int i = 1; i <=n; ++i) {
					be[i] = be[i-1] * ra;
				}
				for (int i = 0; i < nCtrlPts; ++i) {
					bezPt->x += ctrlPts[i].x * be[i]* C[i];
					bezPt->y += ctrlPts[i].y * be[i]* C[i];
					bezPt->z += ctrlPts[i].z * be[i]* C[i];
					ra = i/u-(n-i)/(1.0-u);
					bezTan->x += ctrlPts[i].x * be[i] * ra* C[i];
					bezTan->y += ctrlPts[i].y * be[i] * ra* C[i];
					bezTan->z += ctrlPts[i].z * be[i] * ra* C[i];
				}
			}else{
				bezPt->x = ctrlPts[n].x;
				bezPt->y = ctrlPts[n].y;
				bezPt->z = ctrlPts[n].z;
				bezTan->x = ctrlPts[n].x - ctrlPts[n-1].x;
				bezTan->y = ctrlPts[n].y - ctrlPts[n-1].y;
				bezTan->z = ctrlPts[n].z - ctrlPts[n-1].z;
			}
		}else{
			bezPt->x = ctrlPts[0].x;
			bezPt->y = ctrlPts[0].y;
			bezPt->z = ctrlPts[0].z;
			bezTan->x = ctrlPts[1].x - ctrlPts[0].x;
			bezTan->y = ctrlPts[1].y - ctrlPts[0].y;
			bezTan->z = ctrlPts[1].z - ctrlPts[0].z;
		}
	}
}


/* call to compute the sequence of points on Bezier curve for drawing Bezier curve */
void Bezier::computeBezCurvePts() {
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < nPts; k++) {
		u = GLfloat(k) / GLfloat(nPts-1);
		computeBezPt(u, nCtrlPts, ctrlPts, C, &Pts[k]);
	}
}


/* call to compute the sequence of points and tangents on Bezier curve for mesh of rotating Bezier curve */
void Bezier::computeBezPtsTan(GLint npts, Point pts[], Vector tangents[]) {
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < npts; k++) {
		u = GLfloat(k) / GLfloat(npts-1);
		computeBezPtTan(u, nCtrlPts, ctrlPts, C, &pts[k],  &tangents[k]);
	}
}


void Bezier::drawCPts() {
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < nCtrlPts; i++) {
		glVertex2f(ctrlPts[i].x, ctrlPts[i].y);
	}
	glEnd();
}

/* display Control points in 2D view */
void Bezier::displayCPts() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
}

/* display Control points and curve in 2D view */
void Bezier::display() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
	drawCurve();
}

