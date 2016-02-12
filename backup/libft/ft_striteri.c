/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:01:03 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 11:17:50 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int i;
	unsigned int len;

	i = 0;
	len = (unsigned int)ft_strlen(s);
	if (s != NULL && f != NULL)
	{
		while (i < len)
		{
			f(i, s + i);
			i++;
		}
	}
}
