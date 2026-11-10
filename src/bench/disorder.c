/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 18:13:00 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/10 22:09:15 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* A static helper that counts the "mistakes" */
static int	mistakes_count(t_context	*context)
{
	t_node	*start;
	t_node	*next;
	int		i;

	start = context->a.head;
	i = 0;
	while (start->next != NULL)
	{
		next = start->next;
		while (next != NULL)
		{
			if (start->value > next->value)
				i++;
			next = next->next;
		}
		start = start->next;
	}
	return (i);
}

/*
Calculates disorder via its formula:
Disorder  =  mistakes × 10,000 / total pairs
Times 10,000 to turn it into an int for bench to print properly
*/
long	disorder(t_context	*context)
{
	long	size;
	long	result;
	long	mistakes;

	if (context->a.size < 2)
		return (0);
	size = context->a.size;
	mistakes = mistakes_count(context);
	result = ((mistakes * 10000) / (((size * (size - 1)) / 2)));
	return (result);
}
