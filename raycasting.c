/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 21:47:16 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/25 20:48:39 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			find_start(t_pix *pix, double wall_dist, double wall_x)
{
	pix->lineHeight = (Uint32)(HEIGHT / wall_dist);
	pix->from_to.x = -(pix->lineHeight >> 1u) + HEIGHT_H;
	pix->from_to.y = (pix->lineHeight >> 1u) + HEIGHT_H;
	if (pix->from_to.x < 0)
		pix->from_to.x = 0;
	if (pix->from_to.y >= HEIGHT)
		pix->from_to.y = HEIGHT - 1;
	pix->tex_id = pix->map[pix->ray_map_cord.y][pix->ray_map_cord.x] - 1;
	pix->tex_cord.x = (int)(wall_x * TEXWIDTH);
	if ((pix->edge == 0 && pix->ray.dir.x > 0)
	|| (pix->edge == 1 && pix->ray.dir.y < 0))
		pix->tex_cord.x = TEXWIDTH - pix->tex_cord.x - 1;
}

static void		count_dist(t_pix *pix)
{
	double wall_dist;
	double wall_x;

	if (pix->edge == 0)
	{
		wall_dist = (pix->ray_map_cord.x - pix->player.pos.x
			+ ((1u - pix->step.x) >> 1u)) / pix->ray.dir.x;
		wall_x = pix->player.pos.y + wall_dist * pix->ray.dir.y;
	}
	else
	{
		wall_dist = (pix->ray_map_cord.y - pix->player.pos.y
			+ ((1u - pix->step.y) >> 1u)) / pix->ray.dir.y;
		wall_x = pix->player.pos.x + wall_dist * pix->ray.dir.x;
	}
	wall_x -= floor(wall_x);

	pix->wall_x = wall_x; //
	pix->wall_dist = wall_dist; //

	find_start(pix, pix->wall_dist, pix->wall_x); //
//	find_start(pix, wall_dist, wall_x);
}

static void		check_ray(t_pix *pix)
{
	bool hit;

	hit = false;
	while (hit == false)
	{
		if (pix->ray.side_dist.x < pix->ray.side_dist.y)
		{
			pix->ray.side_dist.x += pix->ray.diff_dist.x;
			pix->ray_map_cord.x += pix->step.x;
			pix->edge = 0;
		}
		else
		{
			pix->ray.side_dist.y += pix->ray.diff_dist.y;
			pix->ray_map_cord.y += pix->step.y;
			pix->edge = 1;
		}
		if (pix->map[pix->ray_map_cord.y][pix->ray_map_cord.x] > 0)
			hit = true;
	}
}

static void		count_raydirect(t_pix *pix, t_vec2 *pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		pix->step.x = -1;
		ray->side_dist.x = (pos->x - pix->ray_map_cord.x) * ray->diff_dist.x;
	}
	else
	{
		pix->step.x = 1;
		ray->side_dist.x = (pix->ray_map_cord.x + 1 - pos->x)
				* ray->diff_dist.x;
	}
	if (ray->dir.y < 0)
	{
		pix->step.y = -1;
		ray->side_dist.y = (pos->y - pix->ray_map_cord.y) * ray->diff_dist.y;
	}
	else
	{
		pix->step.y = 1;
		ray->side_dist.y = (pix->ray_map_cord.y + 1.0 - pos->y)
				* ray->diff_dist.y;
	}
}

void			game_process(t_pix *pix)
{
	size_t	i;
	double	x;

	time_and_rate(pix);
	event_handler(pix);
	i = UINT64_MAX;
	while (++i < WIDTH)
	{
		x = 2.0f * i / WIDTH - 1;
		pix->ray.dir = (t_vec2){
			pix->player.dir.x + pix->plane.x * x,
			(pix->ray.dir.y = pix->player.dir.y + pix->plane.y * x)
		};
		pix->ray_map_cord = (t_map){ (int)pix->player.pos.x,
									(int)pix->player.pos.y
		};
		pix->ray.diff_dist = (t_vec2){
			fabs(1.0 / pix->ray.dir.x),
			pix->ray.diff_dist.y = fabs(1.0 / pix->ray.dir.y)
		};
		count_raydirect(pix, &pix->player.pos, &pix->ray);
		check_ray(pix);
		count_dist(pix);
		draw_line(pix, i, pix->from_to, choose_color(pix));
	}
}
