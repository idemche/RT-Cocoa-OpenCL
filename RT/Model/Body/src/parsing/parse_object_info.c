/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:11 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 14:41:36 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_object_info(t_json_object *o, t_json_scene *js)
{
	o->obj = cJSON_GetObjectItemCaseSensitive(js->object, "config");
	o->p1 = cJSON_GetObjectItemCaseSensitive(o->obj, "point1");
	o->p2 = cJSON_GetObjectItemCaseSensitive(o->obj, "point2");
	o->p3 = cJSON_GetObjectItemCaseSensitive(o->obj, "point3");
	o->dir = cJSON_GetObjectItemCaseSensitive(o->obj, "dir");
	o->angle = cJSON_GetObjectItemCaseSensitive(o->obj, "angle");
	o->color = cJSON_GetObjectItemCaseSensitive(o->obj, "color");
	o->bot = cJSON_GetObjectItemCaseSensitive(o->obj, "bot");
	o->top = cJSON_GetObjectItemCaseSensitive(o->obj, "top");
	o->r = cJSON_GetObjectItemCaseSensitive(o->obj, "r");
	o->r_big = cJSON_GetObjectItemCaseSensitive(o->obj, "r_big");
	o->k = cJSON_GetObjectItemCaseSensitive(o->obj, "k");
	o->vec1 = cJSON_GetObjectItemCaseSensitive(o->obj, "vec1");
	o->vec2 = cJSON_GetObjectItemCaseSensitive(o->obj, "vec2");
	o->n = cJSON_GetObjectItemCaseSensitive(o->obj, "n");
	o->period = cJSON_GetObjectItemCaseSensitive(o->obj, "period");
	o->length = cJSON_GetObjectItemCaseSensitive(o->obj, "length");
	o->width = cJSON_GetObjectItemCaseSensitive(o->obj, "width");
	o->freq = cJSON_GetObjectItemCaseSensitive(o->obj, "freq");
}