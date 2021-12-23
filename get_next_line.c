/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/24 01:18:45 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	**str;
	char		*rst;
	ssize_t		cnt;
	ssize_t		len;

	if (fd < 0)
		return (NULL);
	rst = (char **)malloc(sizeof(char *));
	cnt = read(fd, *rst, BUFFER_SIZE);
	len = 0;
	while ((*rst)[len] != '\n' && (*rst)[len] != '\0')
		len++;
	return (rst);
}
