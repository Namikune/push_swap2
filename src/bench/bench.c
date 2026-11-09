/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 19:53:29 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/09 20:55:14 by hadinh           ###   ########.fr       */
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

static void	print_startegy(t_strategy strategy)
{
	ft_putstr_fd("[bench] Strategy: ", 2);
	if (strategy == ADAPTIVE)
		ft_putstr_fd("Adaptive / O(n√n", 2);
	if (strategy == SIMPLE)
		ft_putstr_fd("Simple / O(n²)", 2);
	if (strategy == MEDIUM)
		ft_putstr_fd("Medium / O(n√n)", 2);
	if (strategy == COMPLEX)
		ft_putstr_fd("Complex / O(n log n)", 2);
	ft_putendl_fd("", 2);
}


void	bench(t_context *context)
{

}
