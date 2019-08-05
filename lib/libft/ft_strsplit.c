/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:35:03 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/07 20:35:15 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**split_arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	k = ft_count_words(s, c);
	if (!(split_arr = (char **)malloc(sizeof(char *) * (k + 1))))
		return (NULL);
	split_arr[k] = NULL;
	while (j < k)
	{
		split_arr[j++] = ft_new_string(s, c, &i);
	}
	return (split_arr);
}
