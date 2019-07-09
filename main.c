/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:33:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/04 21:40:33 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


static t_pix	*init(t_pix *pix)
{
	if (!pix)
		return (NULL);
	pix->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
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
//	SDL_Event event;


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
	parsing(pix, lines_head);
	//write_tex(int **map_val);
	close(pix->fd);

	printf("%s\n", "okaaaay");
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//		//atexit(SDL_Quit());
//		return(1);
//		//ошибки


//	if (pix->win == NULL)
//		exit (1); //ошибки
//
//	SDL_Rect player_RECT;
//	player_RECT.x = WIDTH / 2;   //Смещение полотна по Х
//	player_RECT.y = HEIGHT;   //Смещение полотна по Y
//	player_RECT.w = WIDTH; //Ширина полотна
//	player_RECT.h = HEIGHT; //Высота полотна
//
//	SDL_Renderer *ren = SDL_CreateRenderer(pix->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	SDL_Texture *image = IMG_LoadTexture(ren,"./image2.png");;
//
//	SDL_RenderClear(ren); //Очистка рендера
//	SDL_RenderCopy(ren, image, NULL, &player_RECT); //Копируем в рендер персонажа
//	SDL_RenderPresent(ren); //Погнали!!
//
//	while (running)
//		while(SDL_PollEvent(&event))
//			if((SDL_QUIT == event.type)
//			|| (SDL_KEYDOWN == event.type
//				&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
//				running = 0;
//
//
//	SDL_DestroyWindow(pix->win);
//	SDL_Quit();
	return (0);
}
