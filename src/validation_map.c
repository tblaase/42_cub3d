/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:28:11 by vkuklys           #+#    #+#             */
/*   Updated: 2022/02/01 14:07:01 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_player_position(int y, int x, t_data *data)
{
	data->p_x = y + 0.5;
	data->p_y = x + 0.5;
	set_player_direction(data, data->map.map[y][x]);
	data->map.map[y][x] = '0';
	return (1);
}

int	are_outer_borders_valid(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.map[y] != NULL)
	{
		x = 0;
		while (data->map.map[y][x] != '\0' && data->map.map[y][x] != '\n')
		{
			if (y == 0 || y == data->map.columns - 1)
				if (data->map.map[y][x] != '1' && data->map.map[y][x] != ' ')
					return (1);
			if (x == 0 || x == data->map.rows - 2)
				if (data->map.map[y][x] != '1' && data->map.map[y][x] != ' ')
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	are_spaces_valid(t_data *data, int y_val, int x_val)
{
	int	y[3];
	int	x[3];
	int	i;
	int	j;

	set_coordinates(x, y, x_val, y_val);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (y[i] > 0 && x[j] > 0 && y[i]
				< data->map.columns - 1 && x[j] < data->map.rows - 2)
			{
				if (data->map.map[y[i]][x[j]] != '1'
					&& data->map.map[y[i]][x[j]] != ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	are_inner_borders_valid(t_data *data)
{
	int	x;
	int	y;
	int	flag;

	y = 0;
	flag = 0;
	while (data->map.map[y] != NULL)
	{
		x = 0;
		while (data->map.map[y][x] != '\0' && data->map.map[y][x] != '\n')
		{
			if (data->map.map[y][x] == ' ' && are_spaces_valid(data, y, x))
				return (1);
			else if (!strchr(" 012SNWE", data->map.map[y][x]))//shouldn't it be ft_strchr
				return (1);
			else if (strchr("SNWE", data->map.map[y][x])//shouldn't it be ft_strchr
				&& set_player_position(y, x, data) && flag++ > 0)
				return (1);
			x++;
		}
		y++;
	}
	if (flag == 0)
		return (1);
	return (0);
}

int	is_map_valid(t_data *data)
{
	if (are_outer_borders_valid(data) || are_inner_borders_valid(data))
	{
		write(2, "Invalid map\n", 13);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
