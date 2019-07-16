/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:33:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/11 20:25:40 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	verLine(t_pix *pix, size_t x, int y, int _end, int color)
{
	while (y < _end)
	{
		pix->screen[y * WIDTH + x] = color;
		y++;
	}
}

void	game_process(t_pix *pix)
{
	size_t	y;
	size_t	x;
	double dirX = -1; // начальный вектор направления
	double dirY = 0; // начальный вектор направления
	double planeX = 0;
	double planeY = 0.66; //2D версия Raycaster плоскости камеры

	double time = 0; // время текущего кадра
	double oldTime = 0; // время предыдущего кадра

	// 		double posX = 22;
//		double posY = 12;


//	y = UINT64_MAX;

	x = UINT64_MAX;
		while (++x < pix->width)
	{
		// вычисляем положение и направление луча
		double cameraX = 2 * x / (double)(WIDTH - 1); // координата х в пространстве камеры
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		// в каком поле карты мы находимся
		int mapX = pix->pos.x; // x начальная позиция
		int mapY = pix->pos.y; // y начальная позиция

		// длина луча от текущей позиции до следующей оси x или y
		double sideDistX;
		double sideDistY;

		// длина луча от одной стороны x или y до следующей стороны x или y
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		// в каком направлении нужно двигаться: в направлении x или y? (+1 или -1)
		int stepX;
		int stepY;

		int hit = 0; //ударился ли луч о стену?
		int side; // ??? о какую стену был удар?

		// вычисляем шаг и начальный sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (pix->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - pix->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (pix->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - pix->pos.y) * deltaDistY;
		}


		//perform DDA
		while (hit == 0)
		{
			// переход к следующему квадрату карты, ИЛИ в направлении x, ИЛИ в направлении y
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Проверка ударился ли луч о стену
			if (pix->map[mapY][mapX] > 0)
				hit = 1;
		}

		// Рассчитать расстояние, проецируемое по направлению камеры (евклидово расстояние даст эффект «рыбий глаз»!)
		if (side == 0) perpWallDist = (mapX - pix->pos.x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - pix->pos.y + (1 - stepY) / 2) / rayDirY;

		// Расчет высоты линии для рисования на экране
		int lineHeight = (int)(HEIGHT / perpWallDist);

		// вычисляем нижний и верхний пиксель для заполнения текущей полосы
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		// выбираем цвет стены
		int color;
		int texture;
		texture = (pix->map[mapY][mapX]);
		if (texture == 1)
			color = RED;
		else if (texture == 2)
			color = GREEN;
		else if (texture == 3)
			color = BLUE;
		else if (texture == 4)
			color = YELLOW;

		// дать разной яркости сторонам x и y
//		if (side == 1) {color = color / 2;}

		// рисуем пиксели полосы в виде вертикальной линии
		verLine(pix, x, drawStart, drawEnd, color);
		printf("454\n");
//		//время вывода и счетчик FPS
//		oldTime = time;
//		time = getTicks();
//		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
//		print(1.0 / frameTime); //FPS counter
//		redraw();
//		cls();
	}

}

static t_pix	*init(t_pix *pix)
{
	if (!pix)
		return (NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		//atexit(SDL_Quit());
		errors_msg(8); //уточнить ошибки
	//ошибки
	pix->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

//	pix->ren = SDL_CreateRenderer(pix->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	pix->surf = SDL_GetWindowSurface(pix->win); //
//	pix->surf = IMG_Load("./image2.png");
	pix->screen = (int *)(pix->surf->pixels);
//	screen[y * WIDTH + x] = color;

	pix->screen[5 * WIDTH + 6] = RED;
	pix->screen[5 * WIDTH + 7] = RED;
	pix->screen[5 * WIDTH + 8] = RED;
	pix->screen[5 * WIDTH + 9] = RED;
	pix->screen[5 * WIDTH + 10] = RED;
//	pix->image = SDL_CreateTextureFromSurface(pix->ren, pix->surf);
//	pix->image = IMG_LoadTexture(pix->ren,"./image2.png");


	pix->width = 0;
	pix->height = 0;
	pix->pos = (t_vec2){ 0, 0 };
	return (pix);
}


int				main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int running = 1;
	SDL_Event event;


	t_lines		*lines_head;
	t_pix		*pix;

	if (argc != 2)
		errors_msg(2);
	lines_head = NULL;
	if (!(pix = (t_pix *)malloc(sizeof(t_pix))))
		errors_msg(4);
	init(pix);
	pix->fd = open(argv[1], O_RDONLY);
	if (read(pix->fd, NULL, 0))
		errors_msg(6);
	is_file_valid(pix, &lines_head);
	parsing(pix, lines_head, pix->pos);
	game_process(pix);
	close(pix->fd);

	printf("%s\n", "okaaaay");
	


	if (pix->win == NULL)
		exit (8); //ошибки

	SDL_Rect player_RECT;
	player_RECT.x = WIDTH / 2;   //Смещение полотна по Х
	player_RECT.y = HEIGHT;   //Смещение полотна по Y
	player_RECT.w = WIDTH; //Ширина полотна
	player_RECT.h = HEIGHT; //Высота полотна

//	SDL_RenderClear(pix->ren); //Очистка рендера
//	SDL_RenderCopy(pix->ren, pix->image, NULL, &player_RECT); //Копируем в рендер персонажа
//	SDL_RenderPresent(pix->ren); //Погнали!!

	while (running)
	{
		while (SDL_PollEvent(&event))
			if ((SDL_QUIT == event.type)
				|| (SDL_KEYDOWN == event.type
					&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				running = 0;

		SDL_UpdateWindowSurface(pix->win);
	}

//	SDL_DestroyTexture(pix->image);
//	SDL_DestroyRenderer(pix->ren);
	SDL_FreeSurface(pix->surf);
	SDL_DestroyWindow(pix->win);
	SDL_Quit();
	return (0);
}
