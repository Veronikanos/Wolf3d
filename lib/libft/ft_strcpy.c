/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 18:45:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/02 18:45:50 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	int len;

	len = 0;
	while (src[len] != '\0')
		len++;
	len = len + 1;
	while (len--)
		dst[len] = src[len];
	return (dst);
}
