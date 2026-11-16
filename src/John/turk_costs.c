/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_costs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 13:49:25 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 14:59:37 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	calculate_costs(t_stack *a, t_stack *b)
{
	t_node	*curr;
	int		pos_a;
	int		pos_b;

	curr = a->head;
	while (curr)
	{
		pos_a = get_node_position(a, curr);
		if (pos_a > a->size / 2)
			pos_a -= a->size;
		pos_b = get_node_position(b, curr->target_node);
		if (pos_b > b->size / 2)
			pos_b -= b->size;
		if ((pos_a >= 0 && pos_b >= 0) || (pos_a < 0 && pos_b < 0))
			curr->push_cost = get_max(ft_abs(pos_a), ft_abs(pos_b));
		else
			curr->push_cost = ft_abs(pos_a) + ft_abs(pos_b);
		curr = curr->next;
	}
}

void	set_cheapest(t_stack *a)
{
	long	min_cost;
	t_node	*curr;
	t_node	*cheapest_node;

	min_cost = LONG_MAX;
	cheapest_node = NULL;
	curr = a->head;
	while (curr)
	{
		curr->cheapest = false;
		if (curr->push_cost <= min_cost)
		{
			min_cost = curr->push_cost;
			cheapest_node = curr;
		}
		curr = curr->next;
	}
	if (cheapest_node)
		cheapest_node->cheapest = true;
}
