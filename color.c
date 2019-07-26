/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:10:07 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/26 15:42:31 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		which_col(int texture)
{
	int color;

	color = DEF_COL;
	if (texture == 1)
		color = RED;
	else if (texture == 2)
		color = GREEN;
	else if (texture == 3)
		color = BLUE;
	else if (texture == 4)
		color = YELLOW;
	return (color);
}

int				choose_color(t_pix *pix)
{
	int color;
	int texture;

	color = DEF_COL;
	if (pix->flag.tex_compass == true)
	{
		texture = (pix->map[pix->ray_map_cord.y][pix->ray_map_cord.x]);
		color = which_col(texture);
	}
	else
	{
		if (pix->edge == 0 && pix->ray.dir.x < 0)
			color = BLUE;
		if (pix->edge == 0 && pix->ray.dir.x > 0)
			color = YELLOW;
		if (pix->edge == 1 && pix->ray.dir.y < 0)
			color = PINK;
		if (pix->edge == 1 && pix->ray.dir.y > 0)
			color = GREEN;
	}
	return (color);
}

int				choose_tex(t_pix *pix, int y)
{
	int color;

	pix->d =
		((Uint32)y << 8u) - (HEIGHT << 7u) + ((Uint32)(HEIGHT / pix->wall_dist) << 7u);
	pix->tex_cord.y = (Uint32)((pix->d * TEXHEIGHT) / (HEIGHT / pix->wall_dist)) >> 8u;
	if (pix->flag.tex_compass == false)
	{
		if (pix->edge == 0 && pix->ray.dir.x < 0)
			pix->tex_id = 2;
		if (pix->edge == 0 && pix->ray.dir.x > 0)
			pix->tex_id = 3;
		if (pix->edge == 1 && pix->ray.dir.y < 0)
			pix->tex_id = 0;
		if (pix->edge == 1 && pix->ray.dir.y > 0)
			pix->tex_id = 1;
	}
	color = ((int *)(pix->tex_arr[pix->tex_id]->pixels))
	[TEXWIDTH * pix->tex_cord.y + pix->tex_cord.x];
	return (color);
}
