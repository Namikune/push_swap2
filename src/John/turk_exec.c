/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 14:16:43 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 14:36:38 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_a_to_top(t_context *context, t_node *node)
{
	while (context->a.head != node)
	{
		if (get_node_position(&context->a, node) <= context->a.size / 2)
			ra(context);
		else
			rra(context);
	}
}

static void	rotate_b_to_top(t_context *context, t_node *node)
{
	while (context->b.head != node)
	{
		if (get_node_position(&context->b, node) <= context->b.size / 2)
			rb(context);
		else
			rrb(context);
	}
}

void	push_cheapest_to_b(t_context *context)
{
	t_node	*cheap;
	int		pos_a;
	int		pos_b;

	cheap = context->a.head;
	while (cheap && !cheap->cheapest)
		cheap = cheap->next;
	pos_a = get_node_position(&context->a, cheap);
	pos_b = get_node_position(&context->b, cheap->target_node);
	if (pos_a <= context->a.size / 2 && pos_b <= context->b.size / 2)
	{
		while (context->a.head != cheap
			&& context->b.head != cheap->target_node)
			rr(context);
	}
	else if (pos_a > context->a.size / 2 && pos_b > context->b.size / 2)
	{
		while (context->a.head != cheap
			&& context->b.head != cheap->target_node)
			rrr(context);
	}
	rotate_a_to_top(context, cheap);
	rotate_b_to_top(context, cheap->target_node);
	pb(context);
}
