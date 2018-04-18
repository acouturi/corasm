/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:49:01 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/18 16:34:18 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	change_line_if_needed(char **l)
{
	int		i;
	char	*new;
	int		j;

	i = 0;
	new = 0;
	j = -1;
	while ((*l)[i] == ' ' || (*l)[i] == '\t')
		i++;
	while ((*l)[i])
	{
		if ((*l)[i] == ' ' || (*l)[i] == '\t')
			return (1);
		if (((*l)[i] == DIRECT_CHAR || (*l)[i] == LABEL_CHAR) && (*l)[i + 1]
			&& (*l)[i + 1] != ' ' && (*l)[i + 1] != '\t')
			break ;
		i++;
	}
	if (!(*l)[i])
		return (1);
	if (!(new = (char*)malloc(ft_strlen(*l) + 2)))
		return (0);
	while (++j < i)
		new[j] = (*l)[j];
	new[j] = ' ';
	new[j + 1] = 0;
	ft_strcpy(&(new[j + 1]), &((*l)[i]));
	ft_strdel(l);
	*l = ft_strdup(new);
	ft_strdel(&new);
	return (1);
}

int			read_code(char *l)
{
	char	**spl;
	t_list	*new;
	int		nbp;

	new = NULL;
	init_g_seps();
	change_line_if_needed(&l);
	ft_printf("reline %s\n", l);
	spl = ft_strsplit_mult(l, g_seps, &nbp);
	if (!nbp)
		return (1);
	if (is_label(spl[0]))
	{
		if (nbp > 1 && !is_op_name(spl[1]) && ft_printf("POL\n"))
			return (0);
		if (nbp > 1)
		{
			if (!(new = alloc_line(spl, spl[0], nbp)) && ft_printf("PUL\n"))
				return (0);
			ft_lstpushback(g_lines, new);
		}
		else
		{
			LASTC(spl[0]) = 0;
			LAST_LABEL = spl[0];
		}
	}
	else if (is_op_name(spl[0]))
	{
		if (!is_op_name(spl[0]) && ft_printf("PTL\n"))
			return (0);
		if (!(new = alloc_line(spl, 0, nbp)) && ft_printf("PPL\n"))
			return (0);
		ft_lstpushback(g_lines, new);
	}
	write(1, "PYL\n", 4);
	return (1);
}
