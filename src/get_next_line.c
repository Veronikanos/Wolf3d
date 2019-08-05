/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:37:58 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/01/25 17:38:29 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_struct	*check_fd(int fd, t_struct **symbols)
{
	t_struct		*curr;
	t_struct		*prev;

	if (!*symbols)
	{
		*symbols = ft_memalloc(sizeof(t_struct));
		(*symbols)->fd = fd;
		return (*symbols);
	}
	curr = *symbols;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		prev = curr;
		curr = curr->next;
	}
	prev->next = ft_memalloc(sizeof(t_struct));
	prev->next->fd = fd;
	return (prev->next);
}

int			work_with_stat(char **symbols, char **line, char *n)
{
	int		len;
	char	*tmp;

	if (!symbols || !*symbols || !**symbols)
		return (0);
	if (n)
	{
		len = n - *symbols;
		*line = ft_strsub(*symbols, 0, len);
		tmp = ft_strsub(*symbols, len + 1, ft_strlen(*symbols));
		free(*symbols);
		(*symbols) = tmp;
	}
	else
	{
		*line = ft_strdup(*symbols);
		ft_strdel(symbols);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_struct *symbols = NULL;
	t_struct		*p;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				res;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	p = check_fd(fd, &symbols);
	if (p->head && (tmp = ft_strchr(p->head, '\n')))
		return (work_with_stat(&p->head, line, tmp));
	while (((res = read(fd, buf, BUFF_SIZE)) > 0) && !(buf[res] *= '\0'))
	{
		if (!p->head)
			p->head = ft_strdup(buf);
		else
		{
			tmp = p->head;
			p->head = ft_strjoin(tmp, buf);
			ft_strdel(&tmp);
		}
		if ((tmp = ft_strchr(p->head, '\n')))
			break ;
	}
	return (work_with_stat(&p->head, line, tmp));
}
