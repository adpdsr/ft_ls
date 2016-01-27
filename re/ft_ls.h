/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 14:59:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/20 18:43:41 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"

# include <unistd.h> // write, readlink
# include <dirent.h> // opendir, readdir, closedir
# include <sys/stat.h> // stat, lstat
# include <pwd.h> // getpwuid
// # include <uuid/uuid.h> // getpwuid, getgrgid
# include <grp.h> // getgrgid
# include <sys/xattr.h> // listxattr, getxattr
# include <time.h> // time, ctime
# include <stdlib.h> // malloc, free, exit
# include <stdio.h> // perror, strerror

typedef struct 		s_opt // stock input opt
{
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
	char			err;
}					t_opt;

typedef struct		s_file // stock file info
{
	char			*name; // name of file
	char			*user_id; // user name of file
	char			*group_id; // group name of file
	char			*date; // date of modif of file
	int			size; // size of file
}					t_info;

typedef struct		s_lst
{
	char			*name;
	char 			*path;
	struct s_lst 	*next;
}					t_lst;

#endif
