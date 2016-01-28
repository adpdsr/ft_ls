/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:25:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/28 13:09:32 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h> // remove

static void	init_struct_info(t_info *info)
{
	ft_putendl("--- INIT INFO STRUCT ---\n");
	info->mode = 0;
	info->uid = 0;
	info->gid = 0;
}

static void	get_stat_info(char *path, struct stat *st, t_info *info)
{
	struct passwd *pwd;

	if (stat(path, st) == -1) // get stat of path
	{
		ft_putendl("cant get stat info");
		exit(EXIT_FAILURE);
	}
	if ((pwd = getpwuid(st->st_uid)) != NULL)
	{
		info->uid = st->st_uid;
		info->gid = st->st_gid;
		info->mode = st->st_mode;
		//printf("st_uid dans struct stat : %u\n\n", st->st_uid);
		//printf("pw_name dans struct passwd : %s\n\n", pwd->pw_name);
		//printf("uid saved in struct info : %u\n\n", info->uid);
	}
}

static void	display_info(t_info *info)
{
	ft_putendl("--- INFO SAVED ---\n");
	printf("mode in my struct is : %hu\n", info->mode);
	printf("uid in my struct is : %u\n", info->uid);
	printf("gid in my struct is is : %u\n", info->gid);
}

static int get_size(char *path, struct stat *st)
{
	int size;

	if (stat(path, st) == -1)
	{
		ft_putendl("get_size failed :(");
		exit(EXIT_FAILURE);
	}
	else
		size = st->st_size;
	return (size);
}

static int cnt_ghosts(struct dirent *rd)
{
	int cnt;

	cnt = 0;
	if ((rd->d_name[0]) == '.') // count . and ..
		cnt++;
	else
		return (0);
	return (cnt);
}

static int define_protection(char *path, struct stat *st) // useless
{
	int str = 0;

	if (stat(path, st) == 1)
	{
		ft_putendl("define_protecion failed :(");
		exit(EXIT_FAILURE);
	}
	else
		str = st->st_mode;
	return (str);
}

static int cnt_objects(struct dirent *rd, struct stat *st)
{
	int cnt;

	cnt = 0;
	if (ft_strcmp(rd->d_name, ".") != 0 && ft_strcmp(rd->d_name, "..") != 0)
	{
		ft_putstr("object name : ");
		ft_putendl(rd->d_name);
		cnt++;
	}
	return (cnt);
}

struct passwd *get_uid(char *path, struct stat *st)
{
	struct passwd *pwd;

	if (stat(path, st) == 1)
	{
		ft_putendl("get_uid failed :(");
		exit(EXIT_FAILURE);
	}
	if ((pwd = getpwuid(st->st_uid)) != NULL)
		printf("user id : %s\n", pwd->pw_name);
	return (pwd);
}

struct group *get_gid(char *path, struct stat *st)
{
	struct group *grp;

	if (stat(path, st) == 1)
	{
		ft_putendl("get_gid failed :(");
		exit(EXIT_FAILURE);
	}
	if ((grp = getgrgid(st->st_gid)) != NULL)
	{
		printf("group id : %s\n", grp->gr_name);
	}
	return (grp);
}

static void get_time(char *path, struct stat *st)
{
	if (stat(path, st) == 1)
	{
		ft_putendl("get_time failed :(");
		exit(EXIT_FAILURE);
	}
	printf("time last modif : %s\n", ctime(&st->st_mtime));
}

int		main(int ac, char **av)
{
	t_info	info;

	int cnt_obj;
	int cnt_gh;
	int	size_tot;
	struct stat st;
	struct passwd *uid = NULL; // user id
	int str = 0; // useless
	DIR *dir = NULL; // directory name
	char *path = NULL;
	char *protec = NULL; // protection type
	struct dirent *rd = NULL;

	if (ac != 1)
		path = av[1];
	else
	{
		ft_putendl("WRONG NUMBER OF ARGS");
		return (1);
	}
	dir = opendir(path); // ouverture du dossier path
	while ((rd = readdir(dir)) != NULL) // tant qu'on a pas lu tt le contenu
	{
		cnt_obj += cnt_objects(rd, &st);
		size_tot += get_size(path, &st);
		cnt_gh += cnt_ghosts(rd);
		str = define_protection(path, &st); // useless
		uid = get_uid(path, &st); // not used
		get_gid(path, &st);
		get_time(path, &st);
		//ft_putstr("Protection type  : ");
		//ft_putnbr(str);
		//ft_putstr("\n\n");
	}
	ft_putstr("\nnumber of objects (files + dir, without ghosts) in this dir : ");
	ft_putnbr(cnt_obj);
	ft_putstr("\n\n");

	ft_putstr("total size of objects in this dir : ");
	ft_putnbr(size_tot);
	ft_putstr("\n\n");

	ft_putstr("number of ghost in this dir : ");
	ft_putnbr(cnt_gh);
	ft_putstr("\n\n");

	init_struct_info(&info);
	get_stat_info(path, &st, &info);
	display_info(&info);
	return (0);
}
