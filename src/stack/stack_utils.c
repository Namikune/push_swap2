/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 21:53:20 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/07 14:20:20 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
Returns 1 if stack is sorted.
Returns 1 if stack is empty.
Returns 0 if not sorted
*/
int	stack_is_sorted(t_stack *stack)
{
	t_node	*node;
	t_node	*next_node;

	if (!stack->head)
		return (1);
	node = stack->head;
	next_node = node->next;
	while (next_node != NULL)
	{
		if (next_node->value >= node->value)
		{
			node = next_node;
			next_node = next_node->next;
		}
		else
			return (0);
	}
	return (1);
}
