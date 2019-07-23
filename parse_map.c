/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:48:16 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 21:33:27 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		fix_frame(int num)
{
	return ((num == 0 || num == 9) ? 1 : num);
}

static int		ft_atoi_i(const char *str, size_t *i)
{
	size_t		num;
	char		minus;

	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\r'
		|| str[*i] == '\n' || str[*i] == '\v' || str[*i] == '\f')
		(*i)++;
	num = 0;
	minus = 1;
	if (str[*i] == '-')
		minus = -1;
	while (str[*i] == '+' || str[*i] == '-')
		(*i)++;
	while (str[*i] && (str[*i] >= '0') && (str[*i] <= '9'))
	{
		num = (num * 10) + ((int)str[*i] - '0');
		(*i)++;
	}
	if ((num > 9223372036854775807 && minus == 1))
		return (-1);
	if (num > 9223372036854775807 && minus == -1)
		return (0);
	return ((int)(num * minus));
}

int				parsing(t_pix *pix, t_lines *lst, t_vec2 *pos)
{
	size_t	y;
	size_t	x;
	size_t	i;

	if (!(pix->map = (int **)malloc(pix->height * sizeof(int *))))
		errors_handler(4, pix);
	y = UINT64_MAX;
	while (lst && ++y < pix->height && !(i = 0) && (x = UINT64_MAX))
	{
		if (!(pix->map[y] = (int *)malloc(pix->width * sizeof(int))))
			errors_handler(4, pix);
		while (++x < pix->width)
		{
			pix->map[y][x] = ft_atoi_i(lst->str, &i);
			pix->map[y][x] > TEXTURES + 1 ? pix->map[y][x] = 1 : 0;
			if (x == 0 || y == 0 || x == pix->width - 1 || y == pix->height - 1)
				pix->map[y][x] = fix_frame(pix->map[y][x]);
			else if ((!pix->map[y][x] && (pos->x == 0 || pos->y == 0))
			|| (pix->map[y][x] == 9 && !(pix->map[y][x] = 0)))
				*pos = (t_vec2){ 0.5f + x, 0.5f + y };
//			printf("%d ", pix->map[y][x]);
		}
		lst = lst->next;
//		printf("\n");
	}
//	printf("player pos x = %f, y = %f ", pos->x, pos->y);
	(pos->x == 0 || pos->y == 0) ? errors_handler(3, pix) : 0;
	return (0);
}
