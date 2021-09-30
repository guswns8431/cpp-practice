/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:25:30 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 16:12:38 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CELL_H
# define CELL_H

# include "h_table.hpp"
# include <ctime>
# include <iomanip>
# include <iostream>
# include <memory>
# include <sstream>
# include <string>

template <typename T>
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
			: _row(row), _col(col), _t_ptr(t_ptr) {}

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
		virtual T		to_numeric() = 0;
};

class string_cell : public cell<int>
{
	private:
		std::string				_data;

	public:
		string_cell() : cell<int>() {};
		string_cell(const string_cell& c) = default;
		string_cell(string_cell&& c) = default;
		string_cell& operator=(const string_cell& c) = default;
		~string_cell() = default;

		string_cell(std::string data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell(row, col, t_ptr), _data(data)  {}

		std::string 			stringify() override
		{
			return (_data);
		}

		int				to_numeric() override
		{
			return (0);
		}
};

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T> > >
class numeric_cell : public cell<T>
{
	private:
		T						_data;

	public:
		numeric_cell() : cell<T>() {};
		numeric_cell(const numeric_cell& c) = default;
		numeric_cell(numeric_cell&& c) = default;
		numeric_cell& operator=(const numeric_cell& c) = default;
		~numeric_cell() = default;

		numeric_cell(T data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell<T>(row, col, t_ptr), _data(data) {}

		std::string				stringify() override
		{
			return (std::to_string(_data));
		}

		T					to_numeric() override
		{
			return (static_cast<T>(_data));
		}
};

class date_cell : public cell<unsigned long long>
{
	private:
		time_t					_time;
		std::string				_data;

	public:
		date_cell() : cell<unsigned long long>() {};
		date_cell(const date_cell& c) = default;
		date_cell(date_cell&& c) = default;
		date_cell& operator=(const date_cell& c) = default;
		~date_cell() = default;

		date_cell(time_t time, int row, int col, std::shared_ptr<table> t_ptr)
			: cell(row, col, t_ptr), _time(time)
		{
			tm					*timeinfo = gmtime(&_time);
			std::stringstream	temp;

			temp << std::to_string(timeinfo->tm_year + 1900) << "-"
				<< std::setw(2) << std::setfill('0') << timeinfo->tm_mon + 1 << "-"
				<< std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
			temp >> _data;
		}

		date_cell(std::string data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell<unsigned long long>(row, col, t_ptr), _data(data)
		{
			size_t				index;
			std::string_view	temp = data;
			int					check[12] = { 1, -1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 };
			int					year = std::stoi(temp.data(), &index);
			temp = temp.substr(index + 1).data();
			int					month = std::stoi(temp.data(), &index);
			temp = temp.substr(index + 1).data();
			int					day = std::stoi(temp.data());
			tm					timeinfo;

			if (!(month > 0 && month < 13))
				throw std::runtime_error("value error");
			if (check[month - 1] == 1 && (day < 1 || day > 31))
				throw std::runtime_error("value error");
			else if (check[month - 1] == 0 && (day < 1 || day > 30))
				throw std::runtime_error("value error");
			else if (check[month - 1] == -1 && (day < 1 || day > 28))
			{
				if (!(day == 29 && (!(year % 400) || (year % 100 && !(year % 4)))))
					throw std::runtime_error("value error");
			}
			timeinfo.tm_year = year - 1900;
			timeinfo.tm_mon = month - 1;
			timeinfo.tm_mday = day;
			timeinfo.tm_hour = 0;
			timeinfo.tm_min = 0;
			timeinfo.tm_sec = 0;
			_time = mktime(&timeinfo);
		}

		std::string				stringify() override
		{
			return (_data);
		}

		unsigned long long		to_numeric() override
		{
			return (_time);
		}
};

#endif
