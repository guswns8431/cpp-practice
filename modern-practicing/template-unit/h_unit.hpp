/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_unit.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:33 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 19:57:44 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_H
# define UNIT_H

# include "h_ratio.hpp"
# include <iostream>

template <typename U, typename V, typename W>
class dimension
{
	public:
		using X = U;
		using Y = V;
		using Z = W;
		using type = dimension<U, V, W>;
};

template <typename D1, typename D2>
class _dim_add
{
	public:
		using type = dimension<
						ratio_add<typename D1::X, typename D2::X>,
						ratio_add<typename D1::Y, typename D2::Y>,
						ratio_add<typename D1::Z, typename D2::Z>
					>;
};

template <typename D1, typename D2>
class dim_add : public _dim_add<D1, D2>::type {};

template <typename D1, typename D2>
class _dim_sub
{
	public:
		using type = dimension<
						ratio_sub<typename D1::Y, typename D2::Y>,
						ratio_sub<typename D1::X, typename D2::X>,
						ratio_sub<typename D1::Z, typename D2::Z>
					>;
};

template <typename D1, typename D2>
class dim_sub : public _dim_sub<D1, D2>::type {};

template <typename T, typename D>
class quantity
{
	public:
		T t;
		using dim_type = D;

		quantity operator+(quantity<T, D> q)
		{
			return (quantity<T, D>(t + q.t));
		}

		quantity operator-(quantity<T, D> q)
		{
			return (quantity<T, D>(t - q.t));
		}

		template <typename C>
		quantity<T, dim_add<D, C> > operator*(quantity<T, C> q)
		{
			return (quantity<T, dim_add<D, C> >(t * q.t));
		}

		template <typename C>
		quantity<T, dim_sub<D, C> > operator/(quantity<T, C> q)
		{
			return (quantity<T, dim_sub<D, C> >(t / q.t));
		}

		quantity<T, D> operator*(T scalar)
		{
			return (quantity<T, D>(t * scalar));
		}

		quantity<T, D> operator/(T scalr)
		{
			return (quantity<T, D>(t / scalr));
		}

		quantity<T, D>& operator=(const quantity<T, D>& q)
		{
			t = q.t;
			return (*this);
		}

		quantity(T t) : t(t) {};
		quantity(const quantity<T, D>& q) = default;
		quantity(quantity<T, D>&& q) = default;
		~quantity() = default;
};

template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q)
{
	out << q.t << "\tkg^" << D::X::num / D::X::den << "\tm^" << D::Y::num / D::Y::den << "\ts^" << D::Z::num / D::Z::den;
	return (out);
}

template <typename C, typename T, typename D>
quantity <T, D> operator*(C c, quantity<T, D> q)
{
	return (quantity<T, D>(static_cast<T>(c) * q.t));
}

template <typename C, typename T, typename D>
quantity <T, D> operator/(C c, quantity<T, D> q)
{
	return (quantity<T, D>(static_cast<T>(c) / q.t));
}

#endif
