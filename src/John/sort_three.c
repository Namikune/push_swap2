/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 17:43:38 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/08 12:38:20 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	sort_three(t_context *context)
{
	t_node	*biggest_node;
	t_stack	*a;

	a = &context->a;
	biggest_node = find_max(a);
	if (biggest_node == a->head)
		ra(context);
	else if (a->head->next == biggest_node)
		rra(context);
	if (a->head->value > a->head->next->value)
		sa(context);
}
