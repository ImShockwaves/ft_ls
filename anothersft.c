/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anothersft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:44:10 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 11:15:50 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**ft_revtimesorting(char **params, int i, t_listls *lst)
{
	DIR			*directory;
	char		**res;
	t_filein	*file;

	lst = NULL;
	res = NULL;
	while (params[i])
	{
		directory = opendir(ft_openpath(params[i]));
		while ((file = readdir(directory)) != NULL)
		{
			ft_gethome(file, lst, params[i]);
			if (ft_strcmp(file->d_name, ft_thefile(params[i])) == 0)
				lstaddend(&lst, ft_lstpstock(file, lst, params[i]));
		}
		i++;
		closedir(directory);
	}
	free(params);
	lst = ft_lstsort(lst, 2);
	res = ft_gettimesort(lst, i);
	lst = ft_delmylist(lst);
	return (res);
}

char		**ft_timesorting(char **params, int i, t_listls *lst)
{
	DIR			*directory;
	char		**res;
	t_filein	*file;

	lst = NULL;
	res = NULL;
	while (params[i])
	{
		directory = opendir(ft_openpath(params[i]));
		while ((file = readdir(directory)) != NULL)
		{
			ft_gethome(file, lst, params[i]);
			if (ft_strcmp(file->d_name, ft_thefile(params[i])) == 0)
				lstaddend(&lst, ft_lstpstock(file, lst, params[i]));
		}
		i++;
		closedir(directory);
	}
	free(params);
	lst = ft_lstsort(lst, 3);
	res = ft_gettimesort(lst, i);
	lst = ft_delmylist(lst);
	return (res);
}

char		**ft_revsorting(char **params, int i, char *tmp)
{
	while (params[i + 1])
	{
		if (ft_strcmp(params[i], params[i + 1]) < 0)
		{
			if (!(tmp = ft_strnew(ft_strlen(params[i]))))
				return (NULL);
			tmp = ft_strcpy(tmp, params[i]);
			free(params[i]);
			if (!(params[i] = ft_strnew(ft_strlen(params[i + 1]))))
				return (NULL);
			params[i] = ft_strcpy(params[i], params[i + 1]);
			free(params[i + 1]);
			if (!(params[i + 1] = ft_strnew(ft_strlen(tmp))))
				return (NULL);
			params[i + 1] = ft_strcpy(params[i + 1], tmp);
			free(tmp);
			i = 0;
		}
		i++;
	}
	return (params);
}

char		**ft_sorting(char **params, int i, char *tmp)
{
	while (params[i + 1])
	{
		if (ft_strcmp(params[i], params[i + 1]) > 0)
		{
			if (!(tmp = ft_strnew(ft_strlen(params[i]))))
				return (NULL);
			tmp = ft_strcpy(tmp, params[i]);
			free(params[i]);
			if (!(params[i] = ft_strnew(ft_strlen(params[i + 1]))))
				return (NULL);
			params[i] = ft_strcpy(params[i], params[i + 1]);
			free(params[i + 1]);
			if (!(params[i + 1] = ft_strnew(ft_strlen(tmp))))
				return (NULL);
			params[i + 1] = ft_strcpy(params[i + 1], tmp);
			free(tmp);
			i = 0;
		}
		i++;
	}
	return (params);
}

char		**ft_sortparams(char **params, char *opt)
{
	int			i;
	t_listls	*lst;
	char		*tmp;

	i = 0;
	tmp = NULL;
	lst = NULL;
	if (params)
	{
		if (ft_strchr(opt, 'r') && ft_strchr(opt, 't'))
			params = ft_revtimesorting(params, i, lst);
		else if (ft_strchr(opt, 'r'))
			params = ft_revsorting(params, i, tmp);
		else if (ft_strchr(opt, 't'))
			params = ft_timesorting(params, i, lst);
		else
			params = ft_sorting(params, i, tmp);
		return (params);
	}
	return (NULL);
}
