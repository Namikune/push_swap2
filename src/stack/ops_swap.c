/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:49:42 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/06 17:46:20 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*If stack has atleast 2 nodes, swap the top two*/
int	swap_top(t_stack *stack)
{
	t_node	*node_a;
	t_node	*node_b;
	t_node	*node_c;

	if (stack->size < 2)
		return (0);
	node_a = stack->head;
	node_b = node_a->next;
	node_c = node_b->next;
	node_a->prev = node_b;
	node_b->next = node_a;
	stack->head = node_b;
	node_b->prev = NULL;
	if (stack->size > 2)
	{
		node_a->next = node_c;
		node_c->prev = node_a;
	}
	else
		node_a->next = NULL;
	return (1);
}

void	sa(t_context *context)
{
	t_stack	*a;

	a = &context->a;
	if (swap_top(a) == 1)
		emit(OP_SA, context);
}

void	sb(t_context *context)
{
	t_stack	*b;

	b = &context->b;
	if (swap_top(b) == 1)
		emit(OP_SB, context);
}

void	ss(t_context *context)
{
	t_stack	*a;
	t_stack	*b;
	int		swap_checker_a;
	int		swap_checker_b;

	a = &context->a;
	b = &context->b;
	swap_checker_a = swap_top(a);
	swap_checker_b = swap_top(b);
	if ((swap_checker_a == 1) || (swap_checker_b == 1))
		emit(OP_SS, context);
}
