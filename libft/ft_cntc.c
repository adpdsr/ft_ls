/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 17:05:34 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 17:05:37 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cntc(char *str, char c)
{
	int i;
	int cnt;

	if (str && c)
	{
		i = 0;
		cnt = 0;
		while (str[i])
		{
			if (str[i] == c)
				cnt++;
			i++;
		}
		return (cnt);
	}
	return (0);
}