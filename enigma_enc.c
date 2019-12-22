/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma_enc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 11:04:45 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/22 18:27:26 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

static int	check_char(char c)
{
	return (c >= 'A' && c <= 'Z');
}

static char	wire(t_conf *conf, char c)
{
	size_t	i = 0;

	while (conf->wires[0][i])
	{
		if (c == conf->wires[0][i])
			return (conf->wires[1][i]);
		if (c == conf->wires[1][i])
			return (conf->wires[0][i]);
		i++;
	}
	return (c);
}

static void	rotors_shift(t_conf *conf)
{
	if (++conf->position[0] > 25)
	{
		conf->position[0] = 0;
		if (++conf->position[1] > 25)
		{
			conf->position[1] = 0;
			if (++conf->position[2] > 25)
				conf->position[2] = 0;
		}
	}
}

static char	cypher(t_conf *conf, char c, t_rotor r, t_dir dir)
{
	size_t	i = c - 65;

	if (r == 0 && dir == REFLECTION)
		return (c);
	if (r == 3)
		return (cypher(conf, conf->reflector[i], r - 1, REFLECTION));
	if ((i += conf->position[r]) > 25)
		i %= 26;
	return (cypher(conf, conf->rotor[r][i], dir ? r - 1 : r + 1, dir));
}

t_error		encode(t_conf *conf, char *str)
{
	char	*enc_char = malloc(strlen(str) + 1);
	char	*enc_str = enc_char;

	while (*str)
	{
		if (check_char(*str))
		{
			rotors_shift(conf);
			*enc_char = wire(conf, *str);
			*enc_char = cypher(conf, *enc_char, 0, FIRST_PASS);
			*enc_char = wire(conf, *enc_char);
			enc_char++;
		}
		str++;
	}
	*enc_char = '\0';
	write(1, enc_str, strlen(enc_str));
	return (NO_ERROR);
}
