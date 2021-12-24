/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:36:23 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/25 02:21:30 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd = open("sample", O_RDONLY);
	char	str[10];

	read(fd, str, 10);
	printf("%s", str);
	char	*arr;

	arr = NULL;
	if (arr == NULL || *arr == 'a')
		printf("wow");
	return (0);
}
