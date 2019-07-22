/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 21:47:16 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/22 22:07:59 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		count_dist_and_line_hight(t_pix *pix)
{
	double perpWallDist;

	if (pix->side == 0)
	{
		perpWallDist = (pix->ray_map_cord.x - pix->player.pos.x
			+ (1 - pix->step.x) / 2.0f) / pix->ray.dir.x;
		pix->wallX = pix->player.pos.y + perpWallDist * pix->ray.dir.y;
	}
	else
	{
		perpWallDist = (pix->ray_map_cord.y - pix->player.pos.y
			+ (1 - pix->step.y) / 2.0f) / pix->ray.dir.y;
		pix->wallX = pix->player.pos.x + perpWallDist * pix->ray.dir.x;

	}
	pix->wallX -= floor(pix->wallX);


	// вычисляем нижний и верхний пиксель для заполнения текущей полосы
	pix->lineHeight = (int)(HEIGHT / perpWallDist);
	pix->drawfromto.x = -pix->lineHeight / 2 + HEIGHT / 2;
	pix->drawfromto.y = pix->lineHeight / 2 + HEIGHT / 2;
	if (pix->drawfromto.x < 0)
		pix->drawfromto.x = 0;
	if (pix->drawfromto.y >= HEIGHT)
		pix->drawfromto.y = HEIGHT - 1;

	pix->texNum = pix->map[pix->ray_map_cord.y][pix->ray_map_cord.x] - 1;

	pix->texX = (int)(pix->wallX * TEXWIDTH);
	if (pix->side == 0 && pix->ray.dir.x > 0)
		pix->texX = TEXWIDTH - pix->texX - 1;
	if (pix->side == 1 && pix->ray.dir.y < 0)
		pix->texX = TEXWIDTH - pix->texX - 1;
}

static void		check_ray(t_pix *pix)
{
	bool 	hit;

	hit = false; //ударился ли луч о стену?
//	pix->side = 0; // ??? о какую стену был удар?
	//perform DDA
	while (hit == false)
	{
		// переход к следующему квадрату карты, ИЛИ в направлении x, ИЛИ в направлении y
		if (pix->ray.sideDist.x < pix->ray.sideDist.y)
		{
			pix->ray.sideDist.x += pix->ray.deltaDist.x;
			pix->ray_map_cord.x += pix->step.x;
			pix->side = 0;
		}
		else
		{
			pix->ray.sideDist.y += pix->ray.deltaDist.y;
			pix->ray_map_cord.y += pix->step.y;
			pix->side = 1;
		}
		//Проверка ударился ли луч о стену
		if (pix->map[pix->ray_map_cord.y][pix->ray_map_cord.x] > 0)
			hit = true;
	}
}

static void		count_raydirect(t_pix *pix, t_vec2 *pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		pix->step.x = -1;
		ray->sideDist.x = (pos->x - pix->ray_map_cord.x) * ray->deltaDist.x;
	}
	else
	{
		pix->step.x = 1;
		ray->sideDist.x = (pix->ray_map_cord.x + 1 - pos->x) * ray->deltaDist.x;
	}
	if (ray->dir.y < 0)
	{
		pix->step.y = -1;
		ray->sideDist.y = (pos->y - pix->ray_map_cord.y) * ray->deltaDist.y;
	}
	else
	{
		pix->step.y = 1;
		ray->sideDist.y = (pix->ray_map_cord.y + 1.0 - pos->y) * ray->deltaDist.y;
	}
}

void			game_process(t_pix *pix)
{
	size_t	x;
	int color;

	x = UINT64_MAX;
	while (++x < WIDTH)
	{
		// вычисляем положение и направление луча
		pix->cameraX = 2.0f * x / WIDTH - 1; // координата х в пространстве камеры
		pix->ray.dir = (t_vec2) { pix->player.dir.x + pix->plane.x
										* pix->cameraX, pix->ray.dir.y
										= pix->player.dir.y + pix->plane.y
										* pix->cameraX };
		pix->ray_map_cord = (t_map) { (int)pix->player.pos.x, (int)pix->player.pos.y };
		// длина луча от текущей позиции до следующей оси x или y
//		double pix->ray.sideDist.x;
//		double pix->ray.sideDist.y;
		// длина луча от одной стороны x или y до следующей стороны x или y
		pix->ray.deltaDist = (t_vec2) { fabs(1.0 / pix->ray.dir.x),
											pix->ray.deltaDist.y
											= fabs(1.0 / pix->ray.dir.y) };
		// в каком направлении нужно двигаться: в направлении x или y? (+1 или -1)
		count_raydirect(pix, &pix->player.pos, &pix->ray);
		check_ray(pix);
		count_dist_and_line_hight(pix);

	//	pix->texX = (int)(pix->wallX * 64.0); //здесь заменить на высоту текстуры и кастовать в double

		color = choose_color(pix);
		verLine(pix, x, pix->drawfromto.x, pix->drawfromto.y, color);
	}
}