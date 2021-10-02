/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_excel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:30:08 by jseo              #+#    #+#             */
/*   Updated: 2021/10/02 22:30:34 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_excel.hpp"

std::ostream&							operator<<(std::ostream& out, table *t_ptr)
{
	out << t_ptr->print();
	return (out);
}

long double								circular_find(t_ptr ptr, const std::string& str)
{
	return (ptr->to_numeric(str));
}
