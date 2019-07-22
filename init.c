/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 22:20:25 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/22 19:40:52 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_pix	*init(t_pix *pix)
{
	if (!pix)
		return (NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		//atexit(SDL_Quit());
		errors_msg(8); //уточнить ошибки
	//ошибки
	pix->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

//	pix->ren = SDL_CreateRenderer(pix->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	pix->screen_surf = SDL_GetWindowSurface(pix->win); //
//	pix->screen_surf = IMG_Load("./image2.png");
	pix->screen = (int *)(pix->screen_surf->pixels);
//	pix->image = SDL_CreateTextureFromSurface(pix->ren, pix->screen_surf);
//	pix->image = IMG_LoadTexture(pix->ren,"./image2.png");

	pix->flag = (t_flag) { 0 };
	pix->player.dir = (t_vec2) { -1, 0 };
	pix->plane = (t_vec2) { 0, 0.66 };
	pix->width = 0;
	pix->height = 0;
	pix->side = 0;
	pix->running = 1;
	pix->texX = 0;
	pix->texNum = 0;
	pix->player.pos = (t_vec2){ 0 };
	pix->time = 0; // время текущего кадра
	pix->oldTime = 0; // время предыдущего кадра

	pix->wallX = 0;
	return (pix);
}
