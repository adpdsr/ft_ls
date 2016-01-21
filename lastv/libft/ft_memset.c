/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:04:45 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 10:59:27 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	ch;
	unsigned char	*s;

	i = 0;
	ch = (unsigned char)c;
	s = (unsigned char *)b;
	while (i < len)
	{
		s[i] = ch;
		i++;
	}
	return (b);
}
