/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 15:01:27 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/11 15:53:38 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = ft_strnew(ft_strlen(s1) + (ft_strlen(s2) * len) + 1);
	if (str)
	{
		ft_strcat(str, s1);
		while (i < len)
		{
			ft_strcat(str, s2);
			i++;
		}
	}
	return (str);
}
