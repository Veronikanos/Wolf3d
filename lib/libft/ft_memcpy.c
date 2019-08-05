/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 21:14:42 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/10/31 18:14:37 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*a;
	char		*b;

	a = (const char *)src;
	b = (char *)dst;
	while (n--)
		*b++ = *a++;
	return (dst);
}
