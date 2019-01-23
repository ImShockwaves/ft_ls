/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:15:54 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/03 16:00:23 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_listls	*ft_stock(t_listls *lst, int hide, char *path, int rev)
{
	t_filein	*file;
	DIR			*directory;

	directory = opendir(path);
	while ((file = readdir(directory)))
	{
		if (hide == 0)
		{
			if (file->d_name[0] != '.')
				lstaddend(&lst, ft_lststock(file, lst, path));
		}
		else
			lstaddend(&lst, ft_lststock(file, lst, path));
	}
	closedir(directory);
	if (lst == NULL)
		return (NULL);
	lst = ft_lstsort(lst, rev);
	return (lst);
}

void		ft_displayrorl(char *path, char *opt, int rev, int hide)
{
	t_listls	*lst;

	lst = NULL;
	if (ft_strchr(opt, 'R'))
	{
		displaypath(path);
		if (ft_strchr(opt, 'l'))
			ft_putr(path, hide, 1, rev);
		else
			ft_putr(path, hide, 0, rev);
	}
	else
	{
		if (ft_strcmp(path, "."))
			displaypath(path);
		lst = ft_stock(lst, hide, path, rev);
		if (ft_strchr(opt, 'l'))
			ft_displayl(lst);
		else
			ft_display(lst);
	}
	lst = ft_delmylist(lst);
}

void		ft_displayopt(char *path, char *opt)
{
	int	rev;
	int	hide;

	rev = 0;
	hide = 0;
	if (ft_checkopt(opt) == 1)
	{
		if (ft_strchr(opt, 'a'))
			hide = 1;
		if (ft_strchr(opt, 'r'))
		{
			if (ft_strchr(opt, 't'))
				rev = 2;
			else
				rev = 1;
		}
		else if (ft_strchr(opt, 't'))
			rev = 3;
		ft_displayrorl(path, opt, rev, hide);
	}
}

void		stockndisplayfile(DIR *directory, char *str, char *opt)
{
	t_filein	*file;
	char		*link;

	if (directory == NULL)
	{
		if (errno == ENOTDIR || ft_checklink2fold(str, directory, opt) == 1)
		{
			directory = opendir(ft_openpath(str));
			link = ft_thefile(str);
			while ((file = readdir(directory)) != NULL)
				stockfile(file, str, opt, link);
			closedir(directory);
		}
		else
		{
			ft_putchar('\n');
			perror("ls error");
		}
	}
}

void		ft_parsingparams(int ac, char **av)
{
	int				i;
	char			*opt;
	char			*inter;

	opt = ft_strnew(1);
	opt[0] = '\0';
	i = 1;
	if (ac > 1)
	{
		while (av[i] && av[i][0] == '-' && ft_strlen(av[i]) > 1)
		{
			if (!(ft_strcmp(av[i], "--")))
			{
				i++;
				break ;
			}
			inter = ft_strsub(av[i], 1, ft_strlen(av[i]));
			opt = ft_strjoinnfree(inter, opt);
			free(inter);
			i++;
		}
		optornot(opt, av, i, ac);
	}
}
