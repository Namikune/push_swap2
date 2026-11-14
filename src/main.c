/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:40:28 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 21:57:33 by johtadro         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_context	context;
	char		**args;

	if (argc == 1)
		return (0);
	init_context(&context);
	parse_flags(argc, argv, &context);
	args = normalize_args(argv);
	if (!args)
		free_errors(&context);
	if (!init_stack_a(&context, args, 0))
	{
		free_split(args);
		free_errors(&context);
	}
	free_split(args);
	dispatch_sort(&context);
	if (context.config.bench == 1)
		bench(&context);
	stack_free(&context.a);
	return (0);
}
