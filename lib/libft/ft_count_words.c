/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:44:49 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/14 17:45:26 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *str, char c)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] != c && str[i + 1] == c)
		|| (str[i] != c && str[i + 1] == '\0'))
			j++;
	}
	return (j);
}
