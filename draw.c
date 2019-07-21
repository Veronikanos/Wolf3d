/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:23:32 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/21 22:33:13 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		choose_color(t_pix *pix)
{
	int color;
	int texture;

	color = DEF_COL;
	if (pix->flag.tex_change == true)
	{
		texture = (pix->map[pix->map_cord.y][pix->map_cord.x]);
		if (texture == 1)
			color = RED;
		else if (texture == 2)
			color = GREEN;
		else if (texture == 3)
			color = BLUE;
		else if (texture == 4)
			color = YELLOW;
	}

		// дать разной яркости сторонам x и y
		//	color = color / 2;
	else
	{
		if (pix->side == 0 && pix->ray.rayDir.x < 0)
			color = PURPLE;
		if (pix->side == 0 && pix->ray.rayDir.x > 0)
			color = MAGENTA;
		if (pix->side == 1 && pix->ray.rayDir.y < 0)
			color = PINK;
		if (pix->side == 1 && pix->ray.rayDir.y > 0)
			color = CORAL;



	//		pix->texX = 64 - pix->texX - 1;
	}
	return (color);
}

void		clear_screen(t_pix *pix)
{
	size_t	y;
	size_t	x;

	y = UINT64_MAX;
	while (++y < HEIGHT && (x = UINT64_MAX))
		while (++x < WIDTH)
			pix->screen[y * WIDTH + x] = 0x0;
}

void	verLine(t_pix *pix, size_t x, int y, int _end, int color)
{
	int yy;

	yy = 0;
	while (yy < y)
	{
		pix->screen[yy * WIDTH + x] = CEIL_COL;
		yy++;
	}
	while (y < _end)
	{
		pix->screen[y * WIDTH + x] = color;
		y++;
	}
	while (y < HEIGHT)
	{
		pix->screen[y * WIDTH + x] = FLOOR_COL;
		y++;
	}
}
