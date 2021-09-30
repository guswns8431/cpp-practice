/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:53:28 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 21:37:28 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_unit.hpp"

int main(void)
{
	/*
	using r1 = ratio<2, 3>;
	using r2 = ratio<3, 2>;
	using r3 = ratio_mul<r1, r2>;
	using r4 = ratio_add<r3, ratio<15, 6> >;

	std::cout << "(2 / 3) * (3 / 2) = (" << r3::num << " / " << r3::den << ")\n";
	std::cout << "(" << r3::num << " / " << r3::den << ") + " << "(15 / 6) = (" << r4::num << " / " << r4::den << ")\n";
	*/

	using zero = ratio<0, 1>;
	using one = ratio<1, 1>;

	quantity<double, dimension<one, zero, zero> > kg(1);
	quantity<double, dimension<zero, one, zero> > m(1);
	quantity<double, dimension<zero, zero, one> > s(1);

	std::cout << kg << "\n";
	std::cout << m << "\n";
	std::cout << s << "\n";

	decltype(kg) tmp1(1);
	decltype(m) tmp2(1);
	decltype(s) tmp3(1);

	kg = tmp1;
	m = tmp2;
	s = tmp3;

	std::cout << kg << "\n";
	std::cout << m << "\n";
	std::cout << s << "\n";

	decltype(tmp1) tmp4(std::move(tmp1));
	decltype(tmp2) tmp5(std::move(tmp2));
	decltype(tmp3) tmp6(std::move(tmp3));

	std::cout << tmp4 << "\n";
	std::cout << tmp5 << "\n";
	std::cout << tmp6 << "\n";

	auto copy_kg(tmp4);
	auto copy_m(tmp5);
	auto copy_s(tmp6);

	std::cout << copy_kg << "\n";
	std::cout << copy_m << "\n";
	std::cout << copy_s << "\n";

	auto value1 = 2 * kg * 3 * m / (s * s);
	auto value2 = 3 / (s * s) * m;
	std::cout << value1 << "\n" << value2;

	return (0);
}
