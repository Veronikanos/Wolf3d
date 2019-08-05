/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:23:32 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/08/05 18:00:55 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			clear_screen(t_pix *pix)
{
	size_t	y;
	size_t	x;

	y = UINT64_MAX;
	while (++y < HEIGHT)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
			pix->screen[y * WIDTH + x] = 0x0;
	}
}

static void		draw_floor_and_ceiling(t_pix *pix, size_t y, size_t x)
{
	const double	weight = HEIGHT / (2.0 * y - HEIGHT) / pix->wall_dist;
	const t_vec2	pos = pix->player.pos;
	t_vec2			cur;
	t_xy			draw_tex;
	Uint32			color;

	cur = (t_vec2){ weight * pix->wall_side.x + (1.0 - weight) * pos.x,
					weight * pix->wall_side.y + (1.0 - weight) * pos.y };
	draw_tex = (t_xy){ (int)(cur.x * TEXWIDTH) % TEXWIDTH,
						(int)(cur.y * TEXHEIGHT) % TEXHEIGHT };
	color = (((Uint32 *)pix->tex_arr[4]->pixels)
			[TEXWIDTH * draw_tex.y + draw_tex.x]);
	(pix->flag.light_mode) && (color >>= 1u) && (color &= 8355711u);
	pix->screen[y * WIDTH + x] = pix->flag.color_mode ? color << 16u : color;
	color = (((Uint32 *)pix->tex_arr[3]->pixels)
			[TEXWIDTH * draw_tex.y + draw_tex.x]);
	(pix->flag.light_mode) && (color >>= 1u) && (color &= 8355711u);
	pix->screen[(HEIGHT - y) * WIDTH + x] =
		pix->flag.color_mode ? color << 16u : color;
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

void			draw_line(t_pix *pix, size_t x, t_xy from_to, Uint32 color)
{
	size_t start;
	size_t end;

	start = from_to.x - 1;
	end = from_to.y;
	which_side_of_wall(pix);
	while (++start < end)
	{
		color =
			pix->flag.tex_change ? choose_color(pix) : choose_tex(pix, start);
		(pix->flag.light_mode) && (color >>= 1u) && (color &= 8355711u);
		pix->screen[start * WIDTH + x] =
			(pix->flag.color_mode) ? color << 16u : color;
	}
	start = from_to.y - 1;
	while (++start < HEIGHT)
		if (pix->flag.tex_change)
		{
			pix->screen[start * WIDTH + x] = FLOOR_COL;
			pix->screen[(HEIGHT - start) * WIDTH + x] = CEIL_COL;
		}
		else
			draw_floor_and_ceiling(pix, start, x);
}
