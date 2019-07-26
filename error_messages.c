/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:55:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/26 15:28:59 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		del_all(t_pix *pix, size_t i)
{
	if (!pix)
		return ;
	if (pix->tex_arr)
	{
		while (++i < TEXTURES && pix->tex_arr[i])
			SDL_FreeSurface(pix->tex_arr[i]);
		free(pix->tex_arr);
		pix->tex_arr = NULL;
	}
	if (pix->map && (i = UINT64_MAX))
	{
		while (++i < pix->height && pix->map[i])
			free(pix->map[i]);
		free(pix->map);
		pix->map = NULL;
	}
	if (pix->screen_surf)
	{
		SDL_FreeSurface(pix->screen_surf);
		pix->screen_surf = NULL;
		pix->screen = NULL;
	}
	if (pix->win)
		SDL_DestroyWindow(pix->win);
	SDL_Quit();
}

int			errors_handler(int err, t_pix *pix)
{
	if (err == 2)
		ft_putendl("Usage: ./wolf3d input_file.fdf\n"
	"Incorrect number of arguments.\n\n"
	"Control:\n-> move - arrows, a, w, s, d.\n"
	"-> rotation - q, e, right arrow, left arrow.\n"
	"-> switch colors and textures (custom or compass) - HOME, END\n"
	"-> run acceleration - RIGHT CTRL\n");
	else if (err == 1)
		ft_putendl("Incorrect file or impossible to write file.\n");
	else if (err == 3)
		ft_putendl("There are no space for player.\n");
	else if (err == 4)
		ft_putendl("Impossible to allocate memory.\n");
	else if (err == 5)
		ft_putendl("Impossible to load or convert texture.\n");
	else if (err == 6)
		ft_putendl("Invalid file or it is a directory.\n");
	else if (err == 7)
		ft_putendl("Program malfunction.\n");
	else if (err == 8)
		ft_putendl("Impossible to init SDL2 window.\n");
	del_all(pix, UINT64_MAX);
	exit(0);
	return (0);
}
