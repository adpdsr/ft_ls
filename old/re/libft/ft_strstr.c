/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:03:08 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/14 10:50:34 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	if (s1[i] && s2[j])
	{
		while (s1[i])
		{
			while (s2[j] == s1[i + j])
			{
				if (s2[j + 1] == '\0')
					return ((char *)s1 + i);
				j++;
			}
			i++;
			j = 0;
		}
	}
	return (NULL);
}
