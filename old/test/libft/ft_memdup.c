/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 11:06:57 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/09 12:14:32 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *s, size_t n)
{
	void *cpy;

	if (!(cpy = malloc(sizeof(unsigned char) * n)))
		return (NULL);
	ft_memcpy(cpy, s, n);
	return (cpy);
}
