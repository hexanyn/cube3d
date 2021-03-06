/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 06:33:56 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/28 04:53:03 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

void	handle_keys_n(t_contr *contr, double move_speed)
{
	int		cache;

	if (contr->key.e != 0 && (cache = check_str_(contr, move_speed, 1)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x += contr->plane.x * move_speed;
		if (cache >= 2)
			contr->pos.y += contr->plane.y * move_speed;
	}
	if (contr->key.q != 0 && (cache = check_str_(contr, move_speed, -1)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x -= contr->plane.x * move_speed;
		if (cache >= 2)
			contr->pos.y -= contr->plane.y * move_speed;
	}
}

void	handle_keys(t_contr *contr)
{
	double	move_speed;
	double	rot_speed;
	int		cache;

	rot_speed = (M_PI / 60) / 10 * contr->sett.rot_speed;
	move_speed = 0.025 * contr->sett.move_speed;
	if (contr->key.w != 0 && (cache = check_fw_bw(contr, 1, move_speed)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x += contr->dir.x * move_speed;
		if (cache >= 2)
			contr->pos.y += contr->dir.y * move_speed;
	}
	if (contr->key.s != 0 && (cache = check_fw_bw(contr, -1, move_speed)))
	{
		if (cache == 1 || cache == 3)
			contr->pos.x -= contr->dir.x * move_speed;
		if (cache >= 2)
			contr->pos.y -= contr->dir.y * move_speed;
	}
	if (contr->key.a != 0)
		rotate(contr, 1, rot_speed);
	if (contr->key.d != 0)
		rotate(contr, -1, rot_speed);
	handle_keys_n(contr, move_speed);
}

int		key_press(int key, t_contr *contr)
{
	if (key == 13)
		contr->key.w = 1;
	else if (key == 1)
		contr->key.s = 1;
	else if (key == 2)
		contr->key.e = 1;
	else if (key == 0)
		contr->key.q = 1;
	else if (key == 123)
		contr->key.d = 1;
	else if (key == 124)
		contr->key.a = 1;
	if (key == 53)
		close_(contr, 0);
	if (key == 48)
		contr->menu_mode = 1;
	if (key == 49)
		check_hit(contr);
	return (0);
}

int		key_release(int key, t_contr *contr)
{
	if (key == 13)
		contr->key.w = 0;
	else if (key == 1)
		contr->key.s = 0;
	else if (key == 2)
		contr->key.e = 0;
	else if (key == 0)
		contr->key.q = 0;
	else if (key == 12)
		contr->key.q = 0;
	else if (key == 14)
		contr->key.e = 0;
	else if (key == 123)
		contr->key.d = 0;
	else if (key == 124)
		contr->key.a = 0;
	return (0);
}
