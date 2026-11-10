/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 19:53:29 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/10 22:40:15 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*A static helper that prints disorder text to stdder*/
static void	print_disorder(long disorder)
{
	int	disorder_value;
	int	disorder_remainder;

	disorder_value = disorder / 100;
	disorder_remainder = disorder % 100;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(disorder_value, 2);
	ft_putchar_fd('.', 2);
	if (disorder_remainder < 10)
		ft_putnbr_fd(0, 2);
	ft_putnbr_fd(disorder_remainder, 2);
	ft_putchar_fd('%', 2);
	ft_putendl_fd("", 2);
}

/*
Prints the strategy to stderr
-adaptive: prefix "Adaptive -> ", then the picked strategy
-forced: only the strategy that ran (chosen_strategy)
*/
static void	print_strategy(t_context *context)
{
	ft_putstr_fd("[bench] Strategy: ", 2);
	if (context->config.strategy == ADAPTIVE)
		ft_putstr_fd("Adaptive -> ", 2);
	if (context->config.chosen_strategy == SIMPLE)
		ft_putstr_fd("Simple / O(n²)", 2);
	if (context->config.chosen_strategy == MEDIUM)
		ft_putstr_fd("Medium / O(n√n)", 2);
	if (context->config.chosen_strategy == COMPLEX)
		ft_putstr_fd("Complex / O(n log n)", 2);
	ft_putendl_fd("", 2);
}

/*Prints the total number of operations to stderr*/
static void	print_total(t_context *context)
{
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(context->stats.total, 2);
	ft_putendl_fd("", 2);
}

/*
Prints the count of every operation to stderr
-loops over the 11 slots of stats.ops
-operation_name (emit.c) gives the text for each slot
*/
static void	print_ops(t_context *context)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		ft_putstr_fd("[bench] ", 2);
		ft_putstr_fd(operation_name(i), 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(context->stats.ops[i], 2);
		ft_putendl_fd("", 2);
		i++;
	}
}

/*
Puts it all together:
-Disorder
-Strategy
-Total
-Operations
*/
void	bench(t_context *context)
{
	print_disorder(context->stats.disorder_value);
	print_strategy(context);
	print_total(context);
	print_ops(context);
}
