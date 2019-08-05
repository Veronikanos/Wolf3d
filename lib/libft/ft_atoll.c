/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:19:55 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/21 17:20:13 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long			ft_atoll(const char *str)
{
	long long	sign;
	long long	num;
	int			i;

	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\r')
	|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\n'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	num = 0;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
		num = (num * 10) + (long long)(str[i++] - '0');
	if (num > 9223372036854775807 && sign == 1)
		return (-1);
	if (num > 9223372036854775807 && sign == -1)
		return (0);
	return ((long long)(num * sign));
}
