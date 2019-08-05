/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:45:51 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/14 17:46:17 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_length(char const *str, char c)
{
	int i;

	i = 0;
	if (str[i] == c)
		return (0);
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	return (i);
}
