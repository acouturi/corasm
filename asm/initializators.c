/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:56:08 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/18 16:21:39 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

t_corewar	init_g_corewar(void)
{
	t_corewar ret;

	ret.nb_lines = 0;
	ret.code_len = 0;
	ret.last_label = 0;
	return (ret);
}

void		init_g_seps(void)
{
	g_seps[0] = ' ';
	g_seps[1] = '\t';
	g_seps[2] = SEPARATOR_CHAR;
}

t_error		*init_g_d_errors(void)
{
	static t_error *init = NULL;

	if (!(init = (t_error*)malloc(sizeof(t_error))))
		return (0);
	init->lastmsgerror = 0;
	init->nberror = 0;
	init->read_lines = 0;
	return (init);
}

t_line		*edit_line(char **spl, char *label, t_line *line)
{
	if (label)
		LASTC(label) = 0;
	line->label = label;
	line->opcode = 0;
	if (nbp > 1)
		line->opcode = fetch_opcode((label) ? spl[1] : spl[0]);
	line->len = 0;
	line->len_tot = 0;
	line->addr = 0;
	line->nb_params = 0;
	return (line);
}

t_list		*alloc_line(char **spl, char *label, int nbp)
{
	t_line *line;
	t_list *newlist;

	if (!(line = (t_line*)malloc(sizeof(t_line))))
		return (0);
	if (!(newlist = (t_list*)malloc(sizeof(t_list)))
	&& (ft_memdelbool((void**)&line)))
		return (0);
	line = edit_line(spl, label, line);
	if (nbp > 1)
		line->nb_params = (label) ? nbp - 2 : nbp - 1;
	line->param = NULL;
	if (nbp > 1)
		line->param = (label) ? &(spl[2]) : &(spl[1]);
	newlist->next = NULL;
	newlist->content = line;
	newlist->content_size = 2;
	if (line->nb_params && !check_params(line))
		return (0);
	calc_len(line);
	return (newlist);
}
