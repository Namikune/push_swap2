/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:23:05 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 15:18:31 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_b_to_a_target(t_context *context)
{
	t_node	*target;

	target = context->b.head->target_node;
	while (context->a.head != target)
	{
		if (get_node_position(&context->a, target) <= context->a.size / 2)
			ra(context);
		else
			rra(context);
	}
	pa(context);
}

static void	final_alignment(t_context *context)
{
	t_node	*min_node;

	min_node = find_min(&context->a);
	while (context->a.head != min_node)
	{
		if (get_node_position(&context->a, min_node) <= context->a.size / 2)
			ra(context);
		else
			rra(context);
	}
}

void	complex_sort(t_context *context)
{
	rank_numbers(&context->a);
	if (context->a.size > 3 && !stack_is_sorted(&context->a))
		pb(context);
	if (context->a.size > 3 && !stack_is_sorted(&context->a))
		pb(context);
	while (context->a.size > 3 && !stack_is_sorted(&context->a))
	{
		set_target_a_to_b(&context->a, &context->b);
		calculate_costs(&context->a, &context->b);
		set_cheapest(&context->a);
		push_cheapest_to_b(context);
	}
	if (!stack_is_sorted(&context->a))
		sort_three(context);
	while (context->b.size > 0)
	{
		set_target_b_to_a(&context->b, &context->a);
		push_b_to_a_target(context);
	}
	final_alignment(context);
}
