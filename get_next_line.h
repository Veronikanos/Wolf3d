/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:03:54 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/04/25 18:34:35 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 100

typedef struct	s_struct
{
	char			*head;
	int				fd;
	struct s_struct	*next;
}				t_struct;

int				get_next_line(const int fd, char **line);

#endif
