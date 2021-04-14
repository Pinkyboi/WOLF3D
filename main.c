/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/10 12:52:06 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ALPHA "qwertyuiopasdfghjklzxcvbnm"
#define NUM_FILTER "1234567890"
#define HEX_FILTER "0123456789abcdef"
#define WHITE_SPACES " \n\t\r\v\f"
#define MAX_COLOR_VALUE 16777215
#define LEGAL_BRACKETS "()"
#define METHA_TAG "<metadata>::="
#define MAP_TAG "<map>::="

typedef struct s_tile
{
	char    block;
	char    floor;
	char    ceiling;
}               t_tile;

typedef struct s_block_list
{
	char			block_icon;
	char			type;
	void			*texture_path;
	
	struct s_block_list	*next;
}				t_block_list;

typedef	struct s_wolf
{
	t_block_list block_list;
}				t_wolf;

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void    error_print(char *error, char *position)
{
	ft_putstr_fd(ft_strjoin(error, position), 1);
	exit(-1);
}

void    check_if_number(char *string)
{
	int i;

	i = -1;
	while(string[++i])
		if(!ft_isdigit(string[i]))
			error_print("wrong argument for number in: ", string);
}

void    check_if_alpha(char *string){
	int i;

	i = -1;
	while(string[++i])
		if(!ft_isdigit(string[i]))
			error_print("wrong literal argument in: ", string);
}


char    *trim(char *string, char *filter)
{
	int		head;
	int		end;
	int		string_size;
	char	*trimmed_string;

	head = -1;
	while(string[++head])
		if (!ft_strchr(filter, string[head]))
			break;
	end = ft_strlen(string);
	while(string[--end])
		if (!ft_strchr(filter, string[end]))
			break;
	string_size = end - head + 1;
	trimmed_string = malloc(sizeof(char) * (string_size) + 1);
	trimmed_string[string_size] = '\0';
	ft_strlcat(trimmed_string, &string[head], string_size + 1);
	return(trimmed_string);   
}

int		mini_brackets(char *string, char *bracket)
{
	int open_braket;
	int pair_number;
	int	i;

	i = -1;
	open_braket = 0;
	pair_number = 0;
	while(string[++i])
	{
		if (string[i] == bracket[0])
			open_braket += 1;
		if (!open_braket && string[i] == bracket[1])
			return (-1);
		if (string[i] == bracket[1] && ++pair_number)
			open_braket -= 1;
	}
	return(((open_braket == 0) ? pair_number : -1)); 
}

void	free_array(char **array)
{
	int i;
	i = -1;
	while(array[++i])
		free(array[i]);
}

char	**parse_block_tuple(char *tuple)
{
	int		i;
	int		argument_number;
	char	**splited_tuple;

	if(mini_brackets(tuple, LEGAL_BRACKETS) != 1)
		error_print("wrong tuple format in:", tuple);
	splited_tuple = ft_strsplit(tuple, ',');
	argument_number = row_len(splited_tuple);
	if (argument_number != 2)
		error_print("wrong tuple format in:", tuple);
	i = -1;
	while (splited_tuple[++i])
		splited_tuple[i] = trim(splited_tuple[i],
			ft_strjoin(WHITE_SPACES, LEGAL_BRACKETS));
	return (splited_tuple);
}


char	**parse_resolution(char *resolution_expression)
{
	char **resolution;
	int argument_number;
	int  i;

	resolution = ft_strsplit(resolution_expression, 'x');
	argument_number = row_len(resolution_expression);
	if (argument_number != 2)
		error_print("wrong resolution format in:", resolution_expression);
	i = -1;
	while (resolution[++i])
	{
		resolution[i] = trim(resolution[i], WHITE_SPACES);
		check_if_number(resolution[i]);
	}
	return (resolution);
}

int		hext_to_int(char *number)
{
	int rank;
	int final_number;
	int i;
	int j;

	rank = ft_strlen(number) -1;
	final_number = 0;
	i = -1;
	while(number[++i])
	{
		j = -1;
		if(!ft_strchr(HEX_FILTER, ft_tolower(number[i])))
			return(-1);
		while(++j < 16 && ft_tolower(number[i]) != HEX_FILTER[j]);
		final_number += j * pow(16,  rank);
		rank--;
	}
	return(final_number);
}
int 	hex_to_color(char *color)
{
	int i;
	int color_int;
	int color_len;

	i = -1;
	while (color[++i])
	{
		if(!ft_strchr(HEX_FILTER, ft_tolower(color[i])))
		 	error_print("wrong color format in:", color);
	}
	color_int = hext_to_int(color);
	if(abs(color_int) > MAX_COLOR_VALUE)
		error_print("wrong color format in:", color);
	return (color_int);
}

int		ft_stock_hex(char *color)
{
	int color_int;

	if(color[0] == '#' && color[1])
		color_int = hex_to_color(&color[1]);
	return(color_int);
}

void	parse_block_argument(char *block_argument)
{

}

int		row_len(char **array)
{
	int i;

	i = -1;
	while(array[++i]);
	return (i);
}
void parse_env_block(char *block_infos)
{
	char **block_terms;
	int argument_number;

	
	block_terms = ft_strsplit(block_infos, ':');
	argument_number = row_len(block_terms);
	if	(argument_number != 2)
		error_print("wrong argument format in:", block_infos);
}

char    *read_file(int fd){
	int     read_index;
	char    buffer[42069 + 1];
	char    *content;

	*content = '\0';
	while(1)
	{
		read_index = read(fd, buffer, 42069);
		if(errno || read_index == -1)
			exit(-1);
		if(!read_index)
			break;
		content = ft_strjoin(content, buffer);
	}
	close(fd);
	return(content);
}

int     main(int argc, char **argv)
{
	int fd;
	char *data;


	// fd = open(argv[1], O_RDONLY);
	// if(fd < 0|| argc != 2)
	// 	exit(-1);
	// data = read_file(fd);
	// data = ft_stock_hex("#FF");
	data = malloc(sizeof(char) * 7);
	data[6] = '\0';
	data = "#FFFFFF";
	printf("%d", ft_stock_hex(data));
	
	// int i = -1;
	// while(data[++i])
	// 	printf("%s\n", data[i]);
}
