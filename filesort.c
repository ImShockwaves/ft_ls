/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:37:06 by ccharrie          #+#    #+#             */
/*   Updated: 2017/12/18 16:14:27 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_listls	*ft_revtimesort(t_listls *tmp, t_listls *lstcmp,
		t_listls *lst, t_listls *tmp2)
{
	t_listls	*lstbegin;

	lstbegin = lst;
	while (lst->next)
	{
		while (lstcmp->next)
		{
			if (lstcmp->next->s->st_mtimespec.tv_sec <
				tmp->s->st_mtimespec.tv_sec)
				tmp = lstcmp->next;
			lstcmp = lstcmp->next;
		}
		if (tmp->s->st_mtimespec.tv_sec < lst->s->st_mtimespec.tv_sec)
		{
			tmp2->s = lst->s;
			lst->s = tmp->s;
			tmp->s = tmp2->s;
		}
		lst = lst->next;
		lstcmp = lst;
		tmp = lst;
	}
	return (lstbegin);
}

t_listls	*ft_timesort(t_listls *tmp, t_listls *lstcmp
		, t_listls *lst, t_listls *tmp2)
{
	t_listls	*lstbegin;

	lstbegin = lst;
	while (lst->next)
	{
		while (lstcmp->next)
		{
			if (lstcmp->next->s->st_mtimespec.tv_sec >
					tmp->s->st_mtimespec.tv_sec)
				tmp = lstcmp->next;
			lstcmp = lstcmp->next;
		}
		if (tmp->s->st_mtimespec.tv_sec > lst->s->st_mtimespec.tv_sec)
		{
			tmp2->s = lst->s;
			lst->s = tmp->s;
			tmp->s = tmp2->s;
		}
		lst = lst->next;
		lstcmp = lst;
		tmp = lst;
	}
	return (lstbegin);
}

t_listls	*ft_revsort(t_listls *tmp, t_listls *lstcmp
		, t_listls *lst, t_listls *tmp2)
{
	t_listls	*lstbegin;

	lstbegin = lst;
	while (lst->next)
	{
		while (lstcmp->next)
		{
			if (ft_strcmp(lstcmp->next->s->d_name, tmp->s->d_name) > 0)
				tmp = lstcmp->next;
			lstcmp = lstcmp->next;
		}
		if (ft_strcmp(tmp->s->d_name, lst->s->d_name) > 0)
		{
			tmp2->s = lst->s;
			lst->s = tmp->s;
			tmp->s = tmp2->s;
		}
		lst = lst->next;
		lstcmp = lst;
		tmp = lst;
	}
	return (lstbegin);
}

t_listls	*ft_normalsort(t_listls *tmp, t_listls *lstcmp
		, t_listls *lst, t_listls *tmp2)
{
	t_listls	*lstbegin;

	lstbegin = lst;
	while (lst->next)
	{
		while (lstcmp->next)
		{
			if (ft_strcmp(lstcmp->next->s->d_name, tmp->s->d_name) < 0)
				tmp = lstcmp->next;
			lstcmp = lstcmp->next;
		}
		if (ft_strcmp(tmp->s->d_name, lst->s->d_name) < 0)
		{
			tmp2->s = lst->s;
			lst->s = tmp->s;
			tmp->s = tmp2->s;
		}
		lst = lst->next;
		lstcmp = lst;
		tmp = lst;
	}
	return (lstbegin);
}

t_listls	*ft_lstsort(t_listls *lst, int rev)
{
	t_listls	*tmp;
	t_listls	*lstcmp;
	t_listls	*tmp2;

	tmp2 = NULL;
	if (!(tmp2 = (t_listls *)malloc(sizeof(t_listls))))
		return (NULL);
	tmp2->next = NULL;
	lstcmp = lst;
	tmp = lst;
	if (lst == NULL)
		return (NULL);
	if (rev == 0)
		lst = ft_normalsort(tmp, lstcmp, lst, tmp2);
	else if (rev == 1)
		lst = ft_revsort(tmp, lstcmp, lst, tmp2);
	else if (rev == 3)
		lst = ft_lstorderntmp(tmp, lstcmp, lst, tmp2);
	else if (rev == 2)
		lst = ft_lstrevorderntmp(tmp, lstcmp, lst, tmp2);
	free(tmp2);
	return (lst);
}
