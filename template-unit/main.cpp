/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:53:28 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 17:05:17 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ratio.hpp"
#include <iostream>

int main(void)
{
	using r1 = ratio<2, 3>;
	using r2 = ratio<3, 2>;
	using r3 = ratio_mul<r1, r2>;
	using r4 = ratio_add<r3, ratio<15, 6> >;

	std::cout << "(2 / 3) * (3 / 2) = (" << r3::num << " / " << r3::den << ")\n";
	std::cout << "(" << r3::num << " / " << r3::den << ") + " << "(15 / 6) = (" << r4::num << " / " << r4::den << ")\n";
	return (0);
}
