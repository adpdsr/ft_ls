/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 10:20:35 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/22 13:05:31 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*add_unit(int size)
{
	if (size >= 1 && size <= 3)
		return (" B");
	else if (size >= 4 && size <= 6)
		return (" K");
	else if (size >= 7 && size <= 9)
		return (" M");
	else if (size >= 10 && size <= 12)
		return (" G");
	else
		return (" T");
}

static char	*add_dot(char *s, size_t size)
{
	size_t	toput;
	char	*tmp;

	toput = size % 3;
	((toput == 0)) ? toput = 3 : toput;
	printf("s = %s\n", s);
	printf("malloc = %zu\n", toput + 6);
	tmp = ft_strnew(toput + 4);
	//if (!(tmp = (char *)malloc(sizeof(char) * toput + 5)))
	//	return (NULL);
	tmp = ft_strnew(toput + 7);
	ft_strncpy(tmp, s, toput);
	ft_strcat(tmp, ".");
	if (s[toput] && s[toput + 1] && s[toput + 2])
	{
		tmp[toput + 1] = s[toput];
		tmp[toput + 2] = s[toput + 1];
		tmp[toput + 3] = '\0';
	}
	return (tmp);
}

char	*format_size(char *s)
{
	size_t	size;
	char	*formated;
	char	*end;

	size = ft_strlen(s);
	if (size == 1 && (!ft_atoi(s)))
	{
		free(s);
		s = NULL;
		return (ft_strdup("0 B"));
	}
	formated = ft_strnew(size); // ??
	end = ft_strdup(add_unit(size));
	if (size >= 4)
	{
		formated = add_dot(s, size);
		free(s);
		s = NULL;
		ft_strcat(formated, end);
		free(end);
		end = NULL;
		return (formated);
	}
	else
		return (ft_strjoin(s, end));
	ft_strjoin(formated, s);
	free(s);
	s = NULL;
	ft_strjoin(formated, end);
	free(end);
	end = NULL;
	return (formated);
}

void	put_total(t_lst *lst, int hidd)
{
	int res;

	res = 0;
	if (hidd)
	{
		while (lst)
		{
			res += lst->blok;
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			if (ft_strncmp(lst->name, ".", 1) != 0)
				res += lst->blok;
			lst = lst->next;
		}
	}
	ft_putstr("total ");
	ft_putnbr_endl(res);
}
