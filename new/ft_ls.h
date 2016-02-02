/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 14:59:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/02 14:23:01 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"

# include <unistd.h> // write, readlink
# include <dirent.h> // opendir, readdir, closedir
# include <sys/stat.h> // stat, lstat
# include <pwd.h> // getpwuid
# include <uuid/uuid.h> // getpwuid, getgrgid
# include <grp.h> // getgrgid
# include <sys/xattr.h> // listxattr, getxattr
# include <time.h> // time, ctime
# include <stdlib.h> // malloc, free, exit
# include <stdio.h> // perror, strerror

typedef struct 		s_opt // stock input opt
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_opt;

typedef struct		s_lst // stock file info
{
	char			*name; // name of file
	char			*chem;
	char			perm[11];
	char			*user_id; // user name of file
	char			*group_id; // group name of file
	char			*date; // date of modif of file
	int				blok;
	char			*link;
	char			*size;
	struct s_lst 	*next;
}					t_lst;

void	get_param(char *path);
int		get_opt(char *str, t_opt *opt);
void	padding(t_lst *lst); // test

void	sort_ascii(t_lst **lst, int (*f)());

// basic functions

void	ft_putstr_s(char *s);
void	ft_putnbr_endl(int n);

#endif
