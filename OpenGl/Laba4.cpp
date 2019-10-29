#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct coord {
	double x, y;
	int index = -1;
};

struct edge {
	struct coord * first, * second;
};

float kX = 0.f, kY = 0.f, kZ = 0.f;
float mX = 0.f, mY = 0.f, mZ = 0.f;
float k = 1;

double xpos, ypos;
const int size_H = 640;
const int size_W = 640;
GLubyte bytes[size_H][size_W][4];

struct coord points[100];
vector<edge> edges;
vector<coord> coords;
//edges.resize(100);
//struct edge edges[100];
int current = 0;
int number = 0;

bool compare_x(const coord&coord1, const coord &coord2) {
	return (coord1.x < coord2.x);
}

bool compare_y(const coord&coord1, const coord &coord2) {
	return (coord1.y < coord2.y);
}

void brezenheim(int i) {
	int x_draw, y_draw;
	//if (points[i].x > points[i - 1].x) {
		x_draw = (int)points[i - 1].x;
		y_draw = (int) points[i - 1].y;
	//}
	//else {
		//x_draw = points[i].x;
		//y_draw = points[i].y;
	//}

	bytes[y_draw][x_draw][0] = 255;
	bytes[y_draw][x_draw][1] = 0;
	bytes[y_draw][x_draw][2] = 0;
	bytes[y_draw][x_draw][3] = 255;

	double dx = abs((int)(points[i - 1].x - points[i].x));
	double dy = abs((int)(points[i - 1].y - points[i].y));
	printf("x_d%f y_d%f ", points[i - 1].x, points[i - 1].y);
	printf("x_draw%i y_draw%i ", x_draw, y_draw);

	if (dy != 0) {
		struct coord point_1;
		point_1.x = x_draw;
		point_1.y = y_draw;
		point_1.index = i - 1;
		coords.push_back(point_1);
	}

	
	double p = 2 * dy - dx;
	double sx;
	if (points[i].x - points[i - 1].x > 0) {
		sx = 1;
	}
	else {
		sx = -1;
	}
	
	double sy;
	if (points[i].y - points[i - 1].y > 0) {
		sy = 1;
	}
	else {
		sy = -1;
	}
	int swap = 0;
	if (dy > dx) {
		swap = 1;
		double s = dy;
		dy = dx;
		dx = s;
	}
	for (auto j = 0; j < dx; j++) {
		if (p >= 0) {
			if (swap == 0) {
				y_draw += sy;
				x_draw += sx;
			}
			else {
				x_draw += sx;
				y_draw += sy;
			}
			p += (2 * dy - 2 * dx);
		}else {
			if (swap == 0) {
				x_draw += sx;
			}
			else {
				y_draw += sy;
				
			}
			p += 2 * dy;
		}
		bytes[y_draw][x_draw][0] = 255;
		bytes[y_draw][x_draw][1] = 0;
		bytes[y_draw][x_draw][2] = 0;
		bytes[y_draw][x_draw][3] = 255;
		printf("%d %d ", x_draw, y_draw);

		if (dy != 0) {
			struct coord point_2;
			point_2.x = x_draw;
			point_2.y = y_draw;
			coords.push_back(point_2);
		}
	}

	
	//printf("%d %d ", dx, dy);
	
}


void painting() {
	sort(coords.begin(), coords.end(), compare_y);
	//coord* i = coords.begin();
	for (std::vector<coord>::iterator it = coords.begin(); it != coords.end(); ) {
		std::vector<coord>::iterator it1 = it;
		for (; it1 != coords.end(); ++it1) {
			if ((*it1).y < (*(it1 - 1)).y) break;
		}
		sort(it, it1, compare_x);
		it = it1;
	}

	for (std::vector<coord>::iterator it = coords.begin(); it != coords.end();it+=2) {
		if ((*it).index > 1 && (*it).index < current-1) {
			if (points[(*it).index - 1].y > points[(*it).index].y && points[(*it).index + 1].y > points[(*it).index].y) {
				continue;
			}
			for (auto i = (*it).x; i < (*(it + 1)).x; i++) {
				int x = (int)i;
				int y = (int)((*it).y);
				bytes[y][x][0] = 255;
				bytes[y][x][1] = 0;
				bytes[y][x][2] = 0;
				bytes[y][x][3] = 255;
			}
		}
	}



}

void makepoints() {
	if (number > current) {
		points[current].x = xpos ;
		points[current].y = size_W - ypos;
		printf("xcurr%f ycurr%f ", points[current].x, points[current].y);
		//printf("%d %d ", x_draw, y_draw);
		current = number;
	}
	if (number > 1) {
		edge edge_1;
		edge_1.first = &points[current - 2];
		edge_1.second = &points[current - 1];
		edges.push_back(edge_1);
		brezenheim(current-1);
	}
}


void makebytes() {
	for (auto i = 0; i < size_H; i++) {
		for (auto j = 0; j < size_W; j++) {
			bytes[i][j][0] = 0;
			bytes[i][j][1] = 0;
			bytes[i][j][2] = 0;
			bytes[i][j][3] = 255;
		}
	}
	
}


void display(GLFWwindow * window)
{
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	float   ratio = screenWidth / (float)screenHeight;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // depth testing
	glDepthFunc(GL_LEQUAL);

	glViewport(0.0f, 0.0f, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f * 3, -1.f * 3);// essentially set coordinate system

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	makepoints();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2f(-ratio, -ratio);
	glPixelZoom(1,1);
	//glPixelStorei(GL_UNPACK_ROW_LENGTH, 100);
	//glPixelStorei(GL_UNPACK_SKIP_ROWS, 1);
	//glPixelStorei(GL_UNPACK_SKIP_PIXELS, 1);


	glDrawPixels(size_H, size_W, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	//glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	//glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	//glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	//glFlush();


	glfwSwapBuffers(window);
	glfwPollEvents();
}

void draw(GLFWwindow * window) {
	makebytes();
	//makepoints();
	while (!glfwWindowShouldClose(window))
	{
		display(window);
	}
}

void error(int error, const char * description)
{
	fputs(description, stderr);
}
void key(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_TAB:
			painting();
			break;
		}

	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void button(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		number++;
		//drawPoint();
		printf("%f %f", xpos, ypos);
	}
}

void windowSize(GLFWwindow* window, int width, int height) {
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	width = w;
	height = h;
}

int main()
{
	glfwSetErrorCallback(error);
	if (!glfwInit()) return -1;
	GLFWwindow * window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_WIDTH, "LABA_4", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glDrawBuffer(GL_BACK);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key);
	glfwSetWindowSizeCallback(window, windowSize);
	glfwSetMouseButtonCallback(window, button);
	glRasterPos2f(0, 0);
	glClearColor(0, 0, 0, 0);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	draw(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


/*for (auto j = 0; j < dx ; j++) {
		if (swap == 1) {
			x_draw += sx;
		}
		else {
			y_draw += sy;
		}
		if (p < 0) {
			p += 2 * dy;
		}
		else {
			if (swap == 1) {
				y_draw += sy;
			}
			else {
				x_draw += sx;
			}
			p += 2 * dy - 2 * dx;
		}
		bytes[x_draw][y_draw][0] = 0;
		bytes[x_draw][y_draw][1] = 0;
		bytes[x_draw][y_draw][2] = 0;
		printf("%d %d ", x_draw, y_draw);
	}*/