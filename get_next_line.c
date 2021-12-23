/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/11/21 16:42:37 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static size_t	i;
	static size_t	buff;
	static char		*c;
	ssize_t			rd;

	buff = BUFFER_SIZE;
	if (fd < 0)
		return (NULL);
	c = (char *)malloc(sizeof(char) * buff);
	rd = read(fd, &c[i], 1);
	write(1, &c[i], 1);
	write(1, "\n", 1);
	i++;
	if (rd < 0)
		return (NULL);
	return (c);
}

int	main(void)
{
	static char	*str;
	int	i = 0;

	while (i < 5)
	{
		str = get_next_line(0);
		i++;
	}
	write(1, str, 5);
	free(str);	
	return (0);
}
