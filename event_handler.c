/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 19:56:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 22:23:24 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		walk(t_pix *pix, t_vec2 dir, double moveSpeed)
{
	unsigned int pos_x;
	unsigned int pos_y;

	pos_y = (unsigned int)(pix->player.pos.y);
	pos_x = (unsigned int)(pix->player.pos.x + dir.x * moveSpeed * DIST);
	if (pos_x < pix->width && pos_y < pix->height && !(pix->map[pos_y][pos_x]))
		pix->player.pos.x += dir.x * moveSpeed;
	pos_y = (unsigned int)(pix->player.pos.y + dir.y * moveSpeed * DIST);
	pos_x = (unsigned int)(pix->player.pos.x);
	if (pos_x < pix->width && pos_y < pix->height && !(pix->map[pos_y][pos_x]))
		pix->player.pos.y += dir.y * moveSpeed;
}

static void		rotate(t_plr *player, t_vec2 *plane, double rot_rate)
{
	player->dir = (t_vec2){
		player->dir.x * cos(rot_rate) - player->dir.y * sin(rot_rate),
		player->dir.x * sin(rot_rate) + player->dir.y * cos(rot_rate) };
	*plane = (t_vec2){
		plane->x * cos(rot_rate) - plane->y * sin(rot_rate),
		plane->x * sin(rot_rate) + plane->y * cos(rot_rate) };
}

void			keyboard_events(t_pix *pix, Uint32 type, SDL_Keycode key)
{
	bool val;

	if ((SDL_KEYDOWN == type && (val = true))
	|| (SDL_KEYUP == type && !(val = false)))
	{
		if (SDLK_UP == key)
			pix->flag.straight = val;
		if (SDLK_DOWN == key)
			pix->flag.back = val;
		if (SDLK_RIGHT == key)
			pix->flag.right = val;
		if (SDLK_LEFT == key)
			pix->flag.left = val;
//		if (SDLK_KP_ENTER == key)
//		{
//			pix->flag.speed = val;
//			pix->speed += 5;
//		}
	}
	SDL_KEYUP == type && SDLK_HOME == key && --pix->flag.tex_compas;
	SDL_KEYUP == type && SDLK_END == key && --pix->flag.tex_change;
}

void			event_handler(t_pix *pix)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (SDL_QUIT == event.type
		|| (SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym))
			pix->running = false;
		keyboard_events(pix, event.type, event.key.keysym.sym);
	}
	if (pix->flag.straight)
		walk(pix, pix->player.dir, pix->player.move_rate);
	if (pix->flag.back)
		walk(pix, pix->player.dir, -pix->player.move_rate);
	if (pix->flag.right)
		rotate(&pix->player, &pix->plane, pix->player.rot_rate);
	if (pix->flag.left)
		rotate(&pix->player, &pix->plane, pix->player.rot_rate * -1);
}