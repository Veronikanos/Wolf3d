/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 21:24:48 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/03 21:25:03 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	size_t	i;
	size_t	num;
	char	minus;

	i = ft_skip_whitespaces(str);
	num = 0;
	minus = 1;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		num = (num * 10) + ((int)str[i] - '0');
		i++;
	}
	if ((num > 9223372036854775807 && minus == 1))
		return (-1);
	if (num > 9223372036854775807 && minus == -1)
		return (0);
	return ((int)(num * minus));
}
