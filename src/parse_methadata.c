/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_methadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:33:51 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 21:50:19 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

const t_tag_recognition	g_tag_dico[] = {
	{RENDER_TAG, &load_render_data},
	{PLAYER_TAG, &load_player_data},
	{ENV_TAG, &load_env_block_data},
	{MAP_TAG, &load_map_data},
	{NULL, NULL}
};

char	*ft_strnclone(char *string, int size)
{
	char	*clone;

	clone = malloc(sizeof(char) * (size + 1));
	clone[size] = '\0';
	clone = ft_strncpy(clone, string, size);
	return (clone);
}

int	braket_content(int index, char *string, char *tag,
	t_game_object *game_object)
{
	int		i;
	int		open_braket;
	char	*content;

	i = -1;
	open_braket = 0;
	while (string[++i])
	{
		if (string[i] == '{')
			open_braket++;
		if (!open_braket && string[i] == '}')
			error_print("Missing braket in : ", tag);
		if (string[i] == '}')
			open_braket--;
		if (!open_braket)
			break ;
	}
	content = ft_strnclone(string, i + 1);
	if (mini_brackets(content, "{}") != 1)
		error_print("Wrong braket number in: ", tag);
	g_tag_dico[index].parsing_function(game_object, trim(content,
				WHITE_SPACE_AND_CURLY_BRACKETS));
	return (i);
}

int	get_parsing_function(char *tag)
{
	int	i;

	i = -1;
	while (g_tag_dico[++i].tag_name)
		if (!ft_strcmp(g_tag_dico[i].tag_name, tag))
			return (i);
	error_print("unknown tag : ", tag);
	return (-1);
}

int	extract_content(char *string, t_game_object *game_object)
{
	int		j;
	int		index;
	char	*current_tag;
	int		jump;

	j = 0;
	jump = 0;
	while (string[++j] && string[j] != '>')
		if (ft_strchr("<{}:;-", string[j]))
			error_print("FATAL ERROR : ", "unclosed tag");
	current_tag = ft_strnclone(string, j + 1);
	index = get_parsing_function(current_tag);
	j++;
	while (ft_strchr(WHITE_SPACES, string[j]))
		j++;
	if (string[j] == '{')
		jump = braket_content(index, &string[j], current_tag, game_object);
	else
		error_print("missing braket in : ", current_tag);
	free(current_tag);
	return (jump + j);
}

void	load_game_elements(char *string, t_game_object *game_object)
{
	int		i;

	i = -1;
	while (string[++i])
	{
		if (ft_strchr(WHITE_SPACES, string[i]))
			continue ;
		else if (string[i] == '<')
			i += extract_content(&string[i], game_object);
		else
			error_print("FATAL ERROR : ", "unknown trailing character");
	}	
	free(string);
}
