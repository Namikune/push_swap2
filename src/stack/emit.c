/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:40:24 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/21 17:16:01 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*operation_name(t_operation operation)
{
	if (operation == OP_SA)
		return ("sa");
	if (operation == OP_SB)
		return ("sb");
	if (operation == OP_SS)
		return ("ss");
	if (operation == OP_PA)
		return ("pa");
	if (operation == OP_PB)
		return ("pb");
	if (operation == OP_RA)
		return ("ra");
	if (operation == OP_RB)
		return ("rb");
	if (operation == OP_RR)
		return ("rr");
	if (operation == OP_RRA)
		return ("rra");
	if (operation == OP_RRB)
		return ("rrb");
	if (operation == OP_RRR)
		return ("rrr");
	return ("");
}

void	emit(t_operation operation, t_context *context)
{
	context->stats.ops[operation] += 1;
	context->stats.total += 1;
	ft_putendl_fd(operation_name(operation), 1);
}
