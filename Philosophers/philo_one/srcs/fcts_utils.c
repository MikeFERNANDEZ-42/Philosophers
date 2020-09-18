/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 08:59:59 by user42            #+#    #+#             */
/*   Updated: 2020/09/15 23:08:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

long long	ft_atoi(const char *str)
{
	int			i;
	int			minius;
	long long	result;

	i = 0;
	minius = 1;
	result = 0;
	while ((str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')) && str[i])
		i++;
	if (str[i] == '-')
	{
		minius = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result < 0)
			return ((minius == 1) ? -1 : 0);
	}
	return ((int)result * minius);
}

int	      ft_strlen(char *str)
{
    int	 i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void        ft_putstr(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

int			ft_numlen(long int nb)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	ft_itoa(long int nb, int numlen, char *msg, int *i)
{
	int		j;
	char cpy[numlen];

	j = numlen;
	cpy[j--] = '\0';
	while (j >= 0)
	{
		if ((nb % 10) > 9)
			cpy[j] = (nb % 10) + 87;
		else
			cpy[j] = (nb % 10) + 48;
		nb /= 10;
		j--;
	}
	j = 0;
	while (cpy[j])
		msg[(*i)++] = cpy[j++];
}

void	ft_messages2(int id, long int timestamp, t_global *global, char *message)
{
	char msg[50];
	int i;
	int j;

	if (pthread_mutex_lock(&global->talk) == 0)
	{
		i = 0;
		j = 0;
		ft_itoa(timestamp, ft_numlen(timestamp), msg, &i);
		msg[i++] = ' ';
		ft_itoa(id, ft_numlen(id), msg, &i);
		msg[i++] = ' ';
		while (j < ft_strlen(message))
			msg[i++] = message[j++];
		msg[i++] = '\n';
		msg[i] = '\0';
		ft_putstr(msg, 1);
	    pthread_mutex_unlock(&global->talk);
    }
}

int         ft_isnum(char *str)
{
    size_t i;

    i = 0;
    while (str && str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

void        ft_putchar(char c, int fd)
{
    write(fd, &c, 1);
}



void	ft_sleep(long int	time)
{
	long int        start;
    struct timeval  te;

	time = time / 1000;
	gettimeofday(&te, NULL);
	start = te.tv_sec * 1000LL + te.tv_usec/1000;
	while (((te.tv_sec * 1000LL + te.tv_usec/1000) - start) != time)
		gettimeofday(&te, NULL);
}

long int    get_time(long int type)
{
    long int        time;
    struct timeval  te;
    
    gettimeofday(&te, NULL);
    if (type == 0)
        time = te.tv_sec * 1000LL + te.tv_usec/1000;
    else
        time = (te.tv_sec * 1000LL + te.tv_usec/1000) - type; 
    return (time);
}

/*
void        osleep(long int time)
{
    long int    start;

    start = get_time(0);
    while (get_time(start) < time)
        osleep(1);
}*/