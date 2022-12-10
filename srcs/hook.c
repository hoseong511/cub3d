/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:47 by hossong           #+#    #+#             */
/*   Updated: 2022/12/10 17:17:18 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

static void left_right_key(t_player *p, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;
	
	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(rot_speed) - p->dir.y * sin(rot_speed);
	p->dir.y = old_dir_x * sin(rot_speed) + p->dir.y * cos(rot_speed);
	p->plane.x = p->plane.x * cos(rot_speed) - p->plane.y * sin(rot_speed);
	p->plane.y = old_plane_x * sin(rot_speed) + p->plane.y * cos(rot_speed);
}

int	handle_key_down(int keycode, t_data *param)
{
	double moveSpeed = 0.02 * 5.0;
	double rotSpeed = M_PI / 18.0; // 180/18.0 10deg
	int	up_x;
	int	up_y;
	int down_x;
	int down_y;

	up_x = param->player.row + param->player.dir.x * moveSpeed;
	up_y = param->player.col + param->player.dir.y * moveSpeed;
	down_x = param->player.row - param->player.dir.x * moveSpeed;
	down_y = param->player.col - param->player.dir.y * moveSpeed;
	if (keycode == KEY_W)
	{
		if (param->map[up_x][(int)param->player.col] != '1')
			param->player.row += param->player.dir.x * moveSpeed;
		if (param->map[(int)param->player.row][up_y] != '1')
			param->player.col += param->player.dir.y * moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if (param->map[down_x][(int)param->player.col] != '1')
			param->player.row -= param->player.dir.x * moveSpeed;
		if (param->map[(int)param->player.row][down_y] != '1')
			param->player.col -= param->player.dir.y * moveSpeed;
	}
	else if (keycode == KEY_A)
	{
		if (param->player.player_dir == 'E' || param->player.player_dir == 'W')
			rotSpeed *= -1;
		left_right_key(&param->player, rotSpeed);
	}
	else if (keycode == KEY_D)
	{
		if (param->player.player_dir == 'E' || param->player.player_dir == 'W')
			rotSpeed *= -1;
		left_right_key(&param->player, -rotSpeed);
	}
	render(param);
	return (0);
}
