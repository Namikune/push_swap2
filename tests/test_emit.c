/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_emit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 16:12:37 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/21 17:15:54 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* TEST COMMAND

make -C libft
cc -Wall -Wextra -Werror -I include -I libft tests/test_emit.c src/stack/emit.c libft/libft.a -o test_emit
./test_emit

*/
#include "push_swap.h"

int	main(void)
{
	t_context	ctx;
	size_t		i;

	ft_bzero(&ctx, sizeof(ctx));

	i = 0;
	while (i < 11)
	{
		emit(i, &ctx);
		ft_putnbr_fd(ctx.stats.ops[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_putnbr_fd(ctx.stats.total, 1);
	ft_putchar_fd('\n', 1);

	return (0);
}
