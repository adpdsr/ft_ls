/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 10:20:35 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/11 14:00:51 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*add_unit(char *s, int size)
{
	if (size >= 1 && size <= 3)
		return (" B");
	else if (size >= 4 && size <= 6)
		return (" K");
	else if (size >= 7 && size <= 9)
		return (" M");
	else if (size >= 10 && size <= 13)
		return (" G");
	else
		return (" T");
}

static char	*add_dot(char *s, size_t size)
{
	size_t	toput;
	char	*tmp;

	tmp = ft_strnew(size + 1);
	toput = size % 3;
	((toput == 0)) ? toput = 3 : toput;
	ft_strncpy(tmp, s, toput);
	ft_strcat(tmp, ".");
	tmp[toput + 1] = s[toput];
	tmp[toput + 2] = s[toput + 1];
	return (tmp);
}

char	*format_size(char *s)
{
	size_t	size;
	char	*formated;
	char	*end;

	size = ft_strlen(s);
	formated = ft_strnew(size + 1);
	end = ft_strnew(2);
	end = add_unit(formated, size);
	if (size >= 4)
	{
		formated = add_dot(s, size);
		ft_strcat(formated, end);
		return (formated);
	}
	ft_strcpy(formated, s);
	ft_strcat(formated, end);
	return (formated);
}
