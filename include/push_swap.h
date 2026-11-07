/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:33:41 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/07 14:20:04 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <libft.h>
# include <stdbool.h>

typedef enum e_operation
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
}	t_operation;

typedef enum e_strategy
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX
}	t_strategy;

/*Added extra fields for turk sort*/
typedef struct s_node
{
	int				value;
	int				index;
	int				push_cost;
	bool			above_median;
	bool			cheapest;
	struct s_node	*target_node;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	int		size;
}	t_stack;

typedef struct s_configuration
{
	t_strategy	strategy;
	int			bench;
}	t_config;

typedef struct s_statistics
{
	int	ops[11];
	int	total;
}	t_stats;

typedef struct s_context
{
	t_stack		a;
	t_stack		b;
	t_config	cofig;
	t_stats		stats;
}	t_context;

/*Emit*/
void	emit(t_operation operation, t_context *context);
/*Index*/
void	rank_numbers(t_stack *stack);
/*Stack*/
t_node	*node_new(int value);
void	stack_push_top(t_stack *stack, t_node *node);
t_node	*stack_pop_top(t_stack *stack);
t_node	*stack_last(t_stack *stack);
void	stack_free(t_stack *stack);
int		stack_is_sorted(t_stack *stack);
int		swap_top(t_stack *stack);
/*Stack - Swap operations*/
void	sa(t_context *context);
void	sb(t_context *context);
void	ss(t_context *context);
/*Stack - Pushing operations*/
int		push_top(t_stack *from, t_stack *to);
void	pa(t_context *context);
void	pb(t_context *context);

#endif
