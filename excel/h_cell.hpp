/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:25:30 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 13:42:04 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CELL_H
# define CELL_H

# include "h_table.hpp"
# include <memory>
# include <string>

class cell
{
	protected:
		int						_row;
		int						_col;
		std::shared_ptr<table>	_t_ptr;

	public:
		cell() = default;
		cell(const cell& c) = default;
		cell(cell&& c) = default;
		cell& operator=(const cell& c) = default;
		virtual ~cell() = default;

		cell(int row, int col, std::shared_ptr<table> t_ptr)
			: _row(row), _col(col), _t_ptr(t_ptr) {};

		int						get_row()
		{
			return (_row);
		}

		int						get_col()
		{
			return (_col);
		}

		std::weak_ptr<table>	get_table()
		{
			return (_t_ptr);
		}

		virtual std::string		stringify() = 0;
		virtual long double		to_numeric() = 0;
};

class string_cell : public cell
{
	private:
		std::string				_data;

	public:
		string_cell() : cell() {};
		string_cell(const string_cell& c) = default;
		string_cell(string_cell&& c) = default;
		string_cell& operator=(const string_cell& c) = default;
		~string_cell() = default;

		string_cell(std::string data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell(row, col, t_ptr), _data(data)  {};

		std::string 			stringify() override
		{
			return (_data);
		}

		long double				to_numeric() override
		{
			return (0.0);
		}
};

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T> > >
class numeric_cell : public cell
{
	private:
		T						_data;

	public:
		numeric_cell() : cell() {};
		numeric_cell(const numeric_cell& c) = default;
		numeric_cell(numeric_cell&& c) = default;
		numeric_cell& operator=(const numeric_cell& c) = default;
		~numeric_cell() = default;

		numeric_cell(T t, int row, int col, std::shared_ptr<table> t_ptr)
			: cell(row, col, t_ptr), _data(t) {};

		std::string				stringify() override
		{
			return (std::to_string(_data));
		}

		long double						to_numeric() override
		{
			return (static_cast<long double>(_data));
		}
};

class date_cell : public cell
{

};

#endif
