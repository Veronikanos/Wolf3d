/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:23:32 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/26 16:28:33 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			clear_screen(t_pix *pix)
{
	size_t	y;
	size_t	x;

	y = UINT64_MAX;
	while (++y < HEIGHT && (x = UINT64_MAX))
		while (++x < WIDTH)
			pix->screen[y * WIDTH + x] = 0x0;
}

static void		which_side_of_wall(t_pix *pix)
{
	if (pix->edge == 0 && pix->ray.dir.x > 0)
		pix->wall_side = (t_vec2){ pix->ray_map_cord.x,
								   pix->ray_map_cord.y + pix->wall_x };
	else if (pix->edge == 0 && pix->ray.dir.x < 0)
		pix->wall_side = (t_vec2){ pix->ray_map_cord.x + 1.0,
								   pix->ray_map_cord.y + pix->wall_x };
	else if (pix->edge == 1 && pix->ray.dir.y > 0)
		pix->wall_side = (t_vec2){ pix->ray_map_cord.x + pix->wall_x,
								   pix->ray_map_cord.y };
	else if (pix->edge == 1 && pix->ray.dir.y < 0)
		pix->wall_side = (t_vec2){ pix->ray_map_cord.x + pix->wall_x,
								   pix->ray_map_cord.y + 1.0 };
}

void			draw_line(t_pix *pix, size_t x, t_map from_to, int color)
{
	int yy;
	int y;
	int end;

	double currentDist;
	double distPlayer;
	double distWall;
	distWall = pix->wall_dist;
	distPlayer = 0.0;
	y   = from_to.x;
	end = from_to.y;
	yy  = 0;
	which_side_of_wall(pix);
//	while (yy < y)
//	{
//		pix->screen[yy * WIDTH + x] = CEIL_COL;
//		yy++;
//	}
	while (y < end)
	{
		color = (pix->flag.tex_change) ? choose_tex(pix, y) : choose_color(pix);
		pix->screen[y * WIDTH + x] = color;
		y++;
	}
	y = from_to.y;
//	end = from_to.y;
	while (y < HEIGHT)
	{

//		pix->screen[y * WIDTH + x] = FLOOR_COL;
		currentDist = HEIGHT / (2.0 * y - HEIGHT);

		double weight = (currentDist - distPlayer) / (distWall - distPlayer);

		double currentFloorX =
				weight * pix->wall_side.x + (1.0 - weight) * pix->player.pos.x;
		double currentFloorY =
				weight * pix->wall_side.y + (1.0 - weight) * pix->player.pos.y;

		int floorTexX;
		int floorTexY;
		floorTexX = (int)(currentFloorX * TEXWIDTH) % TEXWIDTH;
		floorTexY = (int)(currentFloorY * TEXHEIGHT) % TEXHEIGHT;

		pix->screen[y * WIDTH + x] =
				((((Uint32 *)pix->tex_arr[2]->pixels)
				[TEXWIDTH * floorTexY + floorTexX] >> 1u) & 8355711u);
		pix->screen[(HEIGHT - y) * WIDTH + x] =
				(((Uint32 *)pix->tex_arr[3]->pixels)
				[TEXWIDTH * floorTexY + floorTexX]);
		y++;
	}
}
