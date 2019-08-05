/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 21:18:34 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/01 21:20:02 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*a;
	char		*b;
	size_t		i;

	i = 0;
	a = (const char *)src;
	b = (char *)dst;
	if (a < b)
		while (len--)
			b[len] = a[len];
	else
		while (i < len)
		{
			b[i] = a[i];
			i++;
		}
	return (dst);
}
