/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:33:33 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/25 16:21:30 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		show_menu(void)
{
	ft_putendl("\n\nControl:\n-> move - arrows, a, w, s, d.\n"
		"-> rotation - q, e, right arrow, left arrow.\n"
		"-> switch colors and textures (custom or compass) - HOME, END.\n"
		"-> run acceleration - RIGHT CTRL.\n");
}

void			time_and_rate(t_pix *pix)
{
	pix->old_time = pix->time;
	pix->time = SDL_GetTicks();
	pix->new_time = (pix->time - pix->old_time) / 1000.0;
	pix->player.move_rate = pix->new_time
			* pix->speed * (pix->flag.speed_up ? 2 : 1);
	pix->player.rot_rate = pix->new_time * 2;
}

int				main(int argc, char **argv)
{
	t_lines		*lines_head;
	t_pix		*pix;

	if (argc != 2)
		errors_handler(2, NULL);
	show_menu();
	lines_head = NULL;
	pix = init();
	is_file_valid(pix, &lines_head, argv);
	parsing(pix, lines_head, &pix->player.pos);
	if (pix->win == NULL)
		errors_handler(8, pix);
	while (pix->game_over)
	{
		game_process(pix);
		SDL_UpdateWindowSurface(pix->win);
		clear_screen(pix);
	}
	del_all(pix, UINT64_MAX);
	return (0);
}
