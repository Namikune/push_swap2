/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 11:21:48 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/12 11:58:49 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_chunk_size(int size)
{
	if (size < 100)
		return (15);
	else if (size <= 250)
		return (25);
	else
		return (35);
}

static void	push_chunks_to_b(t_context *context, int chunk_size)
{
	int	i;
	
	i = 0;
	while (context->a.size > 0)
	{
		if (context->a.head->index <= i)
		{
			pb(context);
			rb(context);
			i++;
		}
		else if (context->a.head->index <= i + chunk_size)
		{
			pb(context);
			i++;
		}
		else
			ra(context);
	}
}

static void	push_back_to_a(t_context *context)
{
	t_node	*max_node;
	int		pos;
	
	while (context->b.head != NULL)
	{
		max_node = find_max(&context->b);
		pos = get_node_position(&context->b, max_node);
		while(context->b.head != max_node)
		{
			if (pos <= (context->b.size / 2))
				rb(context);
			else
				rrb(context);
		}
		pa (context);
	}
}

void	medium_sort(t_context	*context)
{
	int	chunk_size;

	rank_numbers(&context->a);
	chunk_size = get_chunk_size(context->a.size);
	push_chunks_to_b(context, chunk_size);
	push_back_to_a(context);
}