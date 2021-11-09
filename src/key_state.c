/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:53:02 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 20:42:30 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_is_pressed	g_pressed_buttons[] =
{
	{RIGHT, 0},
	{LEFT, 0},
	{FOREWORD, 0},
	{BACKWARD, 0},
	{UP, 0},
	{DOWN, 0},
	{SHIFT, 0},
	{-1, 0}
};

void	ft_change_key_state(int key, short state)
{
	int	i;

	i = -1;
	while (g_pressed_buttons[++i].key != -1)
		if (g_pressed_buttons[i].key == key)
			g_pressed_buttons[i].state = state;
}

short	ft_get_movement_key(int key)
{
	int	i;

	i = -1;
	while (g_pressed_buttons[++i].key != -1)
		if (g_pressed_buttons[i].key == key)
			return (g_pressed_buttons[i].state);
	return (-1);
}

short	ft_any_key_pressed(void)
{
	int	i;

	i = -1;
	while (g_pressed_buttons[++i].key != -1)
		if (g_pressed_buttons[i].state == 1)
			return (1);
	return (0);
}
