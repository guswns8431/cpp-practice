/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_table.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:18:15 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 22:58:36 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "h_cell.hpp"
# include <string>

class table
{
	public:
		long long to_numeric(const std::string& str) { (void)str; return (0); }
};

#endif
