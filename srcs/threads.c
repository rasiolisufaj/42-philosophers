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

// Waits at the start gate, then even philosophers let odd ones grab forks first
void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_unlock(philo->write_lock);
	if (philo->num_of_philos == 1)
		return (eat_alone(philo), NULL);
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
	}
	return (NULL);
}

// Starts everyone's clock at the same instant, then opens the start gate
static void	start_clock(t_program *program)
{
	size_t	now;
	int		i;

	now = get_current_time();
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		program->philos[i].start_time = now;
		program->philos[i].last_meal = now;
		i++;
	}
	pthread_mutex_unlock(&program->write_lock);
}

// All threads are spawned while write_lock (the start gate) is held, so slow
// thread creation can't eat into anyone's time_to_die
int	thread_create(t_program *program)
{
	pthread_t	monitor_thread;
	int			failed;
	int			i;

	pthread_mutex_lock(&program->write_lock);
	i = 0;
	while (i < program->philos[0].num_of_philos
		&& pthread_create(&program->philos[i].thread, NULL, &philo_routine,
			&program->philos[i]) == 0)
		i++;
	failed = (i < program->philos[0].num_of_philos
			|| pthread_create(&monitor_thread, NULL, &monitor,
				program->philos) != 0);
	if (failed)
		program->dead_flag = 1;
	start_clock(program);
	if (!failed)
		pthread_join(monitor_thread, NULL);
	while (i--)
		pthread_join(program->philos[i].thread, NULL);
	return (failed);
}
