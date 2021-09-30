/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:08:40 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 13:39:28 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cell.hpp"
#include <iostream>

int main(void)
{
	auto t_ptr = std::make_shared<table>();
	auto d = std::make_shared<numeric_cell<double> >(30.01, 0, 0, t_ptr);

	std::cout << d->get_col() << "\n"
		<< d->get_row() << "\n"
		<< d->to_numeric() << "\n"
		<< d->stringify() ;

	return (0);
}
