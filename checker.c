/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:32:00 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 12:07:41 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_checkfile(char *params)
{
	DIR				*directory;

	if (!(directory = opendir(params)))
		return (0);
	else
	{
		closedir(directory);
		return (1);
	}
}

int		ft_checkopt(char *opt)
{
	int i;

	i = 0;
	while (opt[i])
	{
		if (opt[i] == 'R' || opt[i] == 'r' || opt[i] == 't'
				|| opt[i] == 'l' || opt[i] == 'a')
			i++;
		else
		{
			ft_putformat("ls: illegal option -- ", LIGHT_RED, NULL,
					"BOLD UNDERLINE");
			ft_putcformat(opt[i], LIGHT_RED, NULL, "BOLD UNDERLINE");
			ft_putformat("\nusage: ls [-Ralrt] [file ...]\n", LIGHT_RED,
					NULL, "BOLD UNDERLINE");
			return (0);
		}
	}
	return (1);
}

int		ft_checklink2fold(char *str, DIR *directory, char *opt)
{
	char		*path;
	char		*link;
	t_filein	*file;

	path = ft_openpath(str);
	link = ft_thefile(str);
	directory = opendir(path);
	while ((file = readdir(directory)) != NULL)
	{
		if (ft_strcmp(link, file->d_name) == 0)
		{
			if (ft_strchr(opt, 'l') && file->d_type == DT_LNK)
			{
				closedir(directory);
				return (1);
			}
		}
	}
	closedir(directory);
	return (0);
}

void	ft_delmy2dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_deltabs(char **s1, char **s2, char **res, int i)
{
	res = joindir(res, s2, i);
	if (s1)
		ft_delmy2dtab(s1);
	if (s2)
		ft_delmy2dtab(s2);
	return (res);
}
