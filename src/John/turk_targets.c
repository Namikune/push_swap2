/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_targets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:52:31 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 15:23:18 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*get_target_for_a(t_node *node_a, t_stack *b)
{
	t_node	*curr_b;
	t_node	*target;
	int		best_match;

	best_match = -1;
	target = NULL;
	curr_b = b->head;
	while (curr_b)
	{
		if (curr_b->index < node_a->index && curr_b->index > best_match)
		{
			best_match = curr_b->index;
			target = curr_b;
		}
		curr_b = curr_b->next;
	}
	if (best_match == -1)
		return (find_max(b));
	return (target);
}

void	set_target_a_to_b(t_stack *a, t_stack *b)
{
	t_node	*curr_a;

	curr_a = a->head;
	while (curr_a)
	{
		curr_a->target_node = get_target_for_a(curr_a, b);
		curr_a = curr_a->next;
	}
}

static t_node	*get_target_for_b(t_node *node_b, t_stack *a)
{
	t_node	*curr_a;
	t_node	*target;
	int		best_match;

	best_match = INT_MAX;
	target = NULL;
	curr_a = a->head;
	while (curr_a)
	{
		if (curr_a->index > node_b->index && curr_a->index < best_match)
		{
			best_match = curr_a->index;
			target = curr_a;
		}
		curr_a = curr_a->next;
	}
	if (best_match == INT_MAX)
		return (find_min(a));
	return (target);
}

void	set_target_b_to_a(t_stack *b, t_stack *a)
{
	t_node	*curr_b;

	curr_b = b->head;
	while (curr_b)
	{
		curr_b->target_node = get_target_for_b(curr_b, a);
		curr_b = curr_b->next;
	}
}
