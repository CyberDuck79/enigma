/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:10:47 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/08 12:00:25 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENIGMA_H
# define ENIGMA_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>

/*
Rotors and reflectors internal connections definitions
*/

# define RTR_I			(const int [26])\
{4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9}
# define R_RTR_I		(const int [26])\
{20,22,24,6,0,3,5,15,21,25,1,4,2,10,12,19,7,23,18,11,17,8,13,16,14,9}
# define RTR_II			(const int [26])\
{0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4}
# define R_RTR_II		(const int [26])\
{0,9,15,2,25,22,17,11,5,1,3,10,14,19,24,20,16,6,4,13,7,23,12,8,21,18}
# define RTR_III		(const int [26])\
{1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14}
# define R_RTR_III		(const int [26])\
{19,0,6,1,15,2,18,3,16,4,20,5,21,13,25,7,24,8,23,9,22,11,17,10,14,12}
# define RTR_IV			(const int [26])\
{4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1}
# define R_RTR_IV		(const int [26])\
{7,25,22,21,0,17,19,13,11,6,20,15,23,16,2,4,9,12,1,18,10,3,24,14,8,5}
# define RTR_V			(const int [26])\
{21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10}
# define R_RTR_V		(const int [26])\
{16,2,24,11,23,22,4,13,5,19,25,14,18,12,21,9,20,3,10,6,8,0,17,15,7,1}
# define RTR_VI			(const int [26])\
{9,15,6,21,14,20,12,5,24,16,1,4,13,7,25,17,3,10,0,18,23,11,8,2,19,22}
# define R_RTR_VI		(const int [26])\
{18,10,23,16,11,7,2,13,22,0,17,21,6,12,4,1,9,15,19,24,5,3,25,20,8,14}
# define RTR_VII		(const int [26])\
{13,25,9,7,6,17,2,23,12,24,18,22,1,14,20,5,0,8,21,11,15,4,10,16,3,19}
# define R_RTR_VII		(const int [26])\
{16,12,6,24,21,15,4,3,17,2,22,19,8,0,13,20,23,5,10,25,14,18,11,7,9,1}
# define RTR_VIII		(const int [26])\
{5,10,16,7,19,11,23,14,2,1,9,18,15,3,25,17,0,12,4,22,13,8,20,24,6,21}
# define R_RTR_VIII		(const int [26])\
{16,9,8,13,18,0,24,3,21,10,1,5,17,20,7,12,2,15,11,4,22,25,19,6,23,14}
# define REFLECTOR_B	(const int [26])\
{24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19}
# define REFLECTOR_C	(const int [26])\
{17,3,14,1,9,13,19,10,21,4,7,12,11,5,2,22,25,0,23,6,24,8,15,18,20,16}

/*
Rotors and reflectors tabs definitions
*/

# define ROTORS			(const int* [8])\
{RTR_I,RTR_II,RTR_III,RTR_IV,RTR_V,RTR_VI,RTR_VII,RTR_VIII}
# define R_ROTORS		(const int* [8])\
{R_RTR_I,R_RTR_II,R_RTR_III,R_RTR_IV,R_RTR_V,R_RTR_VI,R_RTR_VII,R_RTR_VIII}
# define REFLECTORS		(const int* [2])\
{REFLECTOR_B,REFLECTOR_C}

/*
configured rotors and reflector index
*/
typedef enum	e_rotor
{
	ROTOR_I,
	ROTOR_II,
	ROTOR_III,
	REFLECTOR
}				t_rotor;

/*
direction in the encryption circuit
*/
typedef enum	e_dir
{
	FIRST_PASS,
	REFLECTION
}				t_dir;

/*
error flag
*/
typedef enum	e_error
{
	NO_ERROR,
	ERROR
}				t_error;

/*
Configuration and machine state structure

rotor) rotors configuration
reflector) reflector configuration
position) state of the rotors positions
wires) wires configuration
*/
typedef struct	s_conf
{
	int			rotor[3][2][26];
	int			reflector[26];
	int			position[3];
	char		wires[2][13];
}				t_conf;

/*
Public methods:
get_conf) parse the sequence or return error
encode) encrypt the input sequnce
*/

t_error			get_conf(t_conf *conf, char *str);
void			encode(t_conf *conf, char *str);

#endif