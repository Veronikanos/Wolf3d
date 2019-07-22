/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:33:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/22 21:51:26 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*load_tex(t_pix *pix, char *name_tex)
{
	SDL_Surface			*pic_surf;
	SDL_Surface			*convert;
	SDL_PixelFormat		format;

	format.format = SDL_PIXELFORMAT_ARGB8888;
	format.palette = NULL;
	format.BytesPerPixel = sizeof(Uint32);
	format.BitsPerPixel = (Uint8)(format.BytesPerPixel * 8);
	format.Rmask = 0;
	format.Gmask = 0;
	format.Bmask = 0;
	format.Amask = 0;
	pic_surf = IMG_Load(name_tex);
	convert = SDL_ConvertSurface(pic_surf, &format, 0); //errors if no pic_surf or convert.
	SDL_FreeSurface(pic_surf);
	return(convert);
}

void	init_tex(t_pix *pix)
{
	pix->tex_arr = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * TEXTURES);
	pix->tex_arr[0] = load_tex(pix, "bricks.jpg");
	pix->tex_arr[1] = load_tex(pix, "bookshelf.gif");
	pix->tex_arr[2] = load_tex(pix, "multibrick.gif");
	pix->tex_arr[3] = load_tex(pix, "diamond.gif");
//	pix->tex_arr[4] = load_tex(pix, "diamond.gif");
//	pix->tex_arr[5] = load_tex(pix, "diamond.gif");
//	pix->tex_arr[6] = load_tex(pix, "diamond.gif");
//	pix->tex_arr[7] = load_tex(pix, "diamond.gif");
}

int				main(int argc, char **argv)
{
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
	parsing(pix, lines_head, &pix->player.pos);

	init_tex(pix);
	game_process(pix);
	close(pix->fd);
//	printf("%s\n", "okaaaay");
	if (pix->win == NULL)
		exit (8); //ошибки

//	SDL_Rect player_RECT;
//	player_RECT.x = WIDTH / 2;   //Смещение полотна по Х
//	player_RECT.y = HEIGHT;   //Смещение полотна по Y
//	player_RECT.w = WIDTH; //Ширина полотна
//	player_RECT.h = HEIGHT; //Высота полотна

//	SDL_RenderClear(pix->ren); //Очистка рендера
//	SDL_RenderCopy(pix->ren, pix->image, NULL, &player_RECT); //Копируем в рендер персонажа
//	SDL_RenderPresent(pix->ren); //Погнали!!

	while (pix->running)
	{			//время вывода и счетчик FPS
		pix->oldTime = pix->time;
		pix->time = SDL_GetTicks();
		pix->frameTime = (pix->time - pix->oldTime) / 1000.0; //frameTime - время, которое этот кадр занял, в секундах
//		print(1.0 / frameTime); //FPS counter
//		redraw();
//		cls();
//
//		 модификаторы скорости
		pix->player.move_rate = pix->frameTime * 2.0; //the constant value is in squares/second
		pix->player.rot_rate = pix->frameTime * 3.0; //the constant value is in radians/second
		event_handler(pix);
		game_process(pix);
		SDL_UpdateWindowSurface(pix->win);
		clear_screen(pix);
	}

//	SDL_DestroyTexture(pix->image);
//	SDL_DestroyRenderer(pix->ren);
	SDL_FreeSurface(pix->screen_surf);
	SDL_DestroyWindow(pix->win);
	SDL_Quit();
//
//	close(pix->fd);
//
//	printf("%s\n", "okaaaay");

	return (0);
}
