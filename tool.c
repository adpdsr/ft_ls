/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:54:47 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 13:52:11 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*add_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char	*remove_slash(char *path)
{
	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

void	ft_putstr_s(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	ft_putstr(" ");
}

void	ft_putnbr_endl(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n *= -1;
		}
		if (n >= 10)
			ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	write(1, "\n", 1);
}

int		is_what(char *tab)
{
	DIR			*dir;
	struct stat	st;

	if ((dir = opendir(tab)))
	{
		closedir(dir);
		return (1);
	}
	else if (!stat(tab, &st))
		return (0);
	else
		return (-1);
}

char	*get_path(char *path)
{
	int		i;
	int		j;
	int 	end;
	char	*new;

	j = 0;
	path = remove_slash(path);
	i = ft_strlen(path);
	end = i;
	while (i > 0 && path[i - 1] != '/')
		i--;
	new = ft_strnew(end - i + 1);
	while (path[i])
	{
		new[j] = path[i];
		i++;
		j++;
	}
	return (new);
}
