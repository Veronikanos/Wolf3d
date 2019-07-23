/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:10:07 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 21:15:55 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		choose_color(t_pix *pix)
{
	int color;
	int texture;

	color = DEF_COL;
	if (pix->flag.tex_compas == true)
	{
		texture = (pix->map[pix->ray_map_cord.y][pix->ray_map_cord.x]);
		if (texture == 1)
			color = RED;
		else if (texture == 2)
			color = GREEN;
		else if (texture == 3)
			color = BLUE;
		else if (texture == 4)
			color = YELLOW;
	}
	else
	{
		if (pix->side == 0 && pix->ray.dir.x < 0)
			color = BLUE;
		if (pix->side == 0 && pix->ray.dir.x > 0)
			color = YELLOW;
		if (pix->side == 1 && pix->ray.dir.y < 0)
			color = PINK;
		if (pix->side == 1 && pix->ray.dir.y > 0)
			color = GREEN;
	}
	return (color);
}

int		choose_tex(t_pix *pix, int y)
{
	int color;

	pix->d = y * 256 - HEIGHT * 128 + pix->lineHeight * 128;
	pix->tex_cord.y = ((pix->d * TEXHEIGHT) / pix->lineHeight) / 256;
	if (pix->flag.tex_compas == true)
	{
		if (pix->side == 0 && pix->ray.dir.x < 0)
			pix->texNum = 0;
		if (pix->side == 0 && pix->ray.dir.x > 0)
			pix->texNum = 1;
		if (pix->side == 1 && pix->ray.dir.y < 0)
			pix->texNum = 2;
		if (pix->side == 1 && pix->ray.dir.y > 0)
			pix->texNum = 3;
	}
	color = ((int *)(pix->tex_arr[pix->texNum]->pixels))
	[TEXWIDTH * pix->tex_cord.y + pix->tex_cord.x];
	return (color);
}
