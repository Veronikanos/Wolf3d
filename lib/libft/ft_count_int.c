/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:53:36 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/14 17:53:39 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t			ft_count_int(long long int num)
{
	size_t		i;

	i = 1;
	if (num < 0)
		i++;
	while (i && (num /= 10))
		i++;
	return (i);
}
