/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 17:43:38 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/12 11:52:25 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
