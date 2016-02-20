/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:40:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/20 16:37:35 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

static void	tab_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void		sort_tab(char **tab, t_opt *opt, int flag)
{
	int i;

	i = 1;
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
