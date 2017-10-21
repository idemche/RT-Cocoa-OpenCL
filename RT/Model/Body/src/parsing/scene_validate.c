/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/20 01:07:52 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		object_warning(t_info *a, int i, char *str)
{
	ft_putstr_fd("Object #", a->log_fd);
	ft_putnbr_fd(i, a->log_fd);
	ft_putstr_fd(" warning: ", a->log_fd);
	ft_putendl_fd(str, a->log_fd);
}

void		object_error(t_info *a, int i, char *str)
{
	a->scene_is_valid = 0;
	ft_putstr_fd("Object #", a->log_fd);
	ft_putnbr_fd(i, a->log_fd);
	ft_putstr_fd(" error: ", a->log_fd);
	ft_putendl_fd(str, a->log_fd);
}

void		scene_error(t_info *a, char *str)
{
	a->scene_is_valid = 0;
	ft_putstr_fd("Scene error: ", a->log_fd);
	ft_putendl_fd(str, a->log_fd);
}

static void	free_memory(t_info *a)
{
	free(a->objects);
	if (a->scene->n_negative_obj)
		free(a->negative_objects);
	if (a->scene->amount_of_spotlights)
		free(a->spotlights);
	if (a->scene->env_map)
		free(a->environment_map);
	free(a->camera);
}

int			validate_scene(char *file_path)
{
	t_info	*a;

	a = (t_info*)malloc(sizeof(t_info));
	a->is_validating = 1;
	system("rm -f log.log");
	if ((a->log_fd = open("log.log", O_CREAT | O_RDWR, S_IWRITE | S_IREAD))
																		== -1)
	{
		ft_putstr("Could not open log file");
		return (-1);
	}
	print_time(a->log_fd);
	if (!get_file(file_path, &a->json_file))
	{
		ft_putstr_fd("Could not open scene file", a->log_fd);
		return (-2);
	}
	init_scene(a);
	parse_scene(a, a->json_file);
	close(a->log_fd);
	free_memory(a);
	if (!a->scene_is_valid)
		return (-3);
	ft_putendl_fd("Scene is valid", a->log_fd);
	return (0);
}
