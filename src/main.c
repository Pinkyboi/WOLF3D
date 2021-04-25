/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 22:23:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_print(char *error, char *position)
{
	ft_putstr_fd(ft_strjoin(error, position), 1);
	exit(-1);
}

char	*trim(char *string, char *filter)
{
	int		head;
	int		end;
	int		string_size;
	char	*trimmed_string;

	head = -1;
	while (string[++head])
		if (!ft_strchr(filter, string[head]))
			break ;
	end = ft_strlen(string);
	while (string[--end])
		if (!ft_strchr(filter, string[end]))
			break ;
	string_size = end - head + 1;
	trimmed_string = malloc(sizeof(char) * (string_size) + 1);
	trimmed_string[string_size] = '\0';
	ft_strlcat(trimmed_string, &string[head], string_size + 1);
	free(string);
	return (trimmed_string);
}

int	mini_brackets(char *string, char *bracket)
{
	int	open_braket;
	int	pair_number;
	int	i;

	i = -1;
	open_braket = 0;
	pair_number = 0;
	while (string[++i])
	{
		if (string[i] == bracket[0])
			open_braket += 1;
		if (!open_braket && string[i] == bracket[1])
			return (-1);
		if (string[i] == bracket[1] && ++pair_number)
			open_braket -= 1;
	}
	if (open_braket == 0)
		return (pair_number);
	return (-1);
}

t_block_list	*search_for_block_node(t_block_list *block_list, char icon)
{
	t_block_list	*head_save;

	head_save = block_list;
	while (head_save)
	{
		if (head_save->block_icon == icon)
			return (head_save);
		head_save = head_save->next;
	}
	return (NULL);
}

int     main(int argc, char **argv)
{
	int		fd;
	char	*data;
	t_coor		map_sizes;
	t_tile		**map;
	t_block_list *block_list;
	t_block_list *block;

	char **env = ft_strsplit("-\t\n(1, wall):#FF00FF-(2,wall):#FF00FF-(3,floor):#FF00FF", '-');
	block_list = push_block(NULL, create_block_node('w', FILLER_ICON,(t_render){.color = FILLER_COLOR},  NULL));
	load_env_block_data(env, block_list);
	fd = open(argv[1], O_RDONLY);
	if(fd < 0|| argc != 2)
		exit(-1);
	data = read_file(fd);
	data = trim(data, WHITE_SPACES);
	map_sizes = map_max_dimentions(ft_strsplit(data, '\n'));
	map = create_map(ft_strsplit(data, '\n'), block_list);
	int i = -1;
	while(++i < map_sizes.y + 2){
		int j = -1;
		while(++j < map_sizes.x + 2){
			printf("%c ", (map[i][j].wall) ? map[i][j].wall->block_icon : '0');
		}
		printf("\n");
	}
	printf("(%d, %d)\n", map_sizes.x, map_sizes.y);
}