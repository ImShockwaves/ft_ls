/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complemft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 12:01:06 by ccharrie          #+#    #+#             */
/*   Updated: 2017/12/18 16:14:10 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_setuidcheck(t_listls *lst)
{
	if (lst->s->st_mode & S_IXUSR)
	{
		if (lst->s->st_mode & S_ISUID)
			ft_putchar('s');
		else
			ft_putchar('x');
	}
	else if (lst->s->st_mode & S_ISUID)
		ft_putchar('S');
	else
		ft_putchar('-');
}

void		ft_setgidcheck(t_listls *lst)
{
	if (lst->s->st_mode & S_IXGRP)
	{
		if (lst->s->st_mode & S_ISGID)
			ft_putchar('s');
		else
			ft_putchar('x');
	}
	else if (lst->s->st_mode & S_ISGID)
		ft_putchar('S');
	else
		ft_putchar('-');
}

void		ft_stickycheck(t_listls *lst)
{
	if (lst->s->st_mode & S_IXOTH)
	{
		if (lst->s->st_mode & S_ISVTX)
			ft_putchar('t');
		else
			ft_putchar('x');
	}
	else if (lst->s->st_mode & S_ISVTX)
		ft_putchar('T');
	else
		ft_putchar('-');
}

t_listls	*ft_lstorderntmp(t_listls *tmp, t_listls *lstcmp
		, t_listls *lst, t_listls *tmp2)
{
	t_listls	*lstbegin;

	lstbegin = ft_timesort(tmp, lstcmp, lst, tmp2);
	while (lst->next)
	{
		while (lstcmp->next)
		{
			if (ft_strcmp(lstcmp->next->s->d_name, tmp->s->d_name) < 0 &&
					lstcmp->next->s->st_mtimespec.tv_sec ==
					tmp->s->st_mtimespec.tv_sec)
				tmp = lstcmp->next;
			lstcmp = lstcmp->next;
		}
		if (ft_strcmp(tmp->s->d_name, lst->s->d_name) < 0 &&
				tmp->s->st_mtimespec.tv_sec == lst->s->st_mtimespec.tv_sec)
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

t_listls	*ft_lstrevorderntmp(t_listls *tmp, t_listls *lstcmp
		, t_listls *lst, t_listls *tmp2)
{
	t_listls	*lstbegin;

	lstbegin = ft_revtimesort(tmp, lstcmp, lst, tmp2);
	while (lst->next)
	{
		while (lstcmp->next)
		{
			if (ft_strcmp(lstcmp->next->s->d_name, tmp->s->d_name) > 0 &&
					lstcmp->next->s->st_mtimespec.tv_sec ==
					tmp->s->st_mtimespec.tv_sec)
				tmp = lstcmp->next;
			lstcmp = lstcmp->next;
		}
		if (ft_strcmp(tmp->s->d_name, lst->s->d_name) > 0 &&
				tmp->s->st_mtimespec.tv_sec == lst->s->st_mtimespec.tv_sec)
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
