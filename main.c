/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:35:11 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/18 16:50:57 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // test

static int	is_valid_flag(char c)
{
	if (c)
		if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
			return (0);
	return (1);
}

static int	get_flag(char *input, t_opt *flags)
{
	int i;

	ft_putstr("options : ");
	ft_putendl(&input[i]);
	ft_putstr("\n");
	if (input[0] == '-' && is_valid_flag(input[1]) == 0)
	{
		i = 0;
		while (input[i] != '\0')
		{
			if (input[i] == 'l')
				flags->l = 1;
			if (input[i] == 'R')
				flags->r_big = 1;
			if (input[i] == 'a')
				flags->a = 1;
			if (input[i] == 'r')
				flags->r = 1;
			if (input[i] == 't')
				flags->t = 1;
			i++;
		}
	}
	else
		return (1);
	return (0);
}

static void	print_tab_flags(t_opt *flags) // test
{
	printf("case l is : %d\n", flags->l);
	printf("case R is : %d\n", flags->r_big);
	printf("case a is : %d\n", flags->a);
	printf("case r is : %d\n", flags->r);
	printf("case t is : %d\n", flags->t);
}

int		main(int ac, char **av)
{
	int		i;
	char 	*input;
	t_opt 	flags;
	t_list	*path;

	path = NULL;
	flags = (t_opt){0, 0, 0, 0, 0};
	if (ac > 1)
	{
		if (av[1][0] == '-')
			get_flag(av[1], &flags);
		else // cas ou pas d'opt mais args
		//get_param; --> save all param names (and path) in nodes
	}
	print_tab_flags(&flags);
	return (0);
}
