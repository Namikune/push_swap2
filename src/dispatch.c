/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nami <nami@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 22:44:44 by nami              #+#    #+#             */
/*   Updated: 2026/11/08 23:21:15 by nami             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Runs the strategy:
-if sorted, returns nothing (0 or 1 number)
-if 2 numbers, swap a (sa)
-if 3 numbers: sort_three()
-if 4 or more, decides with context's chosen strategy
*/
void	run_strategy(t_context *context)
{
	t_stack		*a;
	t_strategy	strategy;

	a = &context->a;
	strategy = context->config.strategy;
	if (stack_is_sorted(a) == 1)
		return ;
	if (a->size == 2)
	{
		sa(context);
		return ;
	}
	if (a->size == 3)
	{
		sort_three(context);
		return ;
	}
	if (strategy == ADAPTIVE)
		//SORT YET NOT IMPLEMENTED;
		simple_sort(context);
	if (strategy == SIMPLE)
		simple_sort(context);
	if (strategy == MEDIUM)
		//SORT YET NOT IMPLEMENTED;
		simple_sort(context);
	if (strategy == COMPLEX)
		//SORT YET NOT IMPLEMENTED;
		simple_sort(context);
}
