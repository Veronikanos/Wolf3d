/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 18:21:34 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/02 18:21:53 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		i;
	int		len;

	len = 0;
	while (s1[len] != '\0')
		len++;
	new = (char *)malloc(sizeof(*new) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
