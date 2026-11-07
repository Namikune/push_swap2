/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rrorate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:56:08 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/07 15:06:27 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
SILENT CORE
Rotates the bottom node to the top
Returns 1, 0 if size is less than 2
*/
int	rrotate_top(t_stack *stack)
{
	t_node	*top_node;
	t_node	*prev_bottom;
	t_node	*bottom_node;

	if (stack->size < 2)
		return (0);
	top_node = stack->head;
	bottom_node = stack_last(stack);
	prev_bottom = bottom_node->prev;
	bottom_node->next = top_node;
	prev_bottom->next = NULL;
	stack->head = bottom_node;
	top_node->prev = bottom_node;
	bottom_node->prev = NULL;
	return (1);
}

void	rra(t_context *context)
{
	t_stack	*a;

	a = &context->a;
	if (rrotate_top(a) == 1)
		emit(OP_RRA, context);
}

void	rrb(t_context *context)
{
	t_stack	*b;

	b = &context->b;
	if (rrotate_top(b) == 1)
		emit(OP_RRB, context);
}

/*Prints if at least one stack rrotated*/
void	rrr(t_context *context)
{
	t_stack	*a;
	t_stack	*b;
	int		rrotate_checker_a;
	int		rrotate_checker_b;

	a = &context->a;
	b = &context->b;
	rrotate_checker_a = rrotate_top(a);
	rrotate_checker_b = rrotate_top(b);
	if ((rrotate_checker_a == 1) || (rrotate_checker_b == 1))
		emit(OP_RRR, context);
}
