/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:40:28 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/13 17:03:52 by hadinh           ###   ########.fr       */
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
	context->config.strategy = ADAPTIVE;
	context->config.bench = 0;
	context->config.chosen_strategy = ADAPTIVE;
	context->stats.total = 0;
	context->stats.disorder_value = 0;
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
	}
	return (args);
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
	parse_flags(argc, argv, &context);
	args = get_args(argc, argv, &is_allocated, &start_idx);
	init_stack_a(&context, args, start_idx);
	if (is_allocated)
		free_split(args);
	dispatch_sort(&context);
	if (context.config.bench == 1)
		bench(&context);
	stack_free(&context.a);
	return (0);
}
