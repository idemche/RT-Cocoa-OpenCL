/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:53:05 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 17:06:33 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		get_texture_names(t_info *a, t_json_scene js)
{
	int		i;

	a->texture_names = (char**)malloc(sizeof(char*) *
										(a->scene->amount_of_objects + 1));
	i = -1;
	while (++i < a->scene->amount_of_objects)
	{
		js.object = cJSON_GetArrayItem(js.objects, i);
		js.texture = cJSON_GetObjectItemCaseSensitive(js.object, "texture");
		if (!js.texture)
			a->texture_names[i] = strdup("None");
		else
			a->texture_names[i] = strdup(js.texture->valuestring);
	}
	a->texture_names[a->scene->amount_of_objects] = NULL;
}

void		parse_scene(t_info *a, char *json_file)
{
	t_json_scene	js;

	js.root = cJSON_Parse(json_file);
	js.objects = cJSON_GetObjectItemCaseSensitive(js.root, "objects");
	if (!js.objects || !cJSON_IsArray(js.objects))
		scene_error(a, "syntax error");
	else
		a->scene->amount_of_objects = cJSON_GetArraySize(js.objects);
	js.n_object = cJSON_GetObjectItemCaseSensitive(js.root, "negative object");
	if (!js.n_object || !cJSON_IsArray(js.n_object))
		a->scene->n_negative_obj = 0;
	else
	{
		a->scene->n_negative_obj = cJSON_GetArraySize(js.n_object);
		parse_negative_object(a, &js);
	}
	get_texture_names(a, js);
	a->objects = (t_object*)malloc(sizeof(t_object) *
										a->scene->amount_of_objects);
	parse_environment_map(a, &js);
	environment_parsing(a, &js);
	cam_parsing(a, js.root);
	light_parsing(a, &js);
	object_parsing(a, &js);
	cJSON_Delete(js.root);
}
