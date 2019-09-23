/*
* Example 9-4.Slight modified code from the OpenCV documentation that draws a
* cube every frame;this modified version uses the global variables rotx and roty
* that are connected to the sliders in Figure 9-6
*/
// note: can't install openGL library.

#include <GL/gl.h>
#include <GL/glu.h>

#include<opencv2/opencv.hpp>
#include<opencv2/core/opengl.hpp>
#include<iostream>

using namespace std;

int rotx = 55, roty = 40;

void on_opengl(void* param)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -1.0);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	glRotatef(0, 0, 0, 1);

	static const int coords[6][4][3] = {
		{ { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
		{ { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
		{ { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
		{ { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
		{ { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
		{ { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } },
	};

	for (int i = 0; i < 6; ++i)
	{
		glColor3ub(i * 20, 100 + i * 10, i * 42);
		glBegin(GL_QUADS);
		for (int j = 0; j < 4; ++j)
		{
			glVertex3d(
				0.2 * coords[i][j][0],
				0.2 * coords[i][j][1],
				0.2 * coords[i][j][2]
				);
		}
		glEnd();
	}
}
