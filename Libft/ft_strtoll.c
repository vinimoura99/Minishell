/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-vri <joao-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:51:57 by vmoura-d          #+#    #+#             */
/*   Updated: 2025/10/23 19:15:41 by joao-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	ft_isvalid(int c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	return ((c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + base - 10)
		|| (c >= 'A' && c < 'A' + base - 10));
}

static int	ft_digit_value(int c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (0);
}

static long long	convert_digits(const char **nptr, int base, int sign,
		unsigned long long result)
{
	unsigned long long	limit;
	int					digit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = -(unsigned long long)LLONG_MIN;
	while (ft_isvalid(**nptr, base))
	{
		digit = ft_digit_value(**nptr);
		if (result > (limit - digit) / base)
		{
			errno = ERANGE;
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * base + digit;
		(*nptr)++;
	}
	if (sign == 1)
		return ((long long)result);
	else
		return (-((long long)result));
}

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	long long	result;
	int			sign;

	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	result = convert_digits(&nptr, base, sign, 0);
	if (endptr)
		*endptr = (char *)nptr;
	return (result);
}
