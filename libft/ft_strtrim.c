/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:03:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/09 15:18:09 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int start;
	int end;
	int len;

	start = 0;
	end = 0;
	len = ft_strlen(s);
	while (ft_isspace(s[start]))
		start++;
	while (ft_isspace(s[len - end - 1]))
		end++;
	if ((len - start - end) <= 0)
		return (ft_strnew(0));
	else
		return (ft_strsub(s, start, (size_t)(len - start - end)));
}
