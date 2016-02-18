/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:01:13 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 11:25:31 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;

	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str != NULL)
	{
		ft_strcat(str, s1);
		ft_strcat(str, s2);
	}
	return (str);
}
