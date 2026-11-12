/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:18:48 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/12 11:52:31 by johtadro         ###   ########.fr       */
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

void	rank_numbers(t_stack *stack)
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

t_node	*find_min(t_stack *stack)
{
	t_node	*current;
	t_node	*min_node;

	if(!stack || !stack->head)
		return (NULL);
	current = stack->head;
	min_node = current;
	while(current)
	{
		if (current->value < min_node->value)
			min_node = current;
		current = current->next;
	}
	return (min_node);
}

int	get_node_position(t_stack *stack, t_node *target)
{
	t_node	*current;
	int		pos;
	
	pos = 0;
	current = stack->head;
	while (current && current != target)
	{
		pos++;
		current = current->next;
	}
	return (pos);
}

t_node	*find_max(t_stack *stack)
{
	t_node	*current;
	t_node	*max_node;

	if (!stack || !stack->head)
		return (NULL);
	current = stack->head;
	max_node = current;
	while (current)
	{
		if (current->value > max_node->value)
			max_node = current;
		current = current->next;
	}
	return (max_node);
}