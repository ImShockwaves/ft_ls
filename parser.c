/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:30:44 by ccharrie          #+#    #+#             */
/*   Updated: 2018/06/25 18:29:18 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_parsing(int ac, char **av)
{
	DIR			*directory;
	t_filein	*file;
	t_listls	*lst;

	directory = NULL;
	file = NULL;
	lst = NULL;
	if (ac == 1)
	{
		if (!(directory = opendir(".")))
			perror("Error");
		lst = ft_stock(lst, 0, ".", 0);
		closedir(directory);
		ft_display(lst);
		lst = ft_delmylist(lst);
	}
	else
		ft_parsingparams(ac, av);
}

void		ft_recursive(t_listls *lst, int hide, int line, int rev)
{
	while (lst)
	{
		if ((lst->s->st_mode & S_IFDIR) && (ft_strcmp(lst->s->d_name, ".") != 0 &&
					ft_strcmp(lst->s->d_name, "..") != 0))
		{
			ft_putstr("\n\n");
			ft_putformat(lst->s->path, CYAN, NULL, "BOLD");
			ft_putformat(":\n", CYAN, NULL, "BOLD");
			ft_putr(lst->s->path, hide, line, rev);
		}
		lst = lst->next;
	}
}

int			ft_putr(char *str, int hide, int line, int rev)
{
	DIR			*directory;
	t_listls	*lst;

	lst = NULL;
	if (!(directory = opendir(str)))
		perror("ls error");
	else
	{
		lst = ft_stock(lst, hide, str, rev);
		closedir(directory);
	}
	if (lst == NULL)
		return (0);
	if (line == 0)
		ft_display(lst);
	else
		ft_displayl(lst);
	ft_recursive(lst, hide, line, rev);
	lst = ft_delmylist(lst);
	return (0);
}

char		**ft_gettimesort(t_listls *lst, int i)
{
	char		**res;
	t_listls	*beginlst;

	beginlst = lst;
	if (!(res = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
	i = 0;
	while (res[i] && lst)
	{
		res[i] = ft_strdup(lst->s->d_name);
		i++;
		lst = lst->next;
	}
	res[i] = 0;
	lst = beginlst;
	return (res);
}

t_listls	*ft_lstpstock(t_filein *file, t_listls *lst, char *path)
{
	int			inf;
	struct stat	buf;

	(void)file;
	inf = lstat(path, &buf);
	if (!(lst = (t_listls *)malloc(sizeof(t_listls))))
		return (NULL);
	if ((!(lst->s = (t_fileinf *)malloc(sizeof(t_fileinf)))))
		return (NULL);
	lst->s->path = ft_strdup(path);
	lst->s->st_blocks = buf.st_blocks;
	lst->s->st_mode = buf.st_mode;
	lst->s->st_nlink = buf.st_nlink;
	lst->s->st_uid = buf.st_uid;
	lst->s->st_gid = buf.st_gid;
	lst->s->st_mtimespec = buf.st_mtimespec;
	lst->s->st_size = buf.st_size;
	lst->s->d_name = ft_strdup(path);
	lst->next = NULL;
	free(path);
	return (lst);
}
