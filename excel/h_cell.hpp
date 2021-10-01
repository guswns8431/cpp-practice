/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:25:30 by jseo              #+#    #+#             */
/*   Updated: 2021/09/30 23:55:00 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CELL_H
# define CELL_H

# include "h_table.hpp"
# include <ctime>
# include <cctype>
# include <iomanip>
# include <iostream>
# include <memory>
# include <sstream>
# include <stack>
# include <string>
# include <vector>

template <typename T>
class cell
{
	protected:
		int								_row;
		int								_col;
		std::shared_ptr<table>			_t_ptr;

	public:
		cell(void) = default;
		cell(const cell& c) = default;
		cell(cell&& c) = default;
		cell& operator=(const cell& c) = default;
		virtual ~cell(void) = default;

		cell(int row, int col, std::shared_ptr<table> t_ptr)
			: _row(row), _col(col), _t_ptr(t_ptr) {}

		int								get_row(void)
		{
			return (_row);
		}

		int								get_col(void)
		{
			return (_col);
		}

		std::weak_ptr<table>			get_table(void)
		{
			return (_t_ptr);
		}

		virtual std::string				stringify(void) = 0;
		virtual T						to_numeric(void) = 0;
};

class string_cell : public cell<int>
{
	private:
		std::string						_data;

	public:
		string_cell(void) : cell<int>() {};
		string_cell(const string_cell& c) = default;
		string_cell(string_cell&& c) = default;
		string_cell& operator=(const string_cell& c) = default;
		~string_cell(void) = default;

		string_cell(std::string data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell(row, col, t_ptr), _data(data)  {}

		std::string 					stringify(void) override
		{
			return (_data);
		}

		int								to_numeric(void) override
		{
			return (0);
		}
};

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T> > >
class numeric_cell : public cell<T>
{
	private:
		T								_data;

	public:
		numeric_cell(void) : cell<T>() {};
		numeric_cell(const numeric_cell& c) = default;
		numeric_cell(numeric_cell&& c) = default;
		numeric_cell& operator=(const numeric_cell& c) = default;
		~numeric_cell(void) = default;

		numeric_cell(T data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell<T>(row, col, t_ptr), _data(data) {}

		std::string						stringify(void) override
		{
			return (std::to_string(_data));
		}

		T								to_numeric(void) override
		{
			return (static_cast<T>(_data));
		}
};

class date_cell : public cell<long long>
{
	private:
		time_t							_time;
		std::string						_data;

	public:
		date_cell(void) : cell<long long>() {};
		date_cell(const date_cell& c) = default;
		date_cell(date_cell&& c) = default;
		date_cell& operator=(const date_cell& c) = default;
		~date_cell(void) = default;

		date_cell(time_t time, int row, int col, std::shared_ptr<table> t_ptr)
			: cell(row, col, t_ptr), _time(time)
		{
			tm							*timeinfo = gmtime(&_time);
			std::stringstream			temp;

			temp << std::to_string(timeinfo->tm_year + 1900) << "-"
				<< std::setw(2) << std::setfill('0') << timeinfo->tm_mon + 1 << "-"
				<< std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
			temp >> _data;
		}

		date_cell(std::string data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell<long long>(row, col, t_ptr), _data(data)
		{
			size_t						index;
			std::string_view			temp = data;
			int							check[12] = { 1, -1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 };
			int							year = std::stoi(temp.data(), &index);
			temp = temp.substr(index + 1).data();
			int							month = std::stoi(temp.data(), &index);
			temp = temp.substr(index + 1).data();
			int							day = std::stoi(temp.data());
			tm							timeinfo;

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

		std::string						stringify(void) override
		{
			return (_data);
		}

		long long						to_numeric(void) override
		{
			if (_time < 0)
				_time = 0;
			return (_time);
		}
};

class expr_cell : cell<long double>
{
	private:
		std::string						_data;
		std::string						_conv;
		std::vector<std::string>		_expr;
		long double						_retn;

		int								_precedences(char c)
		{
			switch (c)
			{
				case '(':
				case '{':
				case '[':
					return (0);
				case '+':
				case '-':
					return (1);
				case '*':
				case '/':
					return (2);
				default :
					return (0);
			}
		}

		void							_parse(void)
		{
			_data.insert(std::begin(_data), '(');
			_data.push_back(')');

			std::stack<std::string>		_oper;
			std::string					temp;
			auto						begin = std::begin(_data);
			auto						end = std::end(_data);
			while (begin != end)
			{
				if (std::isalpha(*begin))
				{
					temp.push_back(*begin++);
					while (std::isdigit(*begin))
						temp.push_back(*begin++);
					_expr.push_back(std::to_string(_t_ptr->to_numeric(temp)));
					temp.clear();
				}
				else if (std::isdigit(*begin))
				{
					while (std::isdigit(*begin))
						temp.push_back(*begin++);
					_expr.push_back(temp);
					temp.clear();
				}
				else if (*begin == '(' || *begin == '{' || *begin == '[')
					_oper.push(std::string(1, *begin++));
				else if (*begin == ')' || *begin == '}' || *begin == ']')
				{
					std::string			target;
					std::string			top;
					switch (*begin++)
					{
						case ')':
							target = "(";
							break ;
						case '}':
							target = "{";
							break ;
						case ']':
							target = "[";
							break ;
					}
					while (true)
					{
						if (_oper.empty())
							throw std::runtime_error("expr error");
						top = _oper.top();
						_oper.pop();
						if (top == target)
							break ;
						_expr.push_back(top);
					}
				}
				else if (*begin == '+' || *begin == '-' || *begin == '*' || *begin == '/')
				{
					while (!_oper.empty() && _precedences(_oper.top().at(0)) >= _precedences(*begin))
					{
						std::string		top = _oper.top();
						_oper.pop();
						_expr.push_back(top);
					}
					_oper.push(std::string(1, *begin++));
				}
				else
					++begin;
			}
			std::for_each(std::begin(_expr), std::end(_expr), [this] (auto str) { this->_conv += str + " ";} );
		}

		void							_calculate(void)
		{
			long double					result;
			std::stack<long double>		storage;
			auto						begin = std::begin(_expr);
			auto						end = std::end(_expr);

			while (begin != end)
			{
				if ((*begin).at(0) == '+' || (*begin).at(0) == '-' || (*begin).at(0) == '*' || (*begin).at(0) == '/')
				{
					long double y = storage.top();
					storage.pop();
					long double x = storage.top();
					storage.pop();
					switch ((*begin).at(0))
					{
						case '+':
							storage.push(x + y);
							break ;
						case '-':
							storage.push(x - y);
							break ;
						case '*':
							storage.push(x * y);
							break ;
						case '/':
							storage.push(x / y);
							break ;
					}
				}
				else
				{
					result = std::stold(*begin);
					storage.push(result);
				}
				++begin;
			}
			result = storage.top();
			storage.pop();
			_retn = result;
		}

	public:
		expr_cell(void) : cell<long double>() {};
		expr_cell(const expr_cell& c) = default;
		expr_cell(expr_cell&& c) = default;
		expr_cell& operator=(const expr_cell& c) = default;
		~expr_cell(void) = default;

		expr_cell(std::string data, int row, int col, std::shared_ptr<table> t_ptr)
			: cell<long double>(row, col, t_ptr), _data(data)
		{
			try
			{
				_parse();
				_calculate();
			}
			catch (std::exception& e)
			{
				throw std::runtime_error("expr error");
			}
		}

		std::string						stringify(void) override
		{
			return (_conv);
		}

		long double						to_numeric(void) override
		{
			return (_retn);
		}
};

#endif
