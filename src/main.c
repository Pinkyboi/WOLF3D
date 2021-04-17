/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 03:08:32 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    error_print(char *error, char *position)
{
	ft_putstr_fd(ft_strjoin(error, position), 1);
	exit(-1);
}

char    *trim(char *string, char *filter)
{
	int		head;
	int		end;
	int		string_size;
	char	*trimmed_string;

	head = -1;
	while (string[++head])
		if (!ft_strchr(filter, string[head]))
			break;
	end = ft_strlen(string);
	while (string[--end])
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
	int	open_braket;
	int	pair_number;
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
	return (((open_braket == 0) ? pair_number : -1)); 
}

char	**parse_resolution(char *resolution_expression)
{
	char	**resolution;
	int		argument_number;
	int		i;

	resolution = ft_strsplit(resolution_expression, 'x');
	argument_number = row_len(resolution);
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


void parse_env_block(char *block_infos)
{
	char **block_terms;
	int argument_number;

	block_terms = ft_strsplit(block_infos, ':');
	argument_number = row_len(block_terms);
	if (argument_number != 2)
		error_print("wrong argument format in:", block_infos);
}


char **fix_map(char **map)
{
	int i;
	char **line;
	int bigest_row;
	int current_row;
	
	i = -1;
	while(map[++i])
	{
		line = ft_strsplit(map[i], ' ');
		int j = -1;
		while(line[++j])
			map[i][j] = line[j][0];
		map[i][j] = '\0'; 
		bigest_row = ((current_row = row_len(line)) 
			> bigest_row)? current_row : bigest_row;
		free_array(line);
	}
	return(map);
}
char **map_creator(char *data)
{
	char **map;
	
	data = trim(data, WHITE_SPACES);
		map = fix_map(ft_strsplit(data, '\n'));
	int i = -1; 
	while(map[++i]){
		int j = -1;
		while(map[i][++j])
			printf("%c ", map[i][j]);
		printf("%c", '\n');
	}
	return(NULL);
}

int     main(int argc, char **argv)
{
	int fd;
	char *data;

	fd = open(argv[1], O_RDONLY);
	if(fd < 0|| argc != 2)
		exit(-1);
	data = read_file(fd);
	map_creator(data);
}
