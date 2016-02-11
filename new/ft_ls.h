/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 14:59:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/11 16:07:39 by adu-pelo         ###   ########.fr       */
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

typedef struct		s_pad
{
	size_t			len_usr;
	size_t			len_grp;
	size_t			len_lnk;
	size_t			len_siz;
	size_t			len_maj;
	size_t			len_min;
}					t_pad;

typedef struct 		s_opt
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_opt;

typedef struct		s_lst
{
	char			*name;
	char			*chem;
	char			perm[11];
	char			*user_id;
	char			*group_id;
	char			*date;
	int				date_id;
	int				blok;
	char			*link;
	char			*size;
	char			*maj;
	char			*min;
	struct s_lst 	*next;
}					t_lst;

void	ft_putnbr_endl(int n);
void	ft_putstr_s(char *s);
void	put_total(t_lst *lst, int hidd);

void	get_param(char *path, t_opt *opt);
void	padding(t_lst *lst);

char	*format_size(char *s);
char	*join_maj_min(dev_t device_id);

void	display_rllst(t_lst *lst, int hidd);
void	display_llst(t_lst *lst, int hidd);
void	display_rlst(t_lst *lst, int hidd);
void	display_lst(t_lst *lst, int hidd);

int		get_opt(char *str, t_opt *opt);
void	init_opt(t_opt *opt);

t_lst	*lst_sort_ascii(t_lst *lst);
t_lst	*lst_sort_time(t_lst *lst);

#endif
