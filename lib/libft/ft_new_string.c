/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:46:39 by vtlostiu          #+#    #+#             */
/*   Updated: 2018/11/14 17:47:00 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_new_string(char const *str, char c, int *i)
{
	int		j;
	int		len;
	char	*new_word;

	while (str[*i] && str[*i] == c)
		(*i)++;
	len = ft_word_length(str + *i, c);
	if (len > 0)
		new_word = ft_strnew(len);
	j = 0;
	while (str[*i] != c && str[*i] != '\0')
		new_word[j++] = str[(*i)++];
	return (new_word);
}
