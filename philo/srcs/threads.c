/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/09 13:21:40 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Checks if the value of dead_flag changed

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

/*
Thread routine, even-numbered philos wait initially
to prevent dedalock
		ft_usleep(philo->time_to_eat / 2);

*/

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(30);
	while (!dead_loop(philo))
	{
		eat(philo);
		if (dead_loop(philo))
			break ;
		sleeping(philo);
		if (dead_loop(philo))
			break ;
		think(philo);
		if (dead_loop(philo))
			break ;
	}
	return (NULL);
}

// Thread creation
int	thread_create(t_program *program)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &monitor, program->philos) != 0)
		destroy_all(program, program->forks, "Thread creation error");
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			return (destroy_all(program, program->forks,
					"Thread creation error"), 1);
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (destroy_all(program, program->forks, "Thread join error"), 1);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			return (destroy_all(program, program->forks,
					"Thread creation error"), 1);
		i++;
	}
	return (0);
}
