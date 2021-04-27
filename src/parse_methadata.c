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

void	parse_render(char	*string)
{
	printf("1----\n%s\n----\n\n", trim(string, WHITE_SPACES));
}

const t_tag_recognition	g_tag_dico[] = {
	{RENDER_TAG, &parse_render},
	{WINDOW_TAG, &parse_render},
	{PLAYER_TAG, &parse_render},
	{MONSTER_TAG, &parse_render},
	{ENV_TAG, &parse_render},
	{MAP_TAG, &parse_render},
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

int	braket_content(char *string, char *tag, void *parsing_function)
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
			error_print("missing braket in :", tag);
		if (string[i] == '}')
			open_braket--;
		if (!open_braket)
			break ;
	}
	content = malloc(sizeof(char) * (i - 1));
	content[i - 2] = '\0';
	content = ft_strncpy(content, &string[1], (i - 2));
	if (mini_brackets(content, "{}") != 0)
		error_print("wrong braket number in :", tag);
	parse_render(content);
	return (i);
}

void	*get_parsing_function(char *tag)
{
	int	i;

	i = -1;
	while (g_tag_dico[++i].tag_name)
		if (!ft_strcmp(g_tag_dico[i].tag_name, tag))
			return (g_tag_dico[i].tag_parse_function);
	error_print("unknown tag :", tag);
	return (NULL);
}



int	extract_content(char *string)
{
	int		j;
	char	*current_tag;
	int		jump;
	void	*parsing_function;

	j = 0;
	jump = 0;
	while (string[++j] && string[j] != '>')
		if (ft_strchr(" <{}:-", string[j]))
			error_print("FATAL ERROR : ", "unclosed tag");
	current_tag = ft_strnclone(string, j + 1);
	parsing_function = get_parsing_function(current_tag);
	j++;
	while (ft_strchr(WHITE_SPACES, string[j]))
		j++;
	if (string[j] == '{')
		jump = braket_content(&string[j], current_tag, parsing_function);
	else
		error_print("missing braket in : ", current_tag);
	free(current_tag);
	return (jump);
}

void	load_game_elements(char *string)
{
	int		i;
	char	token;

	i = -1;
	while (string[++i])
	{
		if (string[i] == '<')
			i += extract_content(&string[i]);
		// else if (!ft_strchr(WHITE_SPACES, string[i]))
		// {
		// 	token = string[i];
		// 	printf("%s\n", &string[i]);
		// 	exit(0);
		// 	error_print("trailing character : ", &token);
		// }

	}	
	free(string);
}
