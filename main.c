/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2022/01/03 12:54:17 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	static char	*str;
	char		*file;
	int			i;
	int			fd;
	int			n;

	n = 3;
	file = "sample";
	i = 0;
	fd = open("file", O_RDONLY);
	while (i < n)
	{
		str = get_next_line(fd);
		if (str != NULL)
			write(1, str, ft_strlen(str));
		else
			write(1, "NULL", 4);
		free(str);
		i++;
	}
	return (0);
}
