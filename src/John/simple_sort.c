/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:48:05 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/12 11:51:53 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	simple_sort(t_context *context)
{
	t_node	*min_node;
	int		pos;

	while(context->a.size > 3)
	{
		min_node = find_min(&context->a);
		pos = get_node_position(&context->a, min_node);
		while (context->a.head != min_node)
		{
			if (pos <= (context->a.size / 2))
				ra(context);
			else
				rra(context);
		}
		pb(context);
	}
	if (context->a.size == 3)
		sort_three(context);
	while(context->b.head != NULL)
		pa(context);
}