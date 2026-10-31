/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 21:53:20 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/31 17:45:28 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*This implementation is not correct, need to be updated*/
int	stack_is_sorted(t_stack *stack)
{
	t_node	*node;
	t_node	*next_node;

	if (!stack->head)
		return (NULL);
	node = stack->head;
	next_node = node->next;

	while (node != NULL)
	{
		if (next_node->value > node->value)
		{
			node = next_node;
			next_node = next_node->next;
		}
		return (0);
	}
	return (1);
}
