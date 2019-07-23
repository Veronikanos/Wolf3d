/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:23:32 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 17:07:22 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
		color = (pix->flag.tex_change) ? choose_tex(pix, y) : choose_color(pix);
		pix->screen[y * WIDTH + x] = color;
		y++;
	}
	while (y < HEIGHT)
	{
		pix->screen[y * WIDTH + x] = FLOOR_COL;
		y++;
	}
}
