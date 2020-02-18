/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:26:46 by edal--ce          #+#    #+#             */
/*   Updated: 2020/02/18 19:11:03 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

#define VIEW_DIST 8

int		dark_mode_mod(int color, float cur)
{
	t_color c;
	float	yo;

	c.r = 0xff0000 & color;
	c.g = 0xff00 & color;
	c.b = 0xff & color;
	yo = 1.0f - cur / VIEW_DIST;
	if (yo < 0.0f)
		yo = 0.0f;
	else if (yo > 1.0f)
		yo = 1.0f;
	c.r = ((int)((double)0x0 + (c.r - 0x0) * yo) & 0xFF0000);
	c.g = ((int)((double)0x0 + (c.g - 0x0) * yo) & 0xFF00);
	c.b = ((int)((double)0x0 + (c.b - 0x0) * yo) & 0xFF);
	return (c.r + c.g + c.b);
}

void	drawback(t_contr *contr)
{
	int floor;
	int ceil;
	int i;
	int j;

	floor = contr->f_color;
	ceil = contr->c_color;
	i = -1;
	while (++i < contr->res_h / 2)
	{
		j = -1;
		while (++j < contr->res_w)
			p_px(contr, j, i, ceil);
	}
	while (++i < contr->res_h)
	{
		j = -1;
		while (++j < contr->res_w)
			p_px(contr, j, i, floor);
	}
}

void	draw_floor_ceil(t_contr *contr, t_floor_rend *r, int y)
{
	int		x;
	int		color;
	t_vpi	tx_m;

	x = -1;
	while (++x < contr->res_w)
	{
		tx_m.x = (int)(64 * (r->floor.x - (int)r->floor.x)) & (64 - 1);
		tx_m.y = (int)(64 * (r->floor.y - (int)r->floor.y)) & (64 - 1);
		color = g_px(contr->textures[5], tx_m.x, tx_m.y);
		if ((r->floor.x += r->floor_step.x) && contr->dark_mode == 1)
			color = dark_mode_mod(color, contr->res_h /
				(2.0f * y - contr->res_h));
		p_px(contr, x, y, color);
		color = g_px(contr->textures[6], tx_m.x, tx_m.y);
		if ((r->floor.y += r->floor_step.y) && contr->dark_mode == 1)
			color = dark_mode_mod(color, contr->res_h /
				(2.0f * y - contr->res_h));
		p_px(contr, x, contr->res_h - y, color);
	}
}

void	draw_floor(t_contr *contr)
{
	t_floor_rend	r;
	int				y;
	int				p;
	t_vp			ray_0;
	t_vp			ray_1;

	y = -1;
	while (++y < contr->res_h)
	{
		ray_0.x = contr->dir.x - contr->plane.x;
		ray_0.y = contr->dir.y - contr->plane.y;
		ray_1.x = contr->dir.x + contr->plane.x;
		ray_1.y = contr->dir.y + contr->plane.y;
		p = y - contr->res_h / 2;
		r.pos_r = 0.5 * contr->res_h;
		r.floor_step.x = r.pos_r / p * (ray_1.x - ray_0.x) / contr->res_w;
		r.floor_step.y = r.pos_r / p * (ray_1.y - ray_0.y) / contr->res_w;
		r.floor.x = contr->pos.x + r.pos_r / p * ray_0.x;
		r.floor.y = contr->pos.y + r.pos_r / p * ray_0.y;
		draw_floor_ceil(contr, &r, y);
	}
}