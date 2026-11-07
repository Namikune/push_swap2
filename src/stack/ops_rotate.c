/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:22:12 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/07 15:00:11 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
SILENT CORE
Rotates the top node to the bottom
Returns 1, 0 if size is less than 2
*/
int	rotate_top(t_stack *stack)
{
	t_node	*top_node;
	t_node	*next;
	t_node	*bottom_node;

	if (stack->size < 2)
		return (0);
	top_node = stack->head;
	next = top_node->next;
	bottom_node = stack_last(stack);
	top_node->prev = bottom_node;
	bottom_node->next = top_node;
	top_node->next = NULL;
	stack->head = next;
	next->prev = NULL;
	return (1);
}

void	ra(t_context *context)
{
	t_stack	*a;

	a = &context->a;
	if (rotate_top(a) == 1)
		emit(OP_RA, context);
}

void	rb(t_context *context)
{
	t_stack	*b;

	b = &context->b;
	if (rotate_top(b) == 1)
		emit(OP_RB, context);
}

/*Prints if at least one stack rotated*/
void	rr(t_context *context)
{
	t_stack	*a;
	t_stack	*b;
	int		rotate_checker_a;
	int		rotate_checker_b;

	a = &context->a;
	b = &context->b;
	rotate_checker_a = rotate_top(a);
	rotate_checker_b = rotate_top(b);
	if ((rotate_checker_a == 1) || (rotate_checker_b == 1))
		emit(OP_RR, context);
}
