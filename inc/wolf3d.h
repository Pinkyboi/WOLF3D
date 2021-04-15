/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 03:03:11 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "mlx.h"
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
	char			type;
	char			block_icon;
    void			*texture_path;
	struct s_block_list	*next;
}				t_block_list;

typedef	struct s_wolf
{
	t_block_list block_list;
}				t_wolf;

int		isdigit(int c);
int		row_len(char **array);
int		row_len(char **array);
int		hex_to_int(char *number);
int 	hex_to_color(char *color);
int		stock_hex(char *color);
int		mini_brackets(char *string, char *bracket);
char	*trim(char *string, char *filter);
char	**parse_block_tuple(char *tuple);
char    *read_file(int fd);
void    error_print(char *error, char *position);
void    check_if_alpha(char *string);
void    check_if_number(char *string);
void	free_array(char **array);