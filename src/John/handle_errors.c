/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 16:41:42 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/08 16:33:30 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	error_syntax(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	if (str[i] == '+' || str [i] == '-')
	{
		if (!ft_isdigit(str[i + 1]))
			return (1);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	error_duplicate(t_stack *a, int n)
{
	t_node	*current;

	if (!a || !a->head)
		return (0);
	current = a->head;
	while (current)
	{
		if (current->value == n)
			return (1);
		current = current->next;
	}
	return (0);
}

void	free_errors(t_context *context)
{
	stack_free(&context->a);
	stack_free(&context->b);
	write(2, "Error\n", 6);
	exit(1);
}
