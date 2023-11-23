/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:23 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/30 14:19:57 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "get_next_line.h"

#define STRINGFY2(X) #X
#define STRINGFY(X) STRINGFY2(X)

#define NUMBER_OF_FILES 50
#define FILE_SIZE_LIMIT 1000000
#define CHUNK_SIZE 10000

int random_fd;

unsigned char get_random_char(void)
{
	static unsigned char random_pool[CHUNK_SIZE];
	static size_t index = CHUNK_SIZE;

	if (index == CHUNK_SIZE)
	{
		if (read(random_fd, random_pool, CHUNK_SIZE) < 0)
		{
			perror(STRINGFY(__LINE__));
			exit(1);
		}
		index = 0;
	}
	return (random_pool[index++]);
}

void fill_random_char(unsigned char * buff, size_t size)
{
	size_t count;

	for (count = 0; count < size;)
	{
		buff[count] = get_random_char();
		if (buff[count] != '\0')
		{
			++count;
		}
	}
}

void	generate_infile(void)
{
	unsigned int i;
	int fd2;
	unsigned char c[CHUNK_SIZE];
	char filename[20];
	size_t size;
	size_t len;

	mkdir("./infiles", 0777);

	for (i = 0; i < NUMBER_OF_FILES; ++i)
	{
		sprintf(filename, "./infiles/%d", i);
		fd2 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		size = rand();
		size += rand();
		size %= FILE_SIZE_LIMIT;
		while (size > 0)
		{
			len = size < CHUNK_SIZE ? size : CHUNK_SIZE;
			fill_random_char(c, len);
			if (write(fd2, c, len) < 0)
			{
				perror(STRINGFY(__LINE__));
				exit(1);
			}
			size -= len;
		}
		close(fd2);
	}
	fprintf(stderr, "=====test files generated=====\n");
	sleep(1);
}

void	generate_outfile(void)
{
	int count;
	char *line;
	int in_fds[NUMBER_OF_FILES];
	int out_fds[NUMBER_OF_FILES];
	char filename[20];

	mkdir("./outfiles", 0777);
	count = 0;
	while (count < NUMBER_OF_FILES)
	{
		sprintf(filename, "./infiles/%d", count);
		in_fds[count] = open(filename, O_RDONLY);
		if (in_fds[count] < 0)
		{
			perror(STRINGFY(__LINE__));
			exit(1);
		}
		sprintf(filename, "./outfiles/%d", count);
		out_fds[count] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (out_fds[count] < 0)
		{
			perror(STRINGFY(__LINE__));
			exit(1);
		}
		++count;
	}
	count = 0;
	while (count < NUMBER_OF_FILES)
	{
		int file_index = rand() % NUMBER_OF_FILES;
		if (in_fds[file_index] < 0)
		{
			continue;
		}
		line = get_next_line(in_fds[file_index]);
		if (line == NULL)
		{
			close(in_fds[file_index]);
			close(out_fds[file_index]);
			in_fds[file_index] = -1;
			++count;
			continue;
		}
		if (write(out_fds[file_index], line, strlen(line)) < 0)
		{
			perror(STRINGFY(__LINE__));
			exit(1);
		}
		free(line);
	}
	fprintf(stderr, "=====outfiles created=====\n");
}

/*
void	remove_file(void)
{
	system("rm -rf ./infiles");
	system("rm -rf ./outfiles");
	fprintf(stderr, "=====test files removed=====\n");
}
*/

int	main(void)
{
	srand(42);
	random_fd = open("/dev/urandom", O_RDONLY);
	generate_infile();
	generate_outfile();
	close(random_fd);
	return (0);
}
