/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cli.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:19:57 by jseo              #+#    #+#             */
/*   Updated: 2021/10/06 15:07:21 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include "h_excel.hpp"
# include <fstream>
# include <set>
# include <limits>
# include <sstream>
# include <string>
# include <string_view>

using coord = std::pair<int, int>;
using c_ptr = std::shared_ptr<cell>;

class excel
{
	private:
		coord							_max_pos;
		int								_opt;
		std::shared_ptr<table>			_ptr;
		std::string						_ext;

		static void						_information(int& status)
		{
			if (status)
				--status;
			else
				std::cout << "\E[H\E[2J\E[3J";
			std::cout << "Put the table's (Type) (Max Row) (Max Col)"
					<< "\n/* Size of Max Col is 26 (A to Z) */"
					<<	"\n/* Type 1 is Text Table */"
					<< "\n/* Type 2 is HTML Table */"
					<< "\n/* Type 3 is CSV Table */"
					<< "\n\n/* Press 0 to exit */\n\n";
		}

		static void						_arguments(int& args, const std::string_view o, const std::string_view e)
		{
			while (true)
			{
				std::cout << o << ">>\t";
				std::cin >> args;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<int>::max(), '\n');
					std::cout << e;
					continue;
				}
				break ;
			}
		}

		int								_deletion(std::vector<std::string>& chunks)
		{
			if (chunks.size() < 2)
				return (-1);
			if (!std::isalpha(chunks[1][0]) || !std::isdigit(chunks[1][1]))
				return (-1);
			try
			{
				std::string_view		val = chunks[1];
				int						col = chunks[1][0] - 'A';
				int						row = std::stoi(val.substr(1).data());
				c_ptr					data = std::make_shared<cell>(row, col, _ptr);
				_ptr->reg_cell(data);
			}
			catch (std::exception& e)
			{
				return (-1);
			}
			return (0);
		}

		int								_creation(std::vector<std::string>& chunks)
		{
			if (chunks.size() < 3)
				return (-1);
			auto						begin = std::begin(chunks) + 3;
			auto						end = std::end(chunks);
			while (begin != end)
				chunks[2] += std::string(" ") + *begin++;
			if (!std::isalpha(chunks[1][0]) || !std::isdigit(chunks[1][1]))
				return (-1);
			try
			{
				std::string_view		val = chunks[1];
				int						col = chunks[1][0] - 'A';
				int						row = std::stoi(val.substr(1).data());
				c_ptr					data;

				switch (chunks[0][3])
				{
					case 'S':
						data = std::make_shared<string_cell>(chunks[2], row, col, _ptr);
						break ;
					case 'N':
						data = std::make_shared<numeric_cell>(std::stold(chunks[2]), row, col, _ptr);
						break ;
					case 'D':
						data = std::make_shared<date_cell>(chunks[2], row, col, _ptr);
						break ;
					case 'E':
						data = std::make_shared<expr_cell>(chunks[2], row, col, _ptr);
						break ;
				}
				_ptr->reg_cell(data);
			}
			catch (std::exception& e)
			{
				return (-1);
			}
			return (0);
		}

		int								_parse_and_execute(std::string_view sv)
		{
			std::stringstream			ss(sv.data());
			std::string					temp;
			std::vector<std::string>	chunks;
			std::set<std::string>		inst{"SETS", "SETN", "SETD", "SETE", "DELC", "EXPT", "EXIT"};

			while ((ss >> temp))
				chunks.push_back(temp);
			ss.clear();
			if (chunks.empty() || inst.find(chunks[0]) == std::end(inst))
				return (-1);
			if (chunks[0] == "EXPT")
			{
				std::ofstream			out("output" + _ext);
				out << _ptr.get();
				return (1);
			}
			else if (chunks[0] == "EXIT")
				return (2);
			else if (chunks[0] == "DELC")
				return (_deletion(chunks));
			else
				return (_creation(chunks));
		}

		bool							_interaction(void)
		{
			text_table					conv;

			conv = *_ptr;
			std::cout << &conv << "\n\n";
			while (true)
			{
				int						retn;
				std::string				temp;

				std::cout << "There are 7 instructions (SETS - string) (SETN - numeric) (SETD - date) (SETE - expression) (DELC - deletion) (EXPT) (EXIT)\n\n"
					<< "set instructions are to make the cell in table\t\t->\t$(set-instruction) $(cell-name) $(content)\n"
					<< "delc instruction is to delete the cell in the table\t->\t$(delc) $(cell-name)\n"
					<< "expt instruction is to out the table to the file\t->\t$(expt)\n"
					<< "exit instruction is turn down the program\t\t->\t$(exit)\n\n";
				std::getline(std::cin >> std::ws, temp);
				std::transform(std::begin(temp), std::end(temp), std::begin(temp), [] (auto& i) { return (std::toupper(i)); });
				retn = _parse_and_execute(temp);
				conv = *_ptr;
				switch (retn)
				{
					case -1:
						std::cout << "\E[H\E[2J\E[3JInstruction is not well formatted\n\n" << &conv << "\n\n";
						break ;
					case 0:
						std::cout << "\E[H\E[2J\E[3J" << &conv << "\n\n";
						continue ;
					case 1:
						std::cout << "File out is completed\n\n";
						return (true);
					case 2:
						return (false);
				}
			}
		}

	public:
		excel() = default;
		excel(const excel& e) = default ;
		excel(excel&& e) = default;
		excel& operator=(const excel& e) = default;
		~excel() = default;

		excel(int max_row, int max_col, int option = 0)
		{
			_max_pos.first = max_row;
			_max_pos.second = max_col;
			_opt = option;
			switch (option)
			{
				case 0:
					_ptr = std::make_unique<text_table>(max_row, max_col);
					_ext = std::string(".txt");
					break ;
				case 1:
					_ptr = std::make_unique<html_table>(max_row, max_col);
					_ext = std::string(".html");
					break ;
				case 2:
					_ptr =std::make_unique<csv_table>(max_row, max_col);
					_ext = std::string(".csv");
					break ;
			}
		}

		coord							get_size(void)
		{
			return (_max_pos);
		}

		int								get_option(void)
		{
			return (_opt);
		}

		static void						init_excel(void)
		{
			const std::string_view		e1 = "Type is wrong\nSelect the option among 1 to 3\n\n";
			const std::string_view		e2 = "Max Row is wrong\nOnly numeric value available\n\n";
			const std::string_view		e3 = "Max Col is wrong\nOnly numeric value available\n\n";
			int							status = 0;
			int							option;
			int							max_row;
			int							max_col;

			while (true)
			{
				excel::_information(status);
				excel::_arguments(option, "Type\t", e1);
				if (option == 0)
					break ;
				if (option < 1 || option > 3)
				{
					++status;
					std::cout << "\E[H\E[2J\E[3J" << e1.data();
					continue;
				}
				excel::_arguments(max_row, "Max Row\t", e2);
				excel::_arguments(max_col, "Max Col\t", e3);
				excel e(max_row, max_col, option - 1);
				std::cout << "\n";
				if (!e._interaction())
					break ;
			}
		}
};

#endif
