/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:23:32 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/22 20:14:51 by vtlostiu         ###   ########.fr       */
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

		// дать разной яркости сторонам x и y
		//	color = color / 2;
	else
	{
		if (pix->side == 0 && pix->ray.dir.x < 0)
			color = PURPLE;
		if (pix->side == 0 && pix->ray.dir.x > 0)
			color = MAGENTA;
		if (pix->side == 1 && pix->ray.dir.y < 0)
			color = PINK;
		if (pix->side == 1 && pix->ray.dir.y > 0)
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
//	{
//		pix->screen[y * WIDTH + x] = color;
//		y++;
//	}
	{
		pix->d = y * 256 - HEIGHT * 128 + pix->lineHeight * 128;
		pix->texY = ((pix->d * TEXHEIGHT) / pix->lineHeight) / 256;

		color = ((int *)(pix->tex_arr[pix->texNum]->pixels))
				[TEXWIDTH * pix->texY + pix->texX];
		pix->screen[y * WIDTH + x] = color;
		y++;
	}
	while (y < HEIGHT)
	{
		pix->screen[y * WIDTH + x] = FLOOR_COL;
		y++;
	}
}
