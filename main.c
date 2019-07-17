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

static void		walk(t_pix *pix, t_vec2 dir, double moveSpeed)
{
	if (!(pix->map[(int)(pix->pos.x + dir.x * moveSpeed)][(int)(pix->pos.y)]))
		pix->pos.x += dir.x * moveSpeed;
	if (!(pix->map[(int)(pix->pos.x)][(int)(pix->pos.y + dir.y * moveSpeed)]))
		pix->pos.y += dir.y * moveSpeed;
	// двигаться назад, если позади вас нет стены
	if (!(pix->map[(int)(pix->pos.x - dir.x * moveSpeed)][(int)(pix->pos.y)]))
		pix->pos.x -= dir.x * moveSpeed;
	if (!(pix->map[(int)(pix->pos.x)][(int)(pix->pos.y - dir.y * moveSpeed)]))
		pix->pos.y -= dir.y * moveSpeed;
}

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
//	size_t	y;
	size_t	x;

//	y = UINT64_MAX;

	printf("%f %f\n", pix->pos.x, pix->pos.y);
//	pix->pos.x = 9; // x начальная позиция
//	pix->pos.y = 2; // y начальная позиция
	x = UINT64_MAX;
		while (++x < WIDTH) {
			// вычисляем положение и направление луча
			double cameraX =
					2.0f * x / WIDTH - 1; // координата х в пространстве камеры
			double rayDirX = pix->dir.x + pix->plane.x * cameraX;
			double rayDirY = pix->dir.y + pix->plane.y * cameraX;

			// в каком поле карты мы находимся
			double mapX = pix->pos.x; // x начальная позиция
			double mapY = pix->pos.y; // y начальная позиция

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
			int side = 0; // ??? о какую стену был удар?

			// вычисляем шаг и начальный sideDist
			if (rayDirX < 0) {
				stepX = -1;
				sideDistX = (pix->pos.x - mapX) * deltaDistX;
			} else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - pix->pos.x) * deltaDistX;
			}
			if (rayDirY < 0) {
				stepY = -1;
				sideDistY = (pix->pos.y - mapY) * deltaDistY;
			} else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - pix->pos.y) * deltaDistY;
			}


			//perform DDA
			while (hit == 0) {
				// переход к следующему квадрату карты, ИЛИ в направлении x, ИЛИ в направлении y
				if (sideDistX < sideDistY) {
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				} else {
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Проверка ударился ли луч о стену
				if (pix->map[(int) mapY][(int) mapX] > 0)
					hit = 1;
			}

			// Рассчитать расстояние, проецируемое по направлению камеры (евклидово расстояние даст эффект «рыбий глаз»!)
			if (side == 0)
				perpWallDist =
						(mapX - pix->pos.x + (1.0f - stepX) / 2.0f) / rayDirX;
			else
				perpWallDist =
						(mapY - pix->pos.y + (1.0f - stepY) / 2.0f) / rayDirY;

			// Расчет высоты линии для рисования на экране
			int lineHeight = (int) (HEIGHT / perpWallDist);

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
			texture = (pix->map[(int) mapY][(int) mapX]);
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
//		printf("%.2f %.2f\n", rayDirX, rayDirY);








			//	readKeys();
//		walk();

//		// повернуть вправо
//		if (keyDown(SDLK_RIGHT))
//		{
//			// направление камеры и плоскость камеры должны быть повернуты
//			double oldDirX = pix->dir.x;
//			pix->dir.x = pix->dir.x * cos(-rotSpeed) - pix->dir.y * sin(-rotSpeed);
//			pix->dir.y = oldDirX * sin(-rotSpeed) + pix->dir.y * cos(-rotSpeed);
//			double oldPlaneX = pix->plane.x;
//			pix->plane.x = pix->plane.x * cos(-rotSpeed) - pix->plane.y * sin(-rotSpeed);
//			pix->plane.y = oldPlaneX * sin(-rotSpeed) + pix->plane.y * cos(-rotSpeed);
//		}
//		// повернуть налево
//		if (keyDown(SDLK_LEFT))
//		{
//			// направление камеры и плоскость камеры должны быть повернуты
//			double oldDirX = pix->dir.x;
//			pix->dir.x = pix->dir.x * cos(rotSpeed) - pix->dir.y * sin(rotSpeed);
//			pix->dir.y = oldDirX * sin(rotSpeed) + pix->dir.y * cos(rotSpeed);
//			double oldPlaneX = pix->plane.x;
//			pix->plane.x = pix->plane.x * cos(rotSpeed) - pix->plane.y * sin(rotSpeed);
//			pix->plane.y = oldPlaneX * sin(rotSpeed) + pix->plane.y * cos(rotSpeed);
//		}
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
//	pix->image = SDL_CreateTextureFromSurface(pix->ren, pix->surf);
//	pix->image = IMG_LoadTexture(pix->ren,"./image2.png");

	pix->flag = (t_flag) { 0 };
	pix->dir = (t_vec2) { 1, 0 };
	pix->plane = (t_vec2) { 0, 0.66 };
	pix->width = 0;
	pix->height = 0;
	pix->pos = (t_vec2){ 0 };
	pix->time = 0; // время текущего кадра
	pix->oldTime = 0; // время предыдущего кадра
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
	parsing(pix, lines_head, &pix->pos);
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
	{			//время вывода и счетчик FPS
		pix->oldTime = pix->time;
		pix->time = SDL_GetTicks();
		pix->frameTime = (pix->time - pix->oldTime) / 1000.0; //frameTime - время, которое этот кадр занял, в секундах
//		print(1.0 / frameTime); //FPS counter
//		redraw();
//		cls();
//
//		 модификаторы скорости
		pix->moveSpeed = pix->frameTime *
							 5.0; //the constant value is in squares/second
			double rotSpeed = pix->frameTime *
							  3.0; //the constant value is in radians/second
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type)
			|| (SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym))
				running = 0;

			if (SDL_KEYDOWN == event.type && SDLK_UP == event.key.keysym.sym)
			{
				pix->flag.straight = true;
			}
			if (SDL_KEYDOWN == event.type && SDLK_DOWN == event.key.keysym.sym)
			{
				pix->flag.back = true;
			}

			if (SDL_KEYUP == event.type && SDLK_UP == event.key.keysym.sym)
			{
				pix->flag.straight = false;
			}
			if (SDL_KEYUP == event.type && SDLK_DOWN == event.key.keysym.sym)
			{
				pix->flag.back = false;
			}
		}
		if (pix->flag.straight)
			walk(pix, pix->dir, pix->moveSpeed);
		if (pix->flag.back)
			walk(pix, pix->dir, -pix->moveSpeed);

		game_process(pix);
		SDL_UpdateWindowSurface(pix->win);
	}

//	SDL_DestroyTexture(pix->image);
//	SDL_DestroyRenderer(pix->ren);
	SDL_FreeSurface(pix->surf);
	SDL_DestroyWindow(pix->win);
	SDL_Quit();
	return (0);
}
