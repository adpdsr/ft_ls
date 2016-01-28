/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:55:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 11:10:34 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *ch1;
	unsigned char *ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	while (*ch1 && *ch1 == *ch2)
	{
		ch1++;
		ch2++;
	}
	return (*ch1 - *ch2);
}
