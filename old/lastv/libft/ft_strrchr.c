/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:22:03 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/14 12:56:57 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *ch;

	ch = s;
	ch = ch + ft_strlen(s);
	while (*ch != (char)c && s != ch)
		ch--;
	if (*ch == (char)c)
		return ((char *)ch);
	else
		return (NULL);
}
