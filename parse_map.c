/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:48:16 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/04/25 18:40:58 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
//
//static int		atoi_letter_check(char c)
//{
//	if (c >= '0' && c <= '9')
//		return (c - '0');
//	else if (c >= 'a' && c <= 'f')
//		return (c - 'a' + 10);
//	else if (c >= 'A' && c <= 'F')
//		return (c - 'A' + 10);
//	return (0);
//}
//
//static int		ft_atoi_base_color(const char *str, size_t *i)
//{
//	int		res;
//
//	res = 0;
//	if (str[(*i)++] == ',' && str[(*i)++] == '0' && str[(*i)++] == 'x')
//	{
//		while (str[*i] != 32 && str[*i] != '\n' && str[*i] != '\0')
//		{
//			if (is_hex(str[*i]))
//				res = res * 16 + atoi_letter_check(str[*i]);
//			else
//				errors_msg(3);
//			(*i)++;
//		}
//	}
//	else
//		res = COLOR;
//	return (res);
//}

//static void		check_and_change(int *pix->map_val[y][x], t_lines *lines_head, int x, int y)
//{
//
//}

static int		check_player(int num, t_pix *pix)
{
	if (num == 9)
		pix->j > 0 ? num = 0 : pix->j++;
	return (num);
}

static int		check_frame(int num)
{
	if (num == 0 || num == 9)
		num = 1;
	return (num);
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

int				parsing(t_pix *pix, t_lines *lines_head)
{
	size_t	y;
	size_t	x;
	size_t	i;

	if (!(pix->map_val = (int **)malloc(pix->height * sizeof(int *))))
		errors_msg(4);
	y = UINT64_MAX;
	while (lines_head && ++y < pix->height)
	{
		if (!(pix->map_val[y] = (int *)malloc(pix->width * sizeof(int))))
			errors_msg(4);
		x = UINT64_MAX;
		i = 0;
		while (++x < pix->width)
		{
//			check_and_change(pix->map_val[y][x], lines_head, x, y);



			pix->map_val[y][x] = ft_atoi_i(lines_head->str, &i);
			if (x == 0 || y == 0 || x == pix->width - 1 || y == pix->height - 1)
				pix->map_val[y][x] = check_frame(pix->map_val[y][x]);
			else
			{
				pix->map_val[y][x] = check_player(pix->map_val[y][x], pix);
				if (pix->j == 0 && y == pix->height - 2 && x == pix->width - 2)
					pix->map_val[y][x] = 9;
			}
			printf("%d ", pix->map_val[y][x]);
		}
		lines_head = lines_head->next;
		printf("\n");
	}
	return (0);
}
