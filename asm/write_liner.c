/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_liner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:06:30 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/18 15:25:16 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void	write_ocp(int fdc, t_line *line)
{
	int ocp;
	ocp = 0;
	if (g_op_tab[line->opcode - 1].mod_c)
	{
		ocp = create_ocp(line);
		write(fdc, &ocp, 1);
	}
}

static void	write_params(int fdc, t_line *line)
{
	int	i;
	unsigned int	numpar;
	int size;
	unsigned short snumpar;

	size = 0;
	i = 0;
	numpar = 0;
	while (i < line->nb_params)
	{
		if (is_reg((line->param)[i]) && (size = 1))
		{
			numpar = (unsigned int)ft_atoi((line->param)[i] + 1);
			write(fdc, &numpar, size);
		}
		else if (is_direct((line->param)[i]) && (size = (OPL(line).need_c) ?
			2 : 4))
		{
			if (size == 4)
			{
				numpar = (unsigned int)ft_atoi((line->param)[i] + 1);
				endian_swap(&numpar);
				write(fdc, &numpar, size);
			}
			if (size == 2)
			{
				snumpar = (unsigned short)ft_atoi((line->param)[i] + 1);
				short_endian_swap(&snumpar);
				write(fdc, &snumpar, size);
			}
		}
		else if (is_indirect((line->param)[i]) && (size = 2))
		{
			snumpar = (unsigned short)ft_atoi((line->param)[i]);
			short_endian_swap(&snumpar);
			write(fdc, &snumpar, size);
		}
		i++;
	}
}

void		write_line(int fdc, t_line *line)
{
	int i;
	int opcode;

	i = 0;
	opcode = line->opcode;
	write(fdc, &opcode, 1);
	write_ocp(fdc, line);
	write_params(fdc, line);
}
