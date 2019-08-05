/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 16:11:29 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/02 16:13:55 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	symb;
	size_t			i;

	str = (unsigned char *)s;
	symb = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == symb)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
