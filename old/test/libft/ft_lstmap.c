/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 11:42:10 by adu-pelo          #+#    #+#             */
/*   Updated: 2015/12/14 10:44:17 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlst;
	t_list *newlm;
	t_list *prevlm;

	newlst = NULL;
	newlst = f(lst);
	prevlm = newlst;
	lst = lst->next;
	while (lst)
	{
		newlm = f(lst);
		prevlm->next = newlm;
		prevlm = newlm;
		lst = lst->next;
	}
	prevlm->next = NULL;
	return (newlst);
}
