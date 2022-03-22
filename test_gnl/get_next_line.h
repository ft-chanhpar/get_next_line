/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:06:42 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/22 14:18:49 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_file
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	count;
	int		is_end;
}	t_file;

size_t	ft_strlen(char *str);
char	*ft_memmove(char *dst, char *src, size_t len);
char	*ft_substr(char *s1, size_t len);
char	*ft_strjoin(char *s1, char *s2, size_t len);

char	*get_next_line(int fd);

#endif
