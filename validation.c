/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:23:34 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/23 21:33:27 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		is_valid_row(char const *buf)
{
	size_t i;

	if (!buf)
		errors_handler(7, NULL);
	i = 0;
	while (buf[i])
	{
		if (!(ft_isdigit(buf[i]) || buf[i] == ' '))
			errors_handler(1, NULL);
		if (buf[i])
			++i;
	}
	return (1);
}

void			is_file_valid(t_pix *pix, t_lines **lines_head, char **argv)
{
	char	*buf;
	int		fd;

	if ((fd = open(argv[1], O_RDONLY)) >= 0
	&& read(fd, NULL, 0))
		errors_handler(6, NULL);
	while (get_next_line(fd, &buf) == 1 && ++pix->height && is_valid_row(buf))
	{
		if (pix->width == 0)
		{
			if ((pix->width = ft_count_words(buf, 32)) < 3)
				errors_handler(1, NULL);
			ft_add_to_end(lines_head, buf);
		}
		else
		{
			if (pix->width != ft_count_words(buf, 32) && ft_del_all(lines_head))
				errors_handler(1, NULL);
			else
				ft_add_to_end(lines_head, buf);
		}
		ft_memdel((void *)&buf);
	}
	close(fd);
	pix->height < 3 ? errors_handler(1, NULL) : 0;
}
