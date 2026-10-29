/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 15:53:28 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/29 15:54:16 by hadinh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/* TEST COMMAND
cc -Wall -Wextra -Werror -I include -I libft tests/test_index.c src/sort/index.c libft/libft.a -o test_index
./test_index
*/
int	main(void)
{
	t_stack	test_stack;
	t_node	node1;
	t_node	node2;
	t_node	node3;

	ft_bzero(&test_stack, sizeof(test_stack));

	test_stack.size = 3;

	test_stack.head = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = NULL;

	node1.value = 70;
	node2.value = -50;
	node3.value = 10;

	node1.index = -1;
	node2.index = -1;
	node3.index = -1;

	assign_index(&test_stack);

	printf("%d\n", node1.index);
	printf("%d\n", node2.index);
	printf("%d\n", node3.index);
	return (0);
}
