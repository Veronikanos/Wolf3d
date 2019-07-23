/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:33:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 22:22:21 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		time_and_rate(t_pix *pix)
{
	pix->oldTime = pix->time;
	pix->time = SDL_GetTicks();
	pix->frameTime = (pix->time - pix->oldTime) / 1000.0; //frameTime - время, которое этот кадр занял, в секундах
	pix->player.move_rate = pix->frameTime * SPEED; //the constant value
	// is in
	// squares/second
	pix->player.rot_rate = pix->frameTime * 4.2; //the constant value is in
	// radians/second
}

int				main(int argc, char **argv)
{
	t_lines		*lines_head;
	t_pix		*pix;

	if (argc != 2)
		errors_handler(2, NULL);
	lines_head = NULL;
	pix = init();
	is_file_valid(pix, &lines_head, argv);
	parsing(pix, lines_head, &pix->player.pos);
	if (pix->win == NULL)
		errors_handler (8, pix);
	while (pix->running)
	{
		game_process(pix);
		SDL_UpdateWindowSurface(pix->win);
		clear_screen(pix);
	}
	del_all(pix);
	return (0);
}
