/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/25 11:21:10 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	static char	*str;
	int			i;
	int			fd;

	i = 0;
	fd = open("sample", O_RDONLY);
	while (i < 12)
	{
		str = get_next_line(fd);
		if (str != NULL)
			write(1, str, ft_strlen(str));
		else
			write(1, "NULL", 4);
		i++;
	}
	free(str);
	return (0);
}
