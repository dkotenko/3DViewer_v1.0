#include <SDL2/SDL.h> // Библиотека SDL 2

#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include <stdio.h>
#include <stdbool.h>

SDL_Window *window; // задаем окно для SDL

const int width = 640; // ширина окна
const int height = 480; // высота окна

void drawCube(float xrf, float yrf, float zrf);



void init(){

	// Инициализация SDL

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
		printf("SDL init error\n");
		exit(1);
	}

	// Включаем двойной буфер, настраиваем цвета

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

	window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

	if(window == NULL){	// если не получилось создать окно, то выходим
		exit(1);
	}

	// Инициализация OpenGL

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
}

void drawCube(float xrf, float yrf, float zrf){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

	glBegin(GL_QUADS);		// Рисуем куб

	glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
	glVertex3f( 1.0f, 1.0f, -1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, -1.0f);		// Верхний левый
	glVertex3f(-1.0f, 1.0f,  1.0f);		// Нижний левый
	glVertex3f( 1.0f, 1.0f,  1.0f);		// Нижний правый

	glColor3f(1.0f, 0.5f, 0.0f);		// Оранжевая сторона (Нижняя)
	glVertex3f( 1.0f, -1.0f,  1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f,  1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

	glColor3f(1.0f, 0.0f, 0.0f);		// Красная сторона (Передняя)
	glVertex3f( 1.0f,  1.0f, 1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f,  1.0f, 1.0f);		// Верхний левый
	glVertex3f(-1.0f, -1.0f, 1.0f);		// Нижний левый
	glVertex3f( 1.0f, -1.0f, 1.0f);		// Нижний правый

	glColor3f(1.0f,1.0f,0.0f);			// Желтая сторона (Задняя)
	glVertex3f( 1.0f, -1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f,  1.0f, -1.0f);	// Нижний левый
	glVertex3f( 1.0f,  1.0f, -1.0f);	// Нижний правый

	glColor3f(0.0f,0.0f,1.0f);			// Синяя сторона (Левая)
	glVertex3f(-1.0f,  1.0f,  1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f,  1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f(-1.0f, -1.0f,  1.0f);	// Нижний правый

	glColor3f(1.0f,0.0f,1.0f);			// Фиолетовая сторона (Правая)
	glVertex3f( 1.0f,  1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f( 1.0f,  1.0f,  1.0f);	// Верхний левый
	glVertex3f( 1.0f, -1.0f,  1.0f);	// Нижний левый
	glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

	glEnd();	// Закончили квадраты

}

int main(int argc, char *argv[]){

	init(); // инициализация

	bool running = true;

	float xrf = 0, yrf = 0, zrf = 0; // углы поворота

	while(running){

		SDL_Event event; // события SDL

		while ( SDL_PollEvent(&event) ){ // начинаем обработку событий
			switch(event.type){ // смотрим:
	case SDL_QUIT: // если произошло событие закрытия окна, то завершаем работу программы
		running = false;
	break;

	case SDL_KEYDOWN: // если нажата клавиша
		switch(event.key.keysym.sym){ // смотрим какая
			case SDLK_ESCAPE: // клавиша ESC
	running = false; // завершаем работу программы
			break;
		}
	break;
			}
		}

	// пока программа запущена изменяем углы поворота, тем самым вращая куб

		xrf -= 0.01;
		yrf -= 0.01;
		zrf -= 0.01;

		drawCube(xrf, yrf, zrf); // рисуем сам куб с текущими углами поворота

		// обновляем экран

		glFlush();
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit(); // завершаем работу SDL и выходим
	return 0;
}