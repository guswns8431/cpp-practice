/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_ratio.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:06:23 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 17:01:53 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIO_H
# define RATIO_H

# include "h_gcd.hpp"

template <int N, int D = 1>
class ratio
{
	private:
		static const int _gcd = gcd<N, D>::value;

	public:
		using type = ratio<N / _gcd, D / _gcd>;
		static const int num = N;
		static const int den = D;
};

template <typename R1, typename R2>
class _ratio_add
{
	public:
		using type = typename ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>::type;
};

template <typename R1, typename R2>
class  ratio_add : public _ratio_add<R1, R2>::type {};

template <typename R1, typename R2>
class _ratio_sub
{
	public:
		using type = typename ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>::type;
};

template <typename R1, typename R2>
class ratio_sub : public _ratio_sub<R1, R2>::type {};

template <typename R1, typename R2>
class _ratio_mul
{
	public:
		using type = typename ratio<R1::num * R2::num, R1::den * R2::den>::type;
};

template <typename R1, typename R2>
class ratio_mul : public _ratio_mul<R1, R2>::type {};

template <typename R1, typename R2>
class _ratio_div
{
	public:
		using type = typename ratio<R1::num * R2::den, R2::num * R1::den>::type;
};

template <typename R1, typename R2>
class ratio_div : public _ratio_div<R1, R2>::type {};

#endif
