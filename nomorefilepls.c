/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nomorefilepls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:05:54 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 11:10:07 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_gethome(t_filein *file, t_listls *lst, char *params)
{
	if (ft_strcmp(params, "/") == 0)
	{
		if (ft_strcmp(file->d_name, ".") == 0)
			lstaddend(&lst, ft_lstpstock(file, lst, params));
	}
}
