/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_excel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:06:30 by jseo              #+#    #+#             */
/*   Updated: 2021/10/02 22:30:31 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEL_H
# define EXCEL_H

# include <ctime>
# include <cctype>
# include <fstream>
# include <iomanip>
# include <iostream>
# include <memory>
# include <sstream>
# include <stack>
# include <string>
# include <vector>

class cell;
class table;

using coord = std::pair<int, int>;
using t_ptr = std::shared_ptr<table>;
using t_ref = std::weak_ptr<table>;
using c_ptr = std::shared_ptr<cell>;
using t_vec = std::vector<std::pair<coord, c_ptr> >;

std::ostream&							operator<<(std::ostream& out, table *t_ptr);
long double								circular_find(t_ptr ptr, const std::string& str);

class cell
{
	protected:
		coord							_pos;
		t_ptr							_ptr;

	public:
		cell(void) = default;
		cell(const cell& c) = default;
		cell(cell&& c) = default;
		cell& operator=(const cell& c) = default;
		virtual ~cell(void) = default;

		cell(int row, int col, t_ptr ptr)
			: _ptr(ptr)
		{
			_pos = std::make_pair(row, col);
		}

		int								get_row(void)
		{
			return (_pos.first);
		}

		int								get_col(void)
		{
			return (_pos.second);
		}

		t_ref							get_table(void)
		{
			return (_ptr);
		}

		virtual std::string				stringify(void) { return (""); }
		virtual long double				to_numeric(void) { return (0.0); }
};

class string_cell : public cell
{
	private:
		std::string						_data;

	public:
		string_cell(void) = default;
		string_cell(const string_cell& c) = default;
		string_cell(string_cell&& c) = default;
		string_cell& operator=(const string_cell& c) = default;
		~string_cell(void) = default;

		string_cell(std::string data, int row, int col, t_ptr ptr)
			: cell(row, col, ptr), _data(data)  {}

		std::string 					stringify(void) override
		{
			return (_data);
		}

		long double						to_numeric(void) override
		{
			return (0.0);
		}
};

class numeric_cell : public cell
{
	private:
		double							_data;

	public:
		numeric_cell(void) = default;
		numeric_cell(const numeric_cell& c) = default;
		numeric_cell(numeric_cell&& c) = default;
		numeric_cell& operator=(const numeric_cell& c) = default;
		~numeric_cell(void) = default;

		numeric_cell(double data, int row, int col, t_ptr ptr)
			: cell(row, col, ptr), _data(data) {}

		std::string						stringify(void) override
		{
			return (std::to_string(_data));
		}

		long double						to_numeric(void) override
		{
			return (static_cast<long double>(_data));
		}
};

class date_cell : public cell
{
	private:
		time_t							_time;
		std::string						_data;

	public:
		date_cell(void) = default;
		date_cell(const date_cell& c) = default;
		date_cell(date_cell&& c) = default;
		date_cell& operator=(const date_cell& c) = default;
		~date_cell(void) = default;

		date_cell(time_t time, int row, int col, t_ptr ptr)
			: cell(row, col, ptr), _time(time)
		{
			tm							*timeinfo = gmtime(&_time);
			std::stringstream			temp;

			temp << std::to_string(timeinfo->tm_year + 1900) << "-"
				<< std::setw(2) << std::setfill('0') << timeinfo->tm_mon + 1 << "-"
				<< std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
			temp >> _data;
		}

		date_cell(std::string data, int row, int col, t_ptr ptr)
			: cell(row, col, ptr), _data(data)
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
				throw (std::runtime_error("value error"));
			if (check[month - 1] == 1 && (day < 1 || day > 31))
				throw (std::runtime_error("value error"));
			else if (check[month - 1] == 0 && (day < 1 || day > 30))
				throw std::runtime_error("value error");
			else if (check[month - 1] == -1 && (day < 1 || day > 28))
			{
				if (!(day == 29 && (!(year % 400) || (year % 100 && !(year % 4)))))
					throw (std::runtime_error("value error"));
			}
			timeinfo.tm_year = year - 1900;
			timeinfo.tm_mon = month - 1;
			timeinfo.tm_mday = day;
			timeinfo.tm_hour = 0;
			timeinfo.tm_min = 0;
			timeinfo.tm_sec = 0;
			_time = mktime(&timeinfo);
		}

		long long						get_time(void)
		{
			return (_time);
		}

		std::string						stringify(void) override
		{
			return (_data);
		}

		long double						to_numeric(void) override
		{
			return (0.0);
		}
};

class expr_cell : public cell
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
					_expr.push_back(std::to_string(circular_find(_ptr, temp)));
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
							throw (std::runtime_error("expr error"));
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
		expr_cell(void) = default;
		expr_cell(const expr_cell& c) = default;
		expr_cell(expr_cell&& c) = default;
		expr_cell& operator=(const expr_cell& c) = default;
		~expr_cell(void) = default;

		expr_cell(std::string data, int row, int col, t_ptr ptr)
			: cell(row, col, ptr), _data(data)
		{
			try
			{
				_parse();
				_calculate();
			}
			catch (std::exception& e)
			{
				throw (std::runtime_error("expr error"));
			}
		}

		std::string						stringify(void) override
		{
			return (std::to_string(_retn));
		}

		long double						to_numeric(void) override
		{
			return (_retn);
		}
};

class table
{
	protected:
		coord							_max_pos;
		t_vec							_entries;

	public:
		table(void) = default;
		table(const table& t) = default;
		table(table&& t) = default;
		table& operator=(const table& t) = default;
		virtual ~table(void) = default;

		virtual std::string				print(void) { return (""); }

		table(int max_row, int max_col)
		{
			if (max_row < 1)
				max_row = 1;
			if (max_col < 1)
				max_col = 1;
			if (max_col > 26)
				max_col = 26;
			_max_pos = std::make_pair(max_row, max_col);
			_entries.reserve(_max_pos.first * _max_pos.second);
			int							i = 0;
			int							j = 0;
			auto						cell_alloc = [&i, &j, this] () {
				auto 					value = std::make_pair(std::make_pair(i, j), std::make_shared<cell>());
				++j;
				if (j == this->_max_pos.second)
				{
					j = 0;
					++i;
				}
				return (value);
			};
			std::generate_n(std::back_inserter(_entries), _max_pos.first * _max_pos.second, cell_alloc);
		}

		coord&							get_position(void)
		{
			return (_max_pos);
		}

		t_vec&							get_entries(void)
		{
			return (_entries);
		}

		void							reg_cell(c_ptr c)
		{
			if (c->get_row() < 0
				|| c->get_row() >= _max_pos.first
				|| c->get_col() < 0
				|| c->get_col() >= _max_pos.second)
				throw (std::runtime_error("register error"));
			_entries.at(c->get_row() * _max_pos.second + c->get_col()).second = c;
		}

		long double						to_numeric(const std::string& str)
		{
			std::string_view			temp = str;
			int							col = std::toupper(temp[0]) - 'A';
			int							row = std::stoi(temp.substr(1). data());

			if (row >= 0 && row < _max_pos.first && col >= 0 && col < _max_pos.second)
				return ((_entries.at(row * _max_pos.second + col)).second->to_numeric());
			return (0.0);
		}

		long double						to_numeric(int row, int col)
		{
			if (row >= 0 && row < _max_pos.first && col >= 0 && col < _max_pos.second)
				return ((_entries.at(row * _max_pos.second + col)).second->to_numeric());
			return (0.0);

		}

		std::string						stringify(const std::string& str)
		{
			std::string_view			temp = str;
			int							col = std::toupper(temp[0]) - 'A';
			int							row = std::stoi(temp.substr(1). data());

			if (row >= 0 && row < _max_pos.first && col >= 0 && col < _max_pos.second)
				return ((_entries.at(row * _max_pos.second + col)).second->stringify());
			return ("");
		}

		std::string						stringify(int row, int col)
		{
				if (row >= 0 && row < _max_pos.first && col >= 0 && col < _max_pos.second)
				return ((_entries.at(row * _max_pos.second + col)).second->stringify());
			return ("");
		}
};

class text_table : public table
{
	private:
		std::string							divider(int val)
		{
			std::string						temp(val, '-');

			temp += std::string("\n");
			return (std::string("\n") + temp);
		}

		std::string							number(int blank, int num)
		{
			std::string						temp;
			std::string						val;

			if (num >= 0)
				val = std::to_string(num);
			temp = std::string(blank - val.length() - 1, ' ');
			temp += val + std::string(" |");
			return (std::string("| ") + temp);
		}

		std::string							content(std::vector<int>& blank, int row)
		{
			std::string						temp;
			std::string						cont;

			for (int i = 0 ; i < _max_pos.second ; ++i)
			{
				temp += std::string(" ");
				cont = (_entries.at(row * _max_pos.second + i)).second->stringify();
				if (cont.empty())
					cont = std::string(blank[i] - 2, ' ');
				else if (cont.length() < static_cast<size_t>(blank[i]))
					temp += std::string(blank[i] - cont.length() - 2, ' ');
				temp += cont;
				temp += std::string(" |");
			}
			return (temp);
		}

	public:
		text_table(void) = default;
		text_table(const text_table& t) = default;
		text_table(text_table&& t) = default;
		text_table& operator=(const text_table& t) = default;

		text_table& operator=(table& t)
		{
			_max_pos = t.get_position();
			_entries = t.get_entries();
			return (*this);
		}

		~text_table(void) = default;

		text_table(int max_row, int max_col) : table(max_row, max_col) {}

		std::string						print(void) override
		{
			std::string					total;
			int							c_max = std::to_string(_max_pos.second).length() + 2;
			int							t_len = c_max + 2;
			std::vector<int>			r_max;

			r_max.reserve(26);
			for (int j = 0 ; j < _max_pos.second ; ++j)
			{
				size_t					max_len = 0;
				for (int i = 0 ; i < _max_pos.first ; ++i)
					max_len = std::max((_entries.at(i * _max_pos.second + j)).second->stringify().length(), max_len);
				r_max.push_back(static_cast<int>(max_len + 2));
				t_len += (max_len + 3);
			}
			total += divider(t_len);
			total += number(c_max, -1);
			for (int i = 0 ; i < _max_pos.second ; ++i)
			{
				std::string				temp(r_max[i] - 2, ' ');
				temp += i + 'A';
				total += temp + std::string(" |");
			}
			total += divider(t_len);
			for (int i = 0 ; i < _max_pos.first; ++i)
			{
				total += number(c_max, i);
				total += content(r_max, i);
				total += divider(t_len);
			}
			return (total);
		}

};

class html_table : public table
{
	public:
		html_table(void) = delete;
		html_table(const html_table& t) = default;
		html_table(html_table&& t) = default;
		html_table& operator=(const html_table& t) = default;
		~html_table(void) = default;

		html_table(int max_row, int max_col) : table(max_row, max_col) {}

		std::string						print(void) override
		{
			std::string					temp("<table border='1' cellpadding='10'>");

			for (int i = 0 ; i < _max_pos.first ; ++i)
			{
				temp += std::string("<tr>");
				for (int j = 0 ; j < _max_pos.second ; ++j)
				{
					temp += std::string("<td>");
					std::string			cont = (_entries.at(i * _max_pos.second + j)).second->stringify();
					if (!cont.empty())
						temp += cont;
					temp += std::string("</td>");
				}
				temp += std::string("</tr>");
			}
			temp += std::string("</table>");
			return (temp);
		}
};

class csv_table : public table
{
	public:
		csv_table(void) = delete;
		csv_table(const csv_table& t) = default;
		csv_table(csv_table&& t) = default;
		csv_table& operator=(const csv_table& t) = default;
		~csv_table(void) = default;

		csv_table(int max_row, int max_col) : table(max_row, max_col) {}

		std::string						print(void) override
		{
			std::string					temp;

			for (int i = 0 ; i < _max_pos.first ; ++i)
			{
				for (int j = 0 ; j < _max_pos.second ; ++j)
				{
					if (j)
						temp += ",";
					std::string			cont = (_entries.at(i * _max_pos.second + j)).second->stringify();
					for (int k = 0 ; k < static_cast<int>(cont.length()) ; ++k)
					{
						if (cont[k] == '"')
							cont.insert(k++, 1, '"');
					}
					temp += std::string(1, '"') + cont + std::string(1, '"');
				}
				temp += std::string("\n");
			}
			return (temp);
		}
};

#endif
