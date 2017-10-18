/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_negative_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:05 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/18 15:37:44 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_negative_object(t_info *a, t_json_scene *js)
{
	if (a->scene->n_negative_obj != 1)
		warning(a, "only one first negative object is counted");
	a->negative_objects = (t_object*)malloc(sizeof(t_object));
	js->object = cJSON_GetArrayItem(js->n_object, 0);
	js->type = cJSON_GetObjectItemCaseSensitive(js->object, "type");
	if (!cJSON_IsString(js->type))
		object_error(a, -1, "negative object invalid type");
	if (!ft_strcmp(js->type->valuestring, "SPHERE"))
	{
		a->negative_objects->type = SPHERE;
		sphere_parsing(a, -1, a->negative_objects, js);
	}
	else if (!ft_strcmp(js->type->valuestring, "CYLINDER"))
	{
		a->negative_objects->type = CYLINDER;
		cylinder_parsing(a, -1, a->negative_objects, js);
	}
	else
		object_error(a, -1, "only cylinder and sphere can be negative");
}
