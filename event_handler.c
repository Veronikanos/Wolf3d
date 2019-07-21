/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 19:56:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/21 19:48:46 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		walk(t_pix *pix, t_vec2 dir, double moveSpeed)
{
	if (!(pix->map[(int) (pix->player.pos.y)]
	[(int) (pix->player.pos.x + dir.x * moveSpeed)]))
		pix->player.pos.x += dir.x * moveSpeed;
//	printf("%===\n\n");printf("%f \n\n",  dir.x * move_rate);
	if (!(pix->map[(int) (pix->player.pos.y + dir.y * moveSpeed)]
	[(int) (pix->player.pos.x)]))
		pix->player.pos.y += dir.y * moveSpeed;
//	printf("%f  %f\n\n", pix->player.pos.x, pix->player.pos.y);
}

static void		rotate(t_plr *player, t_vec2 *plane,
						t_vec2 dir, double rotSpeed)
{
	player->dir = (t_vec2){
		player->dir.x * cos(rotSpeed) - player->dir.y * sin(rotSpeed),
		player->dir.x * sin(rotSpeed) + player->dir.y * cos(rotSpeed) };
	*plane = (t_vec2){
		plane->x * cos(rotSpeed) - plane->y * sin(rotSpeed),
		plane->x * sin(rotSpeed) + plane->y * cos(rotSpeed) };
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
	}
	SDL_KEYUP == type && SDLK_HOME == key && --pix->flag.tex_change;
}

void			event_handler(t_pix *pix)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (SDL_QUIT == event.type
		|| (SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym))
			pix->running = 0;
		keyboard_events(pix, event.type, event.key.keysym.sym);
	}
	if (pix->flag.straight)
		walk(pix, pix->player.dir, pix->player.move_rate);
	if (pix->flag.back)
		walk(pix, pix->player.dir, -pix->player.move_rate);
	if (pix->flag.left)
		rotate(&pix->player, &pix->plane, pix->player.dir, pix->player.rot_rate);
	if (pix->flag.right)
		rotate(&pix->player, &pix->plane, pix->player.dir, pix->player.rot_rate * -1);
}