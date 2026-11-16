/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johtadro <johtadro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:56:22 by johtadro          #+#    #+#             */
/*   Updated: 2026/11/14 22:03:31 by johtadro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char **argv)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	i = 1;
	count = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "--", 2) != 0)
		{
			split = ft_split(argv[i], ' ');
			if (!split)
				return (-1);
			if (!split[0])
			{
				free_split(split);
				return (-1);
			}
			j = 0;
			while (split[j])
				j++;
			count += j;
			free_split(split);
		}
		i++;
	}
	return (count);
}

static int	append_words(char **result, char *arg, int *pos)
{
	char	**split;
	int		i;

	split = ft_split(arg, ' ');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		result[*pos] = ft_strdup(split[i]);
		if (!result[*pos])
		{
			free_split(split);
			return (0);
		}
		(*pos)++;
		i++;
	}
	free_split(split);
	return (1);
}

char	**normalize_args(char **argv)
{
	char	**result;
	int		i;
	int		pos;
	int		count;

	count = count_words(argv);
	if (count < 0)
		return (NULL);
	result = ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 1;
	pos = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "--", 2) != 0
			&& !append_words(result, argv[i], &pos))
			return (free_split(result), NULL);
		i++;
	}
	return (result);
}
