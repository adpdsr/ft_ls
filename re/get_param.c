/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:46:02 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/27 18:18:34 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_stat(char *path, struct stat st)
{
	struct passwd *pwd;

	printf("str is : %s\n", path);
	if ((pwd = getpwuid(st.st_uid)) != NULL)
	{
		printf("pw_name : %s", pwd->pw_name);
	}
	else
	{
		ft_putendl("getpwuid failed");
		exit(EXIT_FAILURE);
	}
}

void	get_param(char *str)
{
	DIR 			*dir;
	struct stat 	st;
	struct dirent 	*rd;

	//st = NULL;
	if ((dir = opendir(str)) != NULL) // -> pour les dirs
	{
		while ((rd = readdir(dir)) != NULL) // tant qu'on a pas lu tout le contenu
		{
			printf("| %s | is a directory\n", str);
			if (stat(str, &st) == 0) // si stat ok
				get_stat(str, st);
			else
			{
				ft_putendl("stat failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	else // pour les files
		printf("| %s | is a file\n", str);
}
