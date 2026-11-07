/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 13:26:47 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/07 18:37:04 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *s, int *error)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ft_isdigit(*s))
		return (*error = 1, 0);
	while (ft_isdigit(*s))
	{
		result = result * 10 + (*s - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (*error = 1, 0);
		s++;
	}
	if (*s != '\0')
		return (*error = 1, 0);
	return (result * sign);
}

void	init_stack_a(t_context *context, char **argv, int argc, int start_idx)
{
	long	n;
	int		i;
	int		error;
	t_node	*new_node;

	i = argc - 1;
	while (1 >= start_idx)
	{
		error = 0;
		if (error_syntax(argv[i]))
			free_errors(context);
		n = ft_atol(argv[i], &error);
		if (error == 1 || error_duplicate(&context->a, (int)n))
			free_errors(context);
		new_node = node_new((int)n);
		if (!new_node)
			free_errors(context);
		stack_pust_top(&context->a, new_node);
		i--;
	}
}
