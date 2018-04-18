/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:34:45 by acouturi          #+#    #+#             */
/*   Updated: 2018/04/18 15:59:48 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

char		*have_com(t_error *error, char *ret)
{
	char	*tmp;
	int		i;

	tmp = ft_strchr(ret, '"');
	tmp[0] = 0;
	i = (int)tmp;
	while ((++i) >= 0 && tmp[i] && tmp[i] != '#')
		if (tmp[i] != ' ' && tmp[i] != '\n' &&
				add_error(error, "fichier non valide") == 0)
			return (NULL);
	return (ret);
}

char		*have_truc(int fd, t_error *error, int *lignelu, char *truc)
{
	char	*ret;
	char	*tmp;
	int		i;

	get_next_line(fd, &tmp);
	if ((ft_strncmp(truc, tmp, ft_strlen(truc)) ||
			ft_strncmp(&tmp[ft_strlen(truc)], " \"", 2))
			&& add_error(error, "fich. non val") == 0)
		return (NULL);
	ret = ft_strdup(&tmp[ft_strlen(truc) + 2]);
	i = (((int)destroy(&tmp) & (*lignelu)++)) & 0;
	while (ft_strcount(ret, '"') != 1)
	{
		if ((ft_strcount(ret, '"') > 1 &&
				add_error(error, "fichier non valide") == 0)
		|| (get_next_line(fd, &tmp) != 1 &&
				add_error(error, "probleme lecture") == 0))
			return (NULL);
		ret = ft_strjoinfree(ret, "\n");
		ret = ft_strjoinfree(ret, tmp);
		i = ((int)destroy(&tmp) & (*lignelu)++) & 0;
	}
	return (have_com(error, ret));
}

t_list		*have_next(t_list *lst, t_error *error)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
	{
		add_error(error, "mallocerror");
		return (NULL);
	}
	lst->next = new;
	lst = new;
	lst->content_size = 1;
	lst->next = 0;
	return (lst);
}

int			have_header(int fd, t_error *error)
{
	t_list	*lst;
	t_list	*new;
	int		*magic;
	int		lignelu;

	if (!(magic = (int*)malloc(sizeof(int))))
		return (add_error(error, "mallocerror"));
	*magic = COREWAR_EXEC_MAGIC;
	if (!(g_lines = (t_list *)malloc(sizeof(t_list))))
		return (add_error(error, "mallocerror"));
	lst = g_lines;
	lst->content_size = 3;
	lst->next = 0;
	lst->content = magic;
	lignelu = 0;
	lst = have_next(lst, error);
	lst->content = have_truc(fd, error, &lignelu, NAME_CMD_STRING);
	if (error->nberror > 0)
		return (0);
	lst = have_next(lst, error);
	lst->content = have_truc(fd, error, &lignelu, COMMENT_CMD_STRING);
	if (error->nberror > 0)
		return (0);
	return (lignelu);
}
