/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 11:04:45 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/17 13:59:59 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

static t_error	next_token(char **str, char c)
{
	while (**str && **str != c)
		*str += 1;
	if (!**str)
		return (ERROR);
	*str += 1;
	return (NO_ERROR);
}

void	get_rotor_conf(t_conf *conf, int rotor_i, int conf_i)
{
	if (conf_i == 0)
		conf->rotor[rotor_i] = ROTOR_I;
	else if (conf_i == 1)
		conf->rotor[rotor_i] = ROTOR_II;
	else if (conf_i == 2)
		conf->rotor[rotor_i] = ROTOR_III;
	else if (conf_i == 3)
		conf->rotor[rotor_i] = ROTOR_IV;
	else if (conf_i == 4)
		conf->rotor[rotor_i] = ROTOR_V;
	else if (conf_i == 5)
		conf->rotor[rotor_i] = ROTOR_VI;
	else if (conf_i == 6)
		conf->rotor[rotor_i] = ROTOR_VII;
	else if (conf_i == 7)
		conf->rotor[rotor_i] = ROTOR_VIII;
}

t_error	parse_rotors(t_conf *conf, char **str)
{
	int	rotor_1;
	int	rotor_2;
	int	rotor_3;

	rotor_1 = atoi(*str);
	if (rotor_1 < 1 || rotor_1 > 8 || next_token(str, '-'))
		return (ERROR);
	get_rotor_conf(conf, 0, rotor_1 - 1);
	rotor_2 = atoi(*str);
	if (rotor_2 < 1 || rotor_2 > 8 || rotor_2 == rotor_1
	|| next_token(str, '-'))
		return (ERROR);
	get_rotor_conf(conf, 1, rotor_2 - 1);
	rotor_3 = atoi(*str);
	if (rotor_3 < 1 || rotor_3 > 8 || rotor_3 == rotor_1 || rotor_3 == rotor_2
	|| next_token(str, '-'))
		return (ERROR);
	get_rotor_conf(conf, 2, rotor_3 - 1);
	if (**str == 'B')
		conf->reflector = REFLECTOR_B;
	else if (**str == 'C')
		conf->reflector = REFLECTOR_C;
	else
		return (ERROR);
	return (next_token(str, '-'));
}

t_error	parse_positions(t_conf *conf, char **str)
{
	conf->pos_ini[0] = atoi(*str);
	if (conf->pos_ini[0] < 1 || conf->pos_ini[0] > 26 || next_token(str, '-'))
		return (ERROR);
	conf->pos_ini[1] = atoi(*str);
	if (conf->pos_ini[1] < 1 || conf->pos_ini[1] > 26 || next_token(str, '-'))
		return (ERROR);
	conf->pos_ini[2] = atoi(*str);
	if (conf->pos_ini[2] < 1 || conf->pos_ini[2] > 26 || next_token(str, '-'))
		return (ERROR);
	return (NO_ERROR);
}

int	in_string(char c, char *str)
{
	size_t	index = 0;

	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index++;
	}
	return (0);
}

t_error parse_wire(t_conf *conf, char **str, char *used, size_t index)
{
	char	alphabet[27] = ALPHABET;
	size_t	used_i = 10 - index;

	if (!in_string(**str, alphabet) || in_string(**str, used + used_i))
		return (ERROR);
	used[used_i - 1] = **str;
	conf->wire[index / 2][index % 2] = **str;
	if (index == 9)
		return (NO_ERROR);
	else if (index % 2)
		return (next_token(str, '-'));
	else
		return (next_token(str, '/'));
}

t_error	parse_wires(t_conf *conf, char **str)
{
	char	used[11] = {0};
	size_t	index = 0;

	while (index < 10)
	{
		if (parse_wire(conf, str, used, index))
			return (ERROR);
		index++;
	}
	return (NO_ERROR);
}

t_error	get_conf(t_conf *conf, char *str)
{
	if (parse_rotors(conf, &str))
		return (ERROR);
	if (parse_positions(conf, &str))
		return (ERROR);
	if (parse_wires(conf, &str))
		return (ERROR);
	return (NO_ERROR);
}

int		main(int ac, char **av)
{
	t_conf	conf_ini;

	if (ac == 3)
	{
		if (get_conf(&conf_ini, av[1]))
		{
			write(1, "configuration error\n", 20);
			return (0);
		}
		//if (decode(&conf_ini, av[2]))
		//{
		//	write(1, "decoding error\n", 15);
		//	return (0);
		//}
		return (0);
	}
	write(1, "USAGE : configuration message\n", 30);
}