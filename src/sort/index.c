/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:18:48 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/22 15:49:35 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	smaller_nodes_count(t_stack *stack, t_node *node)
{
	int		count;
	t_node	*start;

	start = stack->head;
	count = 0;
	while (start != NULL)
	{
		if (start->value < node->value)
			count++;
		start = start->next;
	}
	return (count);
}

void	assign_index(t_stack *stack)
{
	t_node	*node;
	int		node_index;

	node = stack->head;
	while (node != NULL)
	{
		node_index = smaller_nodes_count(stack, node);
		node->index = node_index;
		node = node->next;
	}
}
