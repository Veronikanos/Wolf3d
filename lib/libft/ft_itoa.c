/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:39:59 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/08 19:40:11 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			*ft_itoa(int n)
{
	size_t			count;
	char			*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_count_int(n);
	if (!(str = ft_strnew(count)))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0 && (str[--count] = (char)('0' + n % 10)))
		n /= 10;
	return (str);
}
