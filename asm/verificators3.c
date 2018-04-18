/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:56:36 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/18 15:19:11 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		what_is(char *str)
{
	if (is_reg(str))
		return (1);
	if (is_direct(str))
		return (2);
	if (is_indirect(str))
		return (3);
	return (0);
}

char	*is_label_dir(char *dir)
{
	if (dir[1] != LABEL_CHAR)
		return (0);
	return (dir + 2);
}

char	*is_label_ind(char *ind)
{
	if (ind[0] != LABEL_CHAR)
		return (0);
	return (ind + 1);
}

int		is_real_label(char *str)
{
	t_list	*surf;
	int		j;

	j = 0;
	surf = g_lines;
	while (surf)
	{
		if (surf->content_size == 2)
		{
			j++;
			if (LINECONT(surf)->label && ft_strequ(LINECONT(surf)->label, str))
				return (LINECONT(surf)->addr);
		}
		surf = surf->next;
	}
	return (-1);
}

int		is_real_code(void)
{
	t_list		*surf;
	int			i;
	char		*label;
	char		*parstr;
	int			addr;

	i = 0;
	surf = g_lines;
	while (surf)
	{
		if (surf->content_size == 2)
		{
			i = 0;
			while (i < LINECONT(surf)->nb_params)
			{
				parstr = LINECONT(surf)->param[i];
				if (is_direct(parstr) && (label = is_label_dir(parstr)))
				{
					if ((addr = is_real_label(label)) == -1 &&
						ft_printf("W %s\n", parstr))
						return (0);
					LINECONT(surf)->param[i] = reinit_direct(&parstr, addr,
						LINECONT(surf)->addr);
				}
				else if (is_indirect(parstr) && (label = is_label_ind(parstr)))
				{
					if ((addr = is_real_label(label)) == -1 &&
						ft_printf("Z %s\n", parstr))
						return (0);
					LINECONT(surf)->param[i] = reinit_indirect(&parstr, addr,
						LINECONT(surf)->addr);
				}
				i++;
			}
		}
		surf = surf->next;
	}
	return (1);
}
