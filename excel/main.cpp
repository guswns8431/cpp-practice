/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:08:40 by jseo              #+#    #+#             */
/*   Updated: 2021/10/01 19:20:38 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_excel.hpp"
#include "h_cli.hpp"

int main(void)
{
	std::ofstream out("test.txt");

	auto t = std::make_shared<text_table>(5, 5);

	auto d = std::make_shared<date_cell>("-2021-12-28", 0, 0, t);
	t->reg_cell(d);
	auto n = std::make_shared<numeric_cell>(3000.0, 2, 3, t);
	t->reg_cell(n);
	auto e = std::make_shared<expr_cell>("3 + 4 * (5 + 4) * (7 - 2) * 100", 1, 1, t);
	t->reg_cell(e);
	auto f = std::make_shared<expr_cell>("b1", 2, 2, t);
	t->reg_cell(f);
	std::cout << t.get();
	out << t.get();
	return (0);
}
