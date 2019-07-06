/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:55:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/04/25 20:54:43 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		errors_msg(int err)
{
	if (err == 2)
		ft_putendl("Usage: ./wolf3d input_file.fdf\n"
				"Incorrect number of arguments.\n");
	else if (err == 1)
		ft_putendl("Incorrect file or impossible to write file.\n");
	else if (err == 3)
		ft_putendl("Incorrect color.\n");
	else if (err == 4)
		ft_putendl("Impossible to allocate memory.\n");
	else if (err == 5)
		ft_putendl("There are no string to write from file.\n");
	else if (err == 6)
		ft_putendl("Invalid file or it is a directory.\n");
	exit(0);
	return (0);
}
