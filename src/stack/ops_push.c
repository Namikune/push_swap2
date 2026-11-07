/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:44:56 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/07 15:00:26 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
SILENT CORE
If source stack is not empty, push the top node to destination stack
*/
int	push_top(t_stack *from, t_stack *to)
{
	t_node	*node;

	if (from->head == NULL)
		return (0);
	node = stack_pop_top(from);
	stack_push_top(to, node);
	return (1);
}

void	pa(t_context *context)
{
	t_stack	*a;
	t_stack	*b;

	a = &context->a;
	b = &context->b;
	if (push_top(b, a) == 1)
		emit(OP_PA, context);
}

void	pb(t_context *context)
{
	t_stack	*a;
	t_stack	*b;

	a = &context->a;
	b = &context->b;
	if (push_top(a, b) == 1)
		emit(OP_PB, context);
}
