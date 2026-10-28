/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:18:22 by nami              #+#    #+#             */
/*   Updated: 2026/09/30 14:14:00 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*p;
	unsigned char		*arr;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	p = (const unsigned char *)src;
	arr = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		arr[i] = p[i];
		i++;
	}
	return (arr);
}
