/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:40:28 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/12 12:27:10 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_context(t_context *context)
{
	int	i;
	
	context->a.head = NULL;
	context->a.size = 0;
	context->b.head = NULL;
	context->b.size = 0;
	context->cofig.strategy = ADAPTIVE;
	context->cofig.bench = 0;
	context->stats.total = 0;
	i = 0;
	while (i < 11)
		context->stats.ops[i++] = 0;
}

void	free_split(char **split_arr)
{
	int	i;

	i = 0;
	if (!split_arr)
		return ;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

static char	**get_args(int argc, char **argv, int *allocated, int *start_idx)
{
	char	**args;

	*allocated = 0;
	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		*allocated = 1;
		*start_idx = 0;
	}
	else
	{
		args = argv;
		*start_idx = 1;
		if (ft_strncmp(args[1], "--", 2) == 0)
			*start_idx = 2;
	}
	return (args);
}

static void	dispatch_sort(t_context *context)
{
	if (stack_is_sorted(&context->a))
		return ;
	if (context->a.size == 2)
		sa(context);
	else if (context->a.size == 3)
		sort_three(context);
	else
	{
		medium_sort(context);
	}
}

int	main(int argc, char **argv)
{
	t_context	context;
	char		**args;
	int			is_allocated;
	int			start_idx;

	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	init_context(&context);
	args = get_args(argc, argv, &is_allocated, &start_idx);
	init_stack_a(&context, args, start_idx);
	if (is_allocated)
		free_split(args);
	dispatch_sort(&context);
	stack_free(&context.a);
	return (0);
}