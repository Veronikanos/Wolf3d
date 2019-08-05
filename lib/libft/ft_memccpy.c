/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:17:09 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/01 20:00:51 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		b[i] = a[i];
		if (b[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
