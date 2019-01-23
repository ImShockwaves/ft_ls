/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:53:27 by ccharrie          #+#    #+#             */
/*   Updated: 2018/01/04 11:11:53 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

# define LBUFF_SIZE 10000

typedef struct dirent	t_filein;

typedef	struct		s_fileinf
{
	char			*d_name;
	unsigned char	d_type;
	char			*path;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	blkcnt_t		st_blocks;
	struct timespec	st_mtimespec;
}					t_fileinf;

typedef struct		s_listls
{
	t_fileinf		*s;
	struct s_listls	*next;
}					t_listls;

/*
**  chained list functions
*/

t_listls			*ft_lstsort(t_listls *lst, int rev);
t_listls			*ft_lststock(t_filein *file, t_listls *lst, char *path);
t_listls			*ft_stock(t_listls *lst, int hide, char *path, int rev);
t_listls			*ft_delmylist(t_listls *lst);
t_listls			*ft_lstorderntmp(t_listls *tmp, t_listls *lstcmp
					, t_listls *lst, t_listls *tmp2);
t_listls			*ft_lstrevorderntmp(t_listls *tmp, t_listls *lstcmp
					, t_listls *lst, t_listls *tmp2);
t_listls			*ft_revsort(t_listls *tmp, t_listls *lstcmp
					, t_listls *lst, t_listls *tmp2);
t_listls			*ft_normalsort(t_listls *tmp, t_listls *lstcmp
					, t_listls *lst, t_listls *tmp2);
t_listls			*ft_revtimesort(t_listls *tmp, t_listls *lstcmp
					, t_listls *lst, t_listls *tmp2);
t_listls			*ft_timesort(t_listls *tmp, t_listls *lstcmp
					, t_listls *lst, t_listls *tmp2);
t_listls			*ft_lstpstock(t_filein *file, t_listls *lst, char *path);

/*
**  void functions
*/

void				ft_parsing(int ac, char **av);
void				lstaddend(t_listls **lst, t_listls *new);
void				ft_display(t_listls *lst);
void				ft_displayl(t_listls *lst);
void				ft_parsingparams(int ac, char **av);
void				stockndisplayfile(DIR *directory, char *str, char *opt);
void				ft_displayopt(char *path, char *opt);
void				optornot(char *opt, char **av, int i, int ac);
void				stockfile(t_filein *file, char *str, char *opt, char *link);
void				displaylall(t_listls *lst);
void				ft_putmode(t_listls *lst);
void				displaypath(char *path);
void				ft_delmy2dtab(char **tab);
void				ft_displaypath4l(char **dirnfile, int j);
void				ft_stickycheck(t_listls *lst);
void				ft_setgidcheck(t_listls *lst);
void				ft_setuidcheck(t_listls *lst);
void				ft_gethome(t_filein *file, t_listls *lst, char *params);

/*
** integer functions
*/

int					ft_putr(char *str, int hide, int line, int rev);
int					ft_checkfile(char *params);
int					ft_checkopt(char *opt);
int					ft_checklink2fold(char *str, DIR *directory, char *opt);

/*
** char and string functions
*/

char				*ft_openpath(char *str);
char				*ft_thefile(char *str);
char				**ft_getdir(int i, char **av, char *opt);
char				**ft_sortparams(char **params, char *opt);
char				**ft_fil(char **file, char **av, int i);
char				**ft_dir(char **folder, char **av, int i);
char				**joindir(char **res, char **folder, int i);
char				**ft_deltabs(char **s1, char **s2, char **res, int i);
char				*ft_morethan6m(t_listls *lst);
char				**ft_gettimesort(t_listls *lst, int i);

#endif
