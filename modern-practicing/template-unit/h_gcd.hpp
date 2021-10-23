/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_gcd.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:34:53 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 16:52:00 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCD_H
# define GCD_H

template <int X, int Y>
class gcd
{
	public:
		static const int value = gcd<Y, X % Y>::value;
};

template <int X>
class gcd<X, 0>
{
	public:
		static const int value = X;
};

#endif
