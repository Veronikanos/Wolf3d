/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:45:31 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/03 17:45:43 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	symb;

	symb = (char)c;
	i = ft_strlen((char *)s);
	while (i != 0 && s[i] != symb)
		i--;
	if (s[i] == symb)
		return ((char *)&s[i]);
	return (NULL);
}
