#include "philos.h"

static void	ph_print(char *print, t_philo *philo, t_data *data);
static void	ph_take_forks_eat(t_data *data, t_philo *philo);
static void	ph_prep_meal(t_philo *philo);
static void	ph_think_sleep(t_philo *philo);

void	run_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	while (data->start_ms > ph_time_to_ms())
		usleep(500);
	if (data->exit)
		return ;
	ph_print(THINKING, philo, data);
	if (data->ph_count == 1)
		return (solo_philo(philo));
	philo->last_meal = data->start_ms;
	while (philo->index % 2 && ph_time_to_ms() - data->start_ms < data->eat_ms
		&& !data->dead)
		usleep(500);
	while (!data->dead)
	{
		ph_prep_meal(philo);
		if (data->dead)
			return ;
		ph_think_sleep(philo);
	}
}

static void	ph_print(char *print, t_philo *philo, t_data *data)
{
	long	current_time;

	pthread_mutex_lock(&data->data_lock);
	current_time = ph_time_to_ms() - data->start_ms;
	if (!data->dead && data->sated < data->ph_count)
		printf("%ld %zu %s\n", current_time, philo->index, print);
	pthread_mutex_unlock(&data->data_lock);
}

static void	ph_think_sleep(t_philo *philo)
{
	t_data	*data;
	long	current_time;
	long	time;

	data = philo->data;
	ph_print(SLEEPING, philo, data);
	current_time = ph_time_to_ms();
	while (ph_time_to_ms() - current_time < data->sleep_ms && !data->dead)
		usleep(500);
	if (data->dead)
		return ;
	time = 1000 * (data->die_ms - data->eat_ms - data->sleep_ms);
	ph_print(THINKING, philo, data);
	if (philo->data->ph_count % 2 != 0 && time > 0 && time < 500000)
		usleep(time * 0.75);
	else if (time > 0 && time < 500000)
		usleep(time * 0.25);
	else
		usleep(500);
}

static void	ph_prep_meal(t_philo *philo)
{
	t_data	*data;
	long	current_time;

	data = philo->data;
	ph_take_forks_eat(data, philo);
	philo->last_meal = ph_time_to_ms();
	pthread_mutex_unlock(&data->meal_lock);
	current_time = ph_time_to_ms();
	while (ph_time_to_ms() - current_time < data->eat_ms && !data->dead)
		usleep(500);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->meals_eaten++;
}

static void	ph_take_forks_eat(t_data *data, t_philo *philo)
{
	if (philo->index == data->ph_count)
	{
		pthread_mutex_lock(philo->l_fork);
		ph_print(FORKING, philo, data);
		pthread_mutex_lock(philo->r_fork);
		ph_print(FORKING, philo, data);
		ph_print(EATING, philo, data);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ph_print(FORKING, philo, data);
		pthread_mutex_lock(philo->l_fork);
		ph_print(FORKING, philo, data);
		ph_print(EATING, philo, data);
	}
	pthread_mutex_lock(&data->meal_lock);
}
