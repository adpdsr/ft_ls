/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:41:51 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/14 10:46:17 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_array_size(char const *s, char c)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int		ft_word_len(char const *s, char c)
{
	int		len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		nb_word;
	char	**tab;

	i = 0;
	nb_word = ft_array_size(s, c);
	tab = (char **)malloc(sizeof(char *) * (ft_array_size(s, c)) + 1);
	if (tab == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s && *s == c)
			s++;
		tab[i] = ft_strsub((const char *)s, 0, ft_word_len(s, c));
		if (tab[i] == NULL)
			return (NULL);
		s = s + ft_word_len(s, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
