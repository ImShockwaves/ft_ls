/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:31:50 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/03 14:42:29 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_colorfile(t_listls *lst)
{
	if (lst->s->d_type == 4)
		ft_putformat(lst->s->d_name, CYAN, NULL, "BOLD");
	else if (lst->s->d_type == DT_LNK)
		ft_putformat(lst->s->d_name, GREEN, NULL, "BOLD");
	else if (lst->s->d_type == DT_SOCK)
		ft_putformat(lst->s->d_name, WHITE, NULL, NULL);
	else if (lst->s->st_mode & S_ISUID)
		ft_putformat(lst->s->d_name, BLACK, BG_RED, NULL);
	else if (lst->s->st_mode & S_ISGID)
		ft_putformat(lst->s->d_name, BLACK, BG_CYAN, NULL);
	else if (lst->s->st_mode & S_IXUSR || lst->s->st_mode & S_IXGRP
			|| lst->s->st_mode & S_IXOTH)
		ft_putformat(lst->s->d_name, LIGHT_RED, NULL, NULL);
	else
		ft_putstr(lst->s->d_name);
}

void		ft_putuserndate(t_listls *lst)
{
	struct passwd	*user;
	struct group	*group;
	char			*date;

	if (!(user = getpwuid(lst->s->st_uid)))
		ft_putnbr(lst->s->st_uid);
	else
		ft_putstr(user->pw_name);
	ft_putchar('\t');
	if (!(group = getgrgid(lst->s->st_gid)))
		ft_putnbr(lst->s->st_gid);
	else
		ft_putstr(group->gr_name);
	ft_putchar('\t');
	ft_putnbr(lst->s->st_size);
	ft_putchar('\t');
	if (lst->s->st_mtimespec.tv_sec > 1477880000)
		date = ft_strsub(ctime(&lst->s->st_mtimespec.tv_sec), 4, 12);
	else
		date = ft_morethan6m(lst);
	ft_putstr(date);
	free(date);
	ft_putchar(' ');
}

void		ft_putmode(t_listls *lst)
{
	char	mode;
	int		ret;
	char	buf[LBUFF_SIZE];

	ft_putchar(mode = (lst->s->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar(mode = (lst->s->st_mode & S_IWUSR) ? 'w' : '-');
	ft_setuidcheck(lst);
	ft_putchar(mode = (lst->s->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar(mode = (lst->s->st_mode & S_IWGRP) ? 'w' : '-');
	ft_setgidcheck(lst);
	ft_putchar(mode = (lst->s->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar(mode = (lst->s->st_mode & S_IWOTH) ? 'w' : '-');
	ft_stickycheck(lst);
	ft_putchar('\t');
	ft_putnbr(lst->s->st_nlink);
	ft_putchar('\t');
	ft_putuserndate(lst);
	ft_colorfile(lst);
	if (lst->s->d_type == DT_LNK)
	{
		ft_putstr(" -> ");
		ft_bzero(buf, LBUFF_SIZE);
		ret = readlink(lst->s->path, buf, LBUFF_SIZE);
		ft_putstr(buf);
	}
}

void		ft_display(t_listls *lst)
{
	t_listls *begin;

	begin = lst;
	while (lst)
	{
		ft_colorfile(lst);
		if (lst->next)
			ft_putchar('\t');
		lst = lst->next;
	}
	lst = begin;
	if (lst && lst->next)
		ft_putchar('\n');
}

void		ft_displayl(t_listls *lst)
{
	t_listls		*begin;
	int				block;

	begin = lst;
	block = 0;
	if (lst && lst->next)
	{
		while (lst)
		{
			block = block + lst->s->st_blocks;
			lst = lst->next;
		}
		ft_putstr("total ");
		ft_putnbr(block);
		ft_putchar('\n');
	}
	lst = begin;
	while (lst)
	{
		displaylall(lst);
		lst = lst->next;
	}
	lst = begin;
	if (lst && lst->next)
		ft_putchar('\n');
}
