/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingparams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:26:26 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 11:22:30 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		parsingnopt(char **dirnfile, t_listls *lst, char *opt)
{
	DIR	*directory;
	int j;

	directory = NULL;
	j = 0;
	while (dirnfile[j])
	{
		if (!(directory = opendir(dirnfile[j])))
			stockndisplayfile(directory, dirnfile[j], opt);
		else
		{
			lst = ft_stock(lst, 0, dirnfile[j], 0);
			displaypath(dirnfile[j]);
			ft_display(lst);
			closedir(directory);
			lst = ft_delmylist(lst);
			if (!(dirnfile[j + 1]))
				free(opt);
		}
		ft_displaypath4l(dirnfile, j);
		j++;
	}
}

void		parsingopt(char **dirnfile, char *opt)
{
	DIR	*directory;
	int j;

	directory = NULL;
	j = 0;
	while (dirnfile[j])
	{
		if (ft_checklink2fold(dirnfile[j], directory, opt) == 1)
			stockndisplayfile(directory, dirnfile[j], opt);
		else if (!(directory = opendir(dirnfile[j])))
			stockndisplayfile(directory, dirnfile[j], opt);
		else
		{
			if (j != 0)
				ft_putstr("\n\n");
			ft_displayopt(dirnfile[j], opt);
			closedir(directory);
		}
		j++;
	}
	if (!(dirnfile[j]))
		free(opt);
}

void		optornot(char *opt, char **av, int i, int ac)
{
	t_listls	*lst;
	DIR			*directory;
	char		**dirnfile;

	lst = NULL;
	if (i < ac)
	{
		dirnfile = ft_getdir(i, av, opt);
		if (opt[0] == '\0')
			parsingnopt(dirnfile, lst, opt);
		else
			parsingopt(dirnfile, opt);
		ft_delmy2dtab(dirnfile);
	}
	else
	{
		directory = opendir(".");
		ft_displayopt(".", opt);
		if (ft_strchr(opt, 'l'))
			ft_putchar('\n');
		free(opt);
		closedir(directory);
	}
}

void		stockfile(t_filein *file, char *str, char *opt, char *link)
{
	t_listls	*lst;
	char		*path;

	path = ft_openpath(str);
	lst = NULL;
	if (ft_strcmp(file->d_name, link) == 0)
	{
		lstaddend(&lst, ft_lststock(file, lst, path));
		if (opt && ft_strchr(opt, 'l'))
		{
			ft_displayl(lst);
			ft_putchar('\n');
		}
		else
		{
			if (ft_strchr(str, '/'))
				ft_putstr(ft_strjoin(path, "/"));
			ft_display(lst);
			ft_putchar(' ');
		}
		lst = ft_delmylist(lst);
	}
}
