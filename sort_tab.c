/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:40:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 11:01:37 by adu-pelo         ###   ########.fr       */
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

static char		**reverse_tab2(char **tab, char **cpy, int start, int i)
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
	ft_freetab(tab);
	return (cpy);
}

char			**reverse_tab(char **tab)
{
	int		i;
	int		ref;
	int		start;
	int		end;
	char	**cpy;

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

static void		cpy_in_tab(int i, int ac, char **tab, char **av)
{
	int ref;
	int j;

	j = 0;
	ref = i;
	while (++i < ac)
		if (is_what(av[i]) == -1)
			tab[j++] = ft_strdup(av[i]);
	i = ref;
	while (++i < ac)
		if (is_what(av[i]) == 0)
			tab[j++] = ft_strdup(av[i]);
	i = ref;
	while (++i < ac)
		if (is_what(av[i]) == 1)
			tab[j++] = ft_strdup(av[i]);
	tab[j] = NULL;
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
	cpy_in_tab(i, ac, tab, av);
	if (opt && opt->t & !opt->r)
		tab = sort_tab_time(tab, opt, ft_tablen(tab));
	else if (opt && opt->t && opt->r)
		tab = reverse_tab(tab);
	return (tab);
}
