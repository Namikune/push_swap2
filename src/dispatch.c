/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 22:44:44 by nami              #+#    #+#             */
/*   Updated: 2026/11/10 22:28:22 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
A helper that picks the strategy based on disorder-value
TWEAK THE DISORDER BORDERS DEPENDING ON PERFORMANCE!!!
*/
static void	disorder_picked_strategy(t_context *context)
{
	long		disorder_value;

	disorder_value = context->stats.disorder_value;
	if (disorder_value < 1000)
		context->config.chosen_strategy = SIMPLE;
	else if (disorder_value < 5000)
		context->config.chosen_strategy = MEDIUM;
	else
		context->config.chosen_strategy = COMPLEX;
}

/*Chooses the sort that is saved in config*/
static void	choose_sort(t_context *context)
{
	if (context->config.chosen_strategy == SIMPLE)
		simple_sort(context);
	else if (context->config.chosen_strategy == MEDIUM)
		simple_sort(context);
	else if (context->config.chosen_strategy == COMPLEX)
		simple_sort(context);
}

/*
Runs the strategy:
-if sorted, returns nothing (0 or 1 number)
-if 2 numbers, swap a (sa)
-if 3 numbers: sort_three()
-if 4 or more, decides with context's chosen strategy
*/
void	dispatch_sort(t_context *context)
{
	t_stack		*a;
	t_strategy	strategy;

	a = &context->a;
	strategy = context->config.strategy;
	context->stats.disorder_value = disorder(context);
	context->config.chosen_strategy = SIMPLE; //This is here for bench to print simple for simple algos, remove if we dont want it
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
		disorder_picked_strategy(context);
	else
		context->config.chosen_strategy = strategy;
	choose_sort(context);
}
