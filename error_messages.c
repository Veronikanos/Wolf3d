/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:55:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 22:11:21 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			del_all(t_pix *pix)
{
	size_t i;

	i = UINT64_MAX;
	while (i++ < TEXTURES)
		SDL_FreeSurface(pix->tex_arr[i]);
	//	SDL_DestroyTexture(pix->image);
//	SDL_DestroyRenderer(pix->ren);
	SDL_FreeSurface(pix->screen_surf);
	SDL_DestroyWindow(pix->win);
	SDL_Quit();
}

int		errors_handler(int err, t_pix *pix)
{
	if (err == 2)
		ft_putendl("Usage: ./wolf3d input_file.fdf\n"
				"Incorrect number of arguments.\n\n"
	"Control:\n-> move and rotate - arrows,\n"
 "-> switch colors and textures (custom or compass) - HOME, END\n");
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

	if (pix)
		del_all(pix);
	exit(0);
	return (0);
}
