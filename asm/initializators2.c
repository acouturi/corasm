/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializators2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:42:21 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/18 16:24:05 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

char		*reinit_direct(char **dir, int addrnb, int addrline)
{
	char	*addrstr;
	int		i;

	i = -1;
	if (addrnb < addrline)
		addrnb = 65536 - (addrline - addrnb);
	else
		addrnb = addrnb - addrline;
	addrstr = ft_itoa(addrnb);
	if (!(*dir = (char*)malloc(ft_strlen(addrstr) + 2)))
		return (0);
	(*dir)[0] = '%';
	while (++i < (int)ft_strlen(addrstr))
		(*dir)[i + 1] = addrstr[i];
	(*dir)[i + 1] = 0;
	return (*dir);
}

char		*reinit_indirect(char **ind, int addrnb, int addrline)
{
	char	*addrstr;
	int		i;

	i = -1;
	if (addrnb < addrline)
		addrnb = 65536 - (addrline - addrnb);
	else
		addrnb = addrnb - addrline;
	addrstr = ft_itoa(addrnb);
	if (!(*ind = (char*)malloc(ft_strlen(addrstr) + 1)))
		return (0);
	while (++i < (int)ft_strlen(addrstr))
		(*ind)[i] = addrstr[i];
	(*ind)[i] = 0;
	return (*ind);
}

int			init_len_code(void)
{
	t_list	*surf;
	t_list	*new;
	int		cl;

	surf = g_lines;
	while (surf->next)
		surf = surf->next;
	CODE_LEN = LINECONT(surf)->len_tot;
	cl = CODE_LEN;
	surf = g_lines;
	surf = g_lines->next;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (0);
	new->content = &cl;
	new->content_size = 4;
	new->next = surf->next;
	surf->next = new;
	return (1);
}

t_op		*init_g_op_tab(void)
{
	static t_op op_tab[17] = {
		{"live", 1, {T_DIR}, 1, 10, "", 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "", 1, 0},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "", 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "", 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "", 1, 0},
		{"and", 3, {T_ALL, T_ALL, T_REG}, 6, 6, "", 1, 0},
		{"or", 3, {T_ALL, T_ALL, T_REG}, 7, 6, "", 1, 0},
		{"xor", 3, {T_ALL, T_ALL, T_REG}, 8, 6, "", 1, 0},
		{"zjmp", 1, {T_DIR}, 9, 20, "", 0, 1},
		{"ldi", 3, {T_ALL, T_DIR | T_REG, T_REG}, 10, 25, "", 1, 1},
		{"sti", 3, {T_REG, T_ALL, T_DIR | T_REG}, 11, 25, "", 1, 1},
		{"fork", 1, {T_DIR}, 12, 800, "", 0, 1},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "", 1, 0},
		{"lldi", 3, {T_ALL, T_DIR | T_REG, T_REG}, 14, 50, "", 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "", 0, 1},
		{"aff", 1, {T_REG}, 16, 2, "", 1, 0},
		{0, 0, {0}, 0, 0, 0, 0, 0}
	};

	return (op_tab);
}
