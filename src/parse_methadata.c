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

int	number_of_tag(char *string, char *tag)
{
	int	i;
	int	j;
	int	tag_number;

	i = -1;
	tag_number = 0;
	while (string[++i])
	{
		if (string[i] == *tag)
		{
			j = -1;
			while (string[i] == tag[++j])
				i++;
			if (!tag[j])
				tag_number++; 
		}
	}
	return (tag_number);
}

char	*braket_content(char *string, int max_braket, char *tag)
{
	int 	i;
	int		open_braket;
	char	*content;

	if(*string == '{')
	{
		i = -1;
		open_braket = 0;
		while(string[++i])
		{
			if (string[i] == '{')
				open_braket++;
			if (string[i] == '}')
				open_braket--;
			if (open_braket < 0)
				error_print("missed braket in :", tag);
			if (!open_braket)
				break;
		}
		content = malloc(sizeof(char) * (i - 1));
		content = ft_strncpy(content, &string[1], (i - 2));
		if(max_braket > 0 && mini_brackets(content, "{}") != max_braket)
			error_print("wrong braket number in :", tag);
		return (content);
	}
	return (NULL);
}

char	*extract_content(char *string, char *tag)
{
	int i;
	int	argument_index;
	char *string_tester;
	char *current_tag;

	i = 0;
	while (string[i] != '-')
		i++;
	current_tag = ft_strncpy(current_tag, string, i);
	if(ft_strcmp(tag, current_tag))
	{
		i++;
		while(ft_strchr(WHITE_SPACES, string[i]))
			i++;
		if(string[i] == '{')
		{
			string_tester = braket_content(string, 1, tag);
			if(string_tester)
				return (string_tester);
		}
	}
	return (NULL);
}
char	**get_tag_content(char *string, char *tag, int number_of_tag)
{
	char 	**content;
	char	*current_tag;
	int		i;
	int		content_index;

	i = -1;
	content_index = 0;
	content = (char **)malloc(sizeof(char *) * (number_of_tag + 1));
	content[number_of_tag] = NULL;
	while(string[++i])
	{
		if(string[i] == '<')
		{
			content[content_index] = extract_content(&string[i], tag);
			if (content[content_index])
				content_index++;
		}
	}
	return (content);
}