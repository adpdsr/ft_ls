/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:28:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/08 17:05:54 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_mem_concat(char *str, char *buff)
{
	char *tmp;

	tmp = ft_strjoin(str, buff);
	ft_strdel(&str);
	return (tmp);
}

static int	ft_get_line(char **line, char *buff, char *overf)
{
	char *tmp;

	if ((tmp = ft_strchr(buff, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(buff);
		ft_memmove(overf, tmp + 1, ft_strlen(tmp + 1) + 1);
		return (1);
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char overf[256][BUFF_SIZE + 1];
	char		buff[BUFF_SIZE + 1];
	char		*str;
	int			ret;

	if (fd < 0 || fd > 256 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (ft_get_line(line, overf[fd], overf[fd]) == 1)
		return (1);
	str = ft_strdup(overf[fd]);
	ft_memset(overf[fd], 0, BUFF_SIZE + 1);
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		str = ft_mem_concat(str, buff);
		if (ft_get_line(line, str, overf[fd]) == 1)
		{
			ft_strdel(&str);
			return (1);
		}
	}
	return ((*line = str) && ft_strlen(*line) != 0);
}
