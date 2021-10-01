/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:08:40 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 23:55:14 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cell.hpp"
#include <iostream>

int main(void)
{
	auto t = std::make_shared<table>();
	auto d = std::make_shared<date_cell>("-2021-12-28", 0, 0, t);
	auto e = std::make_shared<expr_cell>("3 + 4 * (5 + 4)) * (7 - 2)) * 100", 0 ,0, t);

	std::cout << d->stringify() << "\n" << d->to_numeric() << "\n";
	std::cout << e->stringify() << "\n" << e->to_numeric();
	return (0);
}
