/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettersft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:08:15 by ccharrie          #+#    #+#             */
/*   Updated: 2017/12/17 11:57:05 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**joindir(char **res, char **folder, int i)
{
	int j;

	j = 0;
	while (folder[j])
	{
		if (!(res[i + j] = ft_strnew(ft_strlen(folder[j]))))
			return (NULL);
		res[i + j] = ft_strcpy(res[i + j], folder[j]);
		j++;
	}
	res[i + j] = 0;
	return (res);
}

char	**ft_dir(char **folder, char **av, int i)
{
	int		fold;

	fold = 0;
	while (av[i])
	{
		if (ft_checkfile(av[i]) == 1)
		{
			if (!(folder[fold] = ft_strnew(ft_strlen(av[i]))))
				return (NULL);
			folder[fold] = ft_strcpy(folder[fold], av[i]);
			fold++;
		}
		i++;
	}
	folder[fold] = 0;
	return (folder);
}

char	**ft_fil(char **file, char **av, int i)
{
	int fil;

	fil = 0;
	while (av[i])
	{
		if (ft_checkfile(av[i]) == 0)
		{
			if (!(file[fil] = ft_strnew(ft_strlen(av[i]))))
				return (NULL);
			file[fil] = ft_strcpy(file[fil], av[i]);
			fil++;
		}
		i++;
	}
	file[fil] = 0;
	return (file);
}

char	*ft_morethan6m(t_listls *lst)
{
	char	*tmp;
	char	*date;
	char	*tmp2;

	tmp = ctime(&lst->s->st_mtimespec.tv_sec);
	date = ft_strsub(tmp, 20, 4);
	tmp2 = ft_strsub(tmp, 4, 7);
	date = ft_strjoinnfree(tmp2, date);
	free(tmp2);
	return (date);
}

void	ft_displaypath4l(char **dirnfile, int j)
{
	if (dirnfile[j + 1] && ft_checkfile(dirnfile[j + 1]) == 1)
		ft_putstr("\n\n");
	else if (dirnfile[j + 1] && ft_checkfile(dirnfile[j + 1]) == 0)
		ft_putchar(' ');
	else if (ft_checkfile(dirnfile[j]) == 0)
		ft_putchar('\n');
}
