/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 20:53:15 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/02 20:53:32 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	len_dst;

	if (dstsize == 0)
		return (ft_strlen(src));
	len = 0;
	while (dst[len] && len < dstsize)
		len++;
	len_dst = len;
	while (src[len - len_dst] != '\0' && len < dstsize - 1)
	{
		dst[len] = src[len - len_dst];
		len++;
	}
	if (len_dst < dstsize)
		dst[len] = '\0';
	return (len_dst + ft_strlen(src));
}
