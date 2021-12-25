/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/26 01:35:23 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	static char	*str;
	/* char		*file; */
	int			i;
	int			fd;
	int			n;

	n = 1;
	/* file = "sample"; */
	i = 0;
	/* fd = open(file, O_RDONLY); */
	fd = 0;
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
/*                                            */
/* int	main(int argc, char *argv[])           */
/* {                                          */
/*     static char	*str;                      */
/*     char		*file;                           */
/*     int			i;                               */
/*     int			fd;                              */
/*     int			n;                               */
/*                                            */
/*     n = 3;                                 */
/*     file = "sample";                       */
/*     if (argc == 2)                         */
/*         n = atoi(argv[1]);                 */
/*     if (argc == 3)                         */
/*     {                                      */
/*         n = atoi(argv[1]);                 */
/*         file = argv[2];                    */
/*     }                                      */
/*     i = 0;                                 */
/*     fd = open(file, O_RDONLY);             */
/*     while (i < n)                          */
/*     {                                      */
/*         str = get_next_line(fd);           */
/*         if (str != NULL)                   */
/*             write(1, str, ft_strlen(str)); */
/*         else                               */
/*             write(1, "NULL", 4);           */
/*         i++;                               */
/*     }                                      */
/*     free(str);                             */
/*     return (0);                            */
/* }                                          */
