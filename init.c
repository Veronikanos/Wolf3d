/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 22:20:25 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 22:22:21 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static SDL_Surface		*load_tex(t_pix *pix, char *name_tex)
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
	if ((pic_surf = IMG_Load(name_tex)) == false
		|| (convert = SDL_ConvertSurface(pic_surf, &format, 0)) == false) //errors if no pic_surf or convert.
	{
		ft_putstr(SDL_GetError());
		ft_putchar('\n');
		errors_handler(5, pix);
		//	return (NULL);
	}
	SDL_FreeSurface(pic_surf);
	return(convert);
}

static void	init_tex(t_pix *pix)
{
	pix->tex_arr = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * TEXTURES);
	pix->tex_arr[0] = load_tex(pix, "textures/bricks.gif");
	pix->tex_arr[1] = load_tex(pix, "textures/bookshelf.gif");
	pix->tex_arr[2] = load_tex(pix, "textures/multibrick.gif");
	pix->tex_arr[3] = load_tex(pix, "textures/diamond.gif");
	pix->tex_arr[4] = load_tex(pix, "textures/wood.jpg");
	pix->tex_arr[5] = load_tex(pix, "textures/hexgreen.gif");
	pix->tex_arr[6] = load_tex(pix, "textures/stones.jpg");
	pix->tex_arr[7] = load_tex(pix, "textures/red_brick.jpg");
}

t_pix	*init()
{
	t_pix *pix;

	if (!(pix = (t_pix *)malloc(sizeof(t_pix))))
		errors_handler(4, NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		//atexit(SDL_Quit());
		errors_handler(8, pix); //уточнить ошибки
	//ошибки
	pix->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
//	pix->ren = SDL_CreateRenderer(pix->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	pix->screen_surf = SDL_GetWindowSurface(pix->win); //
	pix->screen = (int *)(pix->screen_surf->pixels);
//	pix->image = SDL_CreateTextureFromSurface(pix->ren, pix->screen_surf);
//	pix->image = IMG_LoadTexture(pix->ren,"./image2.png");

	pix->flag = (t_flag){ 0 };
	pix->player.dir = (t_vec2){ 1, 0 };
	pix->plane = (t_vec2){ 0, 0.66 };
	pix->width = 0;
	pix->height = 0;
	pix->side = 0;
	pix->running = true;
	pix->tex_cord = (t_map){ 0 };
	pix->texNum = 0;
	pix->player.pos = (t_vec2){ 0 };
	pix->time = 0;
	pix->oldTime = 0;
	pix->wallX = 0;

//	pix->speed = 2;
	init_tex(pix);
	return (pix);
}
