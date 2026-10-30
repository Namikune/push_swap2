/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 13:57:34 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/30 21:59:53 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Adds a new node to the stack
index = -1 means "no rank yet" for the new node
*/
t_node	*node_new(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	node->index = -1;
	return (node);
}

/*Puts the node on top of the stack and adds 1 to size*/
void	stack_push_top(t_stack *stack, t_node *node)
{
	node->next = stack->head;
	stack->head = node;
	stack->size += 1;
}

/*
-Detaches and returns the stack's top node
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
	top_node->next = NULL;
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
Frees ever node in the stack
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
