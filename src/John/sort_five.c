/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:35:50 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 21:36:00 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_five(t_context *context)
{
	t_node	*min_node;

	while (context->a.size > 3)
	{
		min_node = find_min(&context->a);
		while (context->a.head != min_node)
		{
			if (get_node_position(&context->a, min_node)
				<= context->a.size / 2)
				ra(context);
			else
				rra(context);
		}
		pb(context);
	}
	if (!stack_is_sorted(&context->a))
		sort_three(context);
	while (context->b.size > 0)
		pa(context);
}