/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 17:06:08 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 17:06:11 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(char *str, char c)
{
	int i;

	if (str && c)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		return (ft_strndup(str, i));
	}
	return (NULL);
}
