/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 16:37:39 by nami              #+#    #+#             */
/*   Updated: 2026/09/30 14:14:53 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_length;
	size_t	i;
	char	*arr;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
	{
		len = 0;
	}
	else if (len > s_length - start)
		len = s_length - start;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
