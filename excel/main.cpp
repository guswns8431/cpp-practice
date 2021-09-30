/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:08:40 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 16:14:32 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cell.hpp"
#include <iostream>

int main(void)
{
	auto t = std::make_shared<table>();
	auto d = std::make_shared<date_cell>("604-02-29", 0, 0, t);

	std::cout << d->to_numeric() << "\n" << d->stringify();
	return (0);
}
