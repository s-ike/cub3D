/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnega.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 12:21:01 by sikeda            #+#    #+#             */
/*   Updated: 2020/11/30 14:30:27 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnega(double d)
{
	int	flag;
	int	i;

	i = *((int *)&d + 1);
	flag = (i >> 31) & 1;
	return (flag);
}