/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 01:53:41 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	int	i;

	i = -1;
	while(string[++i])
		if(!ft_isdigit(string[i]))
			error_print("wrong argument for number in: ", string);
}

void    check_if_alpha(char *string){
	int	i;

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
	return(((open_braket == 0) ? pair_number : -1)); 
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while(array[++i])
		free(array[i]);
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





// void	parse_block_argument(char *block_argument)
// {

// }

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

	content = NULL;
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

// int     main(int argc, char **argv)
int     main()
{
	// int fd;
	char *data;


	// fd = open(argv[1], O_RDONLY);
	// if(fd < 0|| argc != 2)
	// 	exit(-1);
	// data = read_file(fd);
	// data = stock_hex("#FF");
	data = malloc(sizeof(char) * 7);
	data[6] = '\0';
	data = "#FFFFFF";
	printf("%d", stock_hex(data));
	
	// int i = -1;
	// while(data[++i])
	// 	printf("%s\n", data[i]);
}
