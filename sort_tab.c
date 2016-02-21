/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:40:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/21 17:51:41 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	tab_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static int	is_what(char *tab)
{
	DIR *dir;
	struct stat st;

	if ((dir = opendir(tab)))
	{
		closedir(dir);
		return (1); // is dir
	}
	else if (!stat(tab, &st))
		return (0); // is file
	else
		return (-1); // is none
}

static void		sort_tab(char **tab, t_opt *opt, int flag)
{
	int i;

	i = 0;
	if (flag > 0)
		i += flag;
	while (tab[i + 1] != NULL)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0 && opt->r == 0)
		{
			tab_swap(tab + i, tab + i + 1);
			sort_tab(tab, opt, flag);
		}
		else if (ft_strcmp(tab[i], tab[i + 1]) < 0 && opt->r == 1)
		{
			tab_swap(tab + i, tab + i + 1);
			sort_tab(tab, opt, flag);
		}
		i++;
	}
}

char	**create_tab(char **av, t_opt *opt, int ac, int flag)
{
	int i;
	int j;
	char **tab;

	i = flag;
	j = 0;
	sort_tab(av, opt, flag);
	if (!(tab = (char **)malloc(sizeof(char *) * ac + 1)))
		return (NULL);
	while (i < ac)
	{
		if (is_what(av[i]) == -1)
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	i = flag;
	while (i < ac)
	{
		if (is_what(av[i]) == 0)
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	i = flag;
	while (i < ac)
	{
		if (is_what(av[i]) == 1)
		{
			tab[j] = ft_strdup(av[i]);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
