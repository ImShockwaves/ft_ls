/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:10:28 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 11:03:23 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**ft_joindirnfile(char **file, char **folder)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	while (file[i])
		i++;
	while (folder[j])
		j++;
	if (!(res = (char **)malloc(sizeof(char *) * (i + j + 1))))
		return (NULL);
	i = 0;
	if (file)
	{
		while (file[i])
		{
			if (!(res[i] = ft_strnew(ft_strlen(file[i]))))
				return (NULL);
			res[i] = ft_strcpy(res[i], file[i]);
			i++;
		}
	}
	res = ft_deltabs(file, folder, res, i);
	return (res);
}

char		**ft_getfile(char **file, int i, char **av, char *opt)
{
	int		fil;
	int		tmp;

	fil = 0;
	tmp = i;
	while (av[i])
	{
		if (ft_checkfile(av[i]) == 0)
			fil++;
		i++;
	}
	if (!(file = (char **)malloc(sizeof(char *) * fil + 1)))
		return (NULL);
	i = tmp;
	file = ft_fil(file, av, i);
	if (file[0])
		file = ft_sortparams(file, opt);
	return (file);
}

char		**ft_getdir(int i, char **av, char *opt)
{
	char	**folder;
	int		fold;
	int		tmp;
	char	**file;

	fold = 0;
	file = NULL;
	file = ft_getfile(file, i, av, opt);
	tmp = i;
	while (av[i])
	{
		if (ft_checkfile(av[i]) == 1)
			fold++;
		i++;
	}
	if (!(folder = (char **)malloc(sizeof(char *) * fold + 1)))
		return (NULL);
	i = tmp;
	folder = ft_dir(folder, av, i);
	if (folder[0])
		folder = ft_sortparams(folder, opt);
	return (ft_joindirnfile(file, folder));
}

char		*ft_openpath(char *str)
{
	int len;

	len = ft_strlen(str);
	if (ft_strchr(str, '/') && ft_strchr(str, '/') != &str[len - 1])
	{
		while (len != 1 && str[len] != '/')
			len--;
		return (ft_strsub(str, 0, len));
	}
	else
		return (".");
}

char		*ft_thefile(char *str)
{
	char	*tmp;
	int		len;

	len = ft_strlen(str);
	if (ft_strchr(str, '/'))
	{
		while (len != 0 && str[len] != '/')
			len--;
		tmp = ft_strsub(str, len + 1, ft_strlen(str));
		return (tmp);
	}
	return (str);
}
