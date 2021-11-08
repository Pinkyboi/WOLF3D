/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_methadata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:33:51 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 18:53:49 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

const t_tag_recognition	g_tag_dico[] = {
	{RENDER_TAG, &ft_load_render_data},
	{PLAYER_TAG, &ft_load_player_data},
	{ENV_TAG, &ft_load_env_block_data},
	{MAP_TAG, &ft_load_map_data},
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
	while (string && string[++i])
	{
		if (string[i] == '{')
			open_braket++;
		if (!open_braket && string[i] == '}')
			ft_err_print("Missing braket in : ", tag);
		if (string[i] == '}')
			open_braket--;
		if (!open_braket)
			break ;
	}
	content = ft_strnclone(string, i + 1);
	if (ft_mini_brackets(content, "{}") != 1)
		ft_err_print("Wrong braket number in: ", tag);
	g_tag_dico[index].parsing_function(game_object, ft_trim(content,
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
	ft_err_print("Unknown tag : ", tag);
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
	while (string && string[++j] && string[j] != '>')
		if (ft_strchr("<{}:;-", string[j]))
			ft_err_print("FATAL ERROR : ", "unclosed tag");
	current_tag = ft_strnclone(string, j + 1);
	index = get_parsing_function(current_tag);
	j++;
	while (ft_strchr(WHITE_SPACES, string[j]))
		j++;
	if (string[j] == '{')
		jump = braket_content(index, &string[j], current_tag, game_object);
	else
		ft_err_print("Missing braket in : ", current_tag);
	free(current_tag);
	return (jump + j);
}

void	ft_load_game_elements(char *string, t_game_object *game_object)
{
	int		i;

	i = -1;
	game_object->parser.block_list = ft_push_block(NULL,
			ft_create_block_node('w', FILLER_ICON,
				(t_render){.color = FILLER_COLOR}, &ft_color_wall));
	ft_load_render_data(game_object, NULL);
	ft_load_player_data(game_object, NULL);
	while (string && string[++i])
	{
		if (ft_strchr(WHITE_SPACES, string[i]))
			continue ;
		else if (string[i] == '<')
			i += extract_content(&string[i], game_object);
		else
			ft_err_print("FATAL ERROR : ", "unknown trailing character");
	}
}
