/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:33:41 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/08 16:14:04 by hadinh           ###   ########.fr       */
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
	t_config	config;
	t_stats		stats;
}	t_context;

/*John's*/
int			error_syntax(char *str);
int			error_duplicate(t_stack *a, int n);
void		free_errors(t_context *context);
t_node		*find_max(t_stack *stack);
void		sort_three(t_context *context);
static int	ft_isdigit(int c);
long		ft_atol(const char *s, int *error);
void		init_stack_a(t_context *context, char **argv, int argc, int start_idx);
/*Emit*/
void		emit(t_operation operation, t_context *context);
/*Index*/
void		rank_numbers(t_stack *stack);
/*Stack - Utils*/
t_node		*node_new(int value);
void		stack_push_top(t_stack *stack, t_node *node);
t_node		*stack_pop_top(t_stack *stack);
t_node		*stack_last(t_stack *stack);
void		stack_free(t_stack *stack);
int			stack_is_sorted(t_stack *stack);
int			swap_top(t_stack *stack);
/*Stack - Swap operations*/
void		sa(t_context *context);
void		sb(t_context *context);
void		ss(t_context *context);
/*Stack - Pushing operations*/
int			push_top(t_stack *from, t_stack *to);
void		pa(t_context *context);
void		pb(t_context *context);
/*Stack - Rotations*/
int			rotate_top(t_stack *stack);
void		ra(t_context *context);
void		rb(t_context *context);
void		rr(t_context *context);
/*Stack - Reverse Rotations*/
int			rrotate_top(t_stack *stack);
void		rra(t_context *context);
void		rrb(t_context *context);
void		rrr(t_context *context);

#endif
