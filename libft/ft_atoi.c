/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaris <afaris@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:01:52 by afaris            #+#    #+#             */
/*   Updated: 2021/11/23 18:03:12 by afaris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ignore_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 7 && str[i] <= 13))
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	unsigned long	res;
	int				s;

	s = 1;
	i = ignore_spaces(nptr);
	res = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] && nptr[i] <= '9' && nptr[i] >= '0')
	{
		res = res * 10 + (nptr[i] - '0');
		if (res > (unsigned long)9223372036854775807 && s == 1)
			return (-1);
		else if (res > (unsigned long)9223372036854775807 + 1 && s == -1)
			return (0);
		i++;
	}
	return (res * s);
}
