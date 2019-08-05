/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:22:32 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/06 19:22:44 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	size = ft_strlen((char *)s);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (*s)
	{
		str[i++] = f(*s);
		s++;
	}
	str[i] = '\0';
	return (str);
}
