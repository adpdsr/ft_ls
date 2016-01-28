/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:16:35 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/27 14:50:48 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

int	main(int ac, char **av)
{
	int i;
	t_list *arg;
	t_opt opt;

	if (ac > 1)
	{
		i = 1;
		if (av[i][0] == '-' && av[i][1]) // si av[1] commence par -x, on check les opt
		{
			if (get_opt(av[i], &opt)) // si une opt est invalide, return 1
				return (1);
			i = 2;
		}
		while (av[i])
		{
			get_param(av[i]);
			i++;
		}
	}
	else
	{
		printf("--- AC = 0 ---\n");
		get_param(".");
		return (0);
	}
	return (0);
}
