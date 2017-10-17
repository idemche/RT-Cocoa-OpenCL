/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_negative_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:05 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:06:07 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_negative_object(t_info *a, t_json_scene *js)
{
	if (a->scene->n_negative_obj != 1)
		ft_putstr("Only one first negative object is counted\n");
	a->negative_objects = (t_object*)malloc(sizeof(t_object));
	js->object = cJSON_GetArrayItem(js->n_object, 0);
	js->type = cJSON_GetObjectItemCaseSensitive(js->object, "type");
	if (!cJSON_IsString(js->type))
		ft_error("Negative object type error");
	if (!ft_strcmp(js->type->valuestring, "SPHERE"))
	{
		a->negative_objects->type = SPHERE;
		sphere_parsing(a->negative_objects, js);
	}
	else if (!ft_strcmp(js->type->valuestring, "CYLINDER"))
	{
		a->negative_objects->type = CYLINDER;
		cylinder_parsing(a->negative_objects, js);
	}
	else
		ft_error("Only cylinder and sphere can be negative");
}
