/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:58:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/07 11:15:30 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char *alloc;

	if (size == 0)
		return (NULL);
	alloc = (unsigned char *)malloc(size);
	if (alloc)
		ft_bzero(alloc, size);
	return ((void *)alloc);
}
