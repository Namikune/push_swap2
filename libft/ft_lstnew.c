/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 20:45:02 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/01 15:55:55 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*space;

	space = malloc(sizeof(t_list));
	if (!space)
		return (NULL);
	space->content = content;
	space->next = NULL;
	return (space);
}
