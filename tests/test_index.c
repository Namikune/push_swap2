/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadinh <hadinh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 15:08:48 by hadinh            #+#    #+#             */
/*   Updated: 2026/10/22 15:49:19 by hadinh           ###   ########.fr       */
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
	t_node	node4;

	ft_bzero(&test_stack, sizeof(test_stack));

	test_stack.size = 4;

	test_stack.head = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;

	node1.value = 70;
	node2.value = -50;
	node3.value = 10;
	node4.value = -5;

	node1.index = -1;
	node2.index = -1;
	node3.index = -1;
	node4.index = -1;

	assign_index(&test_stack);

	printf("%d\n", node1.index);
	printf("%d\n", node2.index);
	printf("%d\n", node3.index);
	printf("%d\n", node4.index);
	return (0);
}
