/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:32:16 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 11:01:57 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (s[i] != (unsigned char)c && i < n)
	{
		d[i] = s[i];
		i++;
	}
	if (s[i] == (unsigned char)c)
	{
		d[i] = s[i];
		i++;
		return (d + i);
	}
	else
		return (NULL);
}
