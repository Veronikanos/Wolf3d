/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 22:20:25 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/26 15:39:06 by vtlostiu         ###   ########.fr       */
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
	format.BitsPerPixel = (Uint8)(format.BytesPerPixel << 3u);
	format.Rmask = 0;
	format.Gmask = 0;
	format.Bmask = 0;
	format.Amask = 0;
	if ((pic_surf = IMG_Load(name_tex)) == false
		|| (convert = SDL_ConvertSurface(pic_surf, &format, 0)) == false)
	{
		ft_putstr(SDL_GetError());
		ft_putchar('\n');
		errors_handler(5, pix);
	}
	SDL_FreeSurface(pic_surf);
	return (convert);
}

static void				init_tex(t_pix *pix)
{
	size_t i;

	if (!(pix->tex_arr =
			(SDL_Surface **)malloc(sizeof(SDL_Surface *) * TEXTURES)))
		errors_handler(4, pix);
	i = UINT32_MAX;
	while (++i < TEXTURES)
		pix->tex_arr[i] = NULL;
	pix->tex_arr[0] = load_tex(pix, "textures/bricks.gif");
	pix->tex_arr[1] = load_tex(pix, "textures/bookshelf.gif");
	pix->tex_arr[2] = load_tex(pix, "textures/multibrick.gif");
	pix->tex_arr[3] = load_tex(pix, "textures/diamond.gif");
	pix->tex_arr[4] = load_tex(pix, "textures/hexgreen.gif");
	pix->tex_arr[5] = load_tex(pix, "textures/x.gif");
	pix->tex_arr[6] = load_tex(pix, "textures/y.gif");
	pix->tex_arr[7] = load_tex(pix, "textures/z.gif");
}

t_pix					*init(void)
{
	t_pix *pix;

	if (!(pix = (t_pix *)malloc(sizeof(t_pix))))
		errors_handler(4, NULL);
	ft_bzero(pix, sizeof(t_pix));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0
	|| !(pix->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		errors_handler(8, pix);
	pix->screen_surf = SDL_GetWindowSurface(pix->win);
	pix->screen = (Uint32 *)(pix->screen_surf->pixels);
	pix->player.dir = (t_vec2){ 1, 0 };
	pix->plane = (t_vec2){ 0, 0.66 };
	pix->game_over = true;
	pix->speed = 2;
	init_tex(pix);
	return (pix);
}
