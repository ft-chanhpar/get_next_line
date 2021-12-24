/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:36:23 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/24 16:39:45 by chanhpar         ###   ########.fr       */
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

	read(fd, str, 5);
	printf("%s", str);
	return (0);
}
