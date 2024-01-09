// void	mrt_print_info(t_info *info)
// {
// 	printf("am: %f\n", info->ambient->ratio);
// 	printf("am: %d %d %d\n", info->ambient->color.r, info->ambient->color.g, info->ambient->color.b);
// 	printf("cam: %f %f %f\n", info->camera->point.x, info->camera->point.y, info->camera->point.z);
// 	printf("cam: %f %f %f\n", info->camera->vector.x, info->camera->vector.y, info->camera->vector.z);
// 	printf("cam: %f\n", info->camera->fov);
// 	printf("light: %f %f %f\n", info->light->point.x, info->light->point.y, info->light->point.z);
// 	printf("light: %f\n", info->light->ratio);
// 	printf("light: %d %d %d\n", info->light->color.r, info->light->color.g, info->light->color.b);
// 	printf("sphere: %f %f %f\n", ((t_sphere*)info->sphere->content)->point.x, ((t_sphere*)info->sphere->content)->point.y, ((t_sphere*)info->sphere->content)->point.z);
// 	printf("sphere: %f\n", ((t_sphere*)info->sphere->content)->diameter);
// 	printf("sphere: %d %d %d\n", ((t_sphere*)info->sphere->content)->color.r, ((t_sphere*)info->sphere->content)->color.g, ((t_sphere*)info->sphere->content)->color.b);
// 	printf("plane: %f %f %f\n", ((t_plane*)info->plane->content)->point.x, ((t_plane*)info->plane->content)->point.y, ((t_plane*)info->plane->content)->point.z);
// 	printf("plane: %f %f %f\n", ((t_plane*)info->plane->content)->vector.x, ((t_plane*)info->plane->content)->vector.y, ((t_plane*)info->plane->content)->vector.z);
// 	printf("plane: %d %d %d\n", ((t_plane*)info->plane->content)->color.r, ((t_plane*)info->plane->content)->color.g, ((t_plane*)info->plane->content)->color.b);
// 	printf("cylinder: %f %f %f\n", ((t_cylinder*)info->cylinder->content)->point.x, ((t_cylinder*)info->cylinder->content)->point.y, ((t_cylinder*)info->cylinder->content)->point.z);
// 	printf("cylinder: %f %f %f\n", ((t_cylinder*)info->cylinder->content)->vector.x, ((t_cylinder*)info->cylinder->content)->vector.y, ((t_cylinder*)info->cylinder->content)->vector.z);
// 	printf("cylinder: %f %f\n", ((t_cylinder*)info->cylinder->content)->diameter, ((t_cylinder*)info->cylinder->content)->height);
// 	printf("cylinder: %d %d %d\n", ((t_cylinder*)info->cylinder->content)->color.r, ((t_cylinder*)info->cylinder->content)->color.g, ((t_cylinder*)info->cylinder->content)->color.b);

// 	//범위 제한 아직 구현안함

// }