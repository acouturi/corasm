/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:51:35 by fsabatie          #+#    #+#             */
<<<<<<< HEAD:libft/list_functions/ft_lstappend.c
/*   Updated: 2018/04/15 22:48:45 by vlay             ###   ########.fr       */
=======
/*   Updated: 2018/04/07 21:49:50 by dsaadia          ###   ########.fr       */
>>>>>>> origin/asm_code_part:libft/list_functions/ft_lstpushback.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Ajoute l’élément new en fin de liste.
*/

void	ft_lstappend(t_list **alst, t_list *new)
{
<<<<<<< HEAD:libft/list_functions/ft_lstappend.c
	t_list	*tmp;

	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
=======
	if (!start)
	{
		start = new;
		return ;
	}
	while (start->next != NULL)
		start = start->next;
	start->next = new;
>>>>>>> origin/asm_code_part:libft/list_functions/ft_lstpushback.c
}
