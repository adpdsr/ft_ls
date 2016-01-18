/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:29:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 11:10:37 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *ch1;
	unsigned char *ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	while (*ch1 != '\0' && *ch1 == *ch2 && n > 0)
	{
		ch1++;
		ch2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*ch1 - *ch2);
}
