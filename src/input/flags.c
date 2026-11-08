/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 14:37:42 by hadinh            #+#    #+#             */
/*   Updated: 2026/11/08 16:36:10 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	parse_flags(int argc, char *argv[], t_context *context)
{
	t_config	*config;
	int			i;

	config = &context->config;
	i = 1;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "--adaptive", 11) == 0)
			config->strategy = ADAPTIVE;
		else if (ft_strncmp(argv[i], "--simple", 9) == 0)
			config->strategy = SIMPLE;
		else if (ft_strncmp(argv[i], "--medium", 9) == 0)
			config->strategy = MEDIUM;
		else if (ft_strncmp(argv[i], "--complex", 10) == 0)
			config->strategy = COMPLEX;
		else if (ft_strncmp(argv[i], "--bench", 8) == 0)
			config->bench = 1;
		else if (ft_strncmp(argv[i], "--", 2) == 0)
			free_errors(context);
		i++;
	}
}
