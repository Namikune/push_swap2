/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 17:48:05 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/08 12:31:26 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*find_min(t_stack *stack)
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

static int	get_node_position(t_stack *stack, t_node *target)
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