/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:56:20 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/12/16 17:32:30 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc >= 5 && argc <= 6)
	{
		if (check_errors(argc, argv) == false)
			return (false);
	}
	else
		return (error_quit(2));
	init_rules(&rules, argc, argv);
	if (rules.nb_philo > 1)
		init_thread(&rules);
	else
		pthread_create(&rules.philo[0].p_t, NULL,
			one_philo_fuck_it, &rules.philo[0]);
	close_threads(&rules);
	return (true);
}
