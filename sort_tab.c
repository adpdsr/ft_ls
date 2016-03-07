/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:40:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/07 18:25:27 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		sort_tab_ascii(char **tab, t_opt *opt, int flag)
{
	int i;

	i = 0;
	if (flag > 0)
		i += flag;
	while (tab[i + 1] != NULL)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0 && opt->r == 0)
		{
			ft_tabswap(tab + i, tab + i + 1);
			sort_tab_ascii(tab, opt, flag);
		}
		else if (ft_strcmp(tab[i], tab[i + 1]) < 0 && opt->r == 1)
		{
			ft_tabswap(tab + i, tab + i + 1);
			sort_tab_ascii(tab, opt, flag);
		}
		i++;
	}
}

int				is_what(char *tab)
{
	DIR			*dir;
	struct stat st;

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

static char 	**reverse_tab2(char **tab, char **cpy, int start, int i)
{
	int end;
	int ref;

	end = i - 1;
	ref = start;
	while (end >= ref)
	{
		cpy[start] = ft_strdup(tab[end]);
		end--;
		start++;
	}
	end = ft_tablen(tab) - 1;
	ref = i;
	while (end >= ref)
	{
		cpy[i] = ft_strdup(tab[end]);
		end--;
		i++;
	}
	cpy[i] = NULL;
	//free tab
	return (cpy);
}

char			**reverse_tab(char **tab)
{
	int i;
	int ref;
	int start;
	int end;
	char **cpy;

	i = 0;
	if (!(cpy = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (is_what(tab[i]) == -1)
	{
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	start = i;
	while (is_what(tab[i]) == 0)
		i++;
	end = i - 1;
	return (reverse_tab2(tab, cpy, start, i));
}

char			**create_tab(char **av, t_opt *opt, int ac, int flag)
{
	int		i;
	int		j;
	char	**tab;

	j = 0;
	i = flag - 1;
	if (opt && !opt->t)
		sort_tab_ascii(av, opt, flag);
	if (!(tab = (char **)malloc(sizeof(char *) * (ac - flag + 1))))
		return (NULL);
	while (++i < ac)
		if (is_what(av[i]) == -1)
			tab[j++] = ft_strdup(av[i]);
	i = flag - 1;
	while (++i < ac)
		if (is_what(av[i]) == 0)
			tab[j++] = ft_strdup(av[i]);
	i = flag - 1;
	while (++i < ac)
		if (is_what(av[i]) == 1)
			tab[j++] = ft_strdup(av[i]);
	tab[j] = NULL;
	if (opt && opt->t)
		tab = sort_tab_time(tab, opt, ft_tablen(tab));
	if (opt && opt->t && opt->r)
		tab = reverse_tab(tab);
	return (tab);
}
