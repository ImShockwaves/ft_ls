/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:41:12 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 11:24:12 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		lstaddend(t_listls **lst, t_listls *new)
{
	t_listls *tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = tmp;
	}
}

t_listls	*ft_delmylist(t_listls *lst)
{
	t_listls *nextlink;

	if (lst)
	{
		free(lst->s->d_name);
		free(lst->s->path);
		free(lst->s);
		nextlink = lst->next;
		free(lst);
		ft_delmylist(nextlink);
	}
	return (lst = NULL);
}

t_listls	*ft_lststock(t_filein *file, t_listls *lst, char *path)
{
	int			inf;
	struct stat	buf;
	char		*rpath;

	path = ft_strjoin(path, "/");
	rpath = ft_strjoin(path, file->d_name);
	inf = lstat(rpath, &buf);
	if (!(lst = (t_listls *)malloc(sizeof(t_listls))))
		return (NULL);
	if ((!(lst->s = (t_fileinf *)malloc(sizeof(t_fileinf)))))
		return (NULL);
	lst->s->path = ft_strdup(rpath);
	lst->s->st_blocks = buf.st_blocks;
	lst->s->st_mode = buf.st_mode;
	lst->s->st_nlink = buf.st_nlink;
	lst->s->st_uid = buf.st_uid;
	lst->s->st_gid = buf.st_gid;
	lst->s->st_mtimespec = buf.st_mtimespec;
	lst->s->st_size = buf.st_size;
	lst->s->d_name = ft_strdup(file->d_name);
	lst->s->d_type = file->d_type;
	lst->next = NULL;
	free(path);
	free(rpath);
	return (lst);
}

void		displaylall(t_listls *lst)
{
	if (lst->s->d_type == 4)
		ft_putchar('d');
	else if (lst->s->d_type == DT_LNK)
		ft_putchar('l');
	else if (lst->s->d_type == DT_CHR)
		ft_putchar('c');
	else if (lst->s->d_type == DT_BLK)
		ft_putchar('b');
	else if (lst->s->d_type == DT_FIFO)
		ft_putchar('p');
	else if (lst->s->d_type == DT_SOCK)
		ft_putchar('s');
	else
		ft_putchar('-');
	ft_putmode(lst);
	if (lst && lst->next)
		ft_putchar('\n');
}

void		displaypath(char *path)
{
	ft_putformat(path, CYAN, NULL, "BOLD");
	ft_putformat(":\n", CYAN, NULL, "BOLD");
}
