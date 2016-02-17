/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 12:07:24 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/02/17 12:09:29 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *s1, size_t len)
{
	char *scpy;

	if (!(scpy = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	return (ft_strncpy(scpy, s1, len));
}
