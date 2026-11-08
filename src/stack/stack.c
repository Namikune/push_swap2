/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 13:57:34 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/08 12:27:17 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Creates a new node
index = -1 means "no rank yet"
The Turk fields start at zero, false or NULL
*/
t_node	*node_new(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = -1;
	node->push_cost = 0;
	node->above_median = false;
	node->cheapest = false;
	node->target_node = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/*
Puts the node on top of the stack and adds 1 to size
The old top (if there is one) now has the new node above it
*/
void	stack_push_top(t_stack *stack, t_node *node)
{
	node->prev = NULL;
	node->next = stack->head;
	if (stack->head != NULL)
		stack->head->prev = node;
	stack->head = node;
	stack->size += 1;
}

/*
-Detaches and returns the stack's top node
-The new top has no node above it anymore
-Subtracts 1 from size
-Returns NULL if stack is empty
*/
t_node	*stack_pop_top(t_stack *stack)
{
	t_node	*top_node;

	if (stack->head == NULL)
		return (NULL);
	top_node = stack->head;
	stack->head = top_node->next;
	if (stack->head != NULL)
		stack->head->prev = NULL;
	top_node->next = NULL;
	top_node->prev = NULL;
	stack->size -= 1;
	return (top_node);
}

/*
-Returns the stack's bottom node
-Returns NULL if stack is empty
*/
t_node	*stack_last(t_stack *stack)
{
	t_node	*last_node;

	if (!stack)
		return (NULL);

	last_node = stack->head;
	if (last_node == NULL)
		return (NULL);
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}
	return (last_node);
}

/*
Frees every node in the stack
Sets stack's size to zero
*/
void	stack_free(t_stack *stack)
{
	t_node	*node;

	node = stack->head;
	while (stack->head != NULL)
	{
		node = node->next;
		free(stack->head);
		stack->head = node;
	}
	stack->size = 0;
}
