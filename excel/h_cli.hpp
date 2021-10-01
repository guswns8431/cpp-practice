/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cli.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:19:57 by jseo              #+#    #+#             */
/*   Updated: 2021/10/01 23:14:35 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include "h_excel.hpp"
# include <limits>

using coord = std::pair<int, int>;

class excel
{
	private:
		coord							_max_pos;
		int								_opt;
		std::shared_ptr<table>			_ptr;

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
					<< "\n/* Type 3 is CSV Table */\n\n";
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

		int								_parse_and_execute(std::string_view sv)
		{

		}

		bool							_interaction(void)
		{
			while (true)
			{
				int						retn;
				std::string				temp;

				std::getline(std::cin, temp);
				std::transform(std::begin(temp), std::end(temp), std::begin(temp), [] (auto& i) { return (std::toupper(i)); });
				retn = _parse_and_execute(temp);
				std::cout << _ptr.get() << "\n\n";
				switch (retn)
				{
					case 0:
						continue ;
					case 1:
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
					break ;
				case 1:
					_ptr = std::make_unique<html_table>(max_row, max_col);
					break ;
				case 2:
					_ptr =std::make_unique<csv_table>(max_row, max_col);
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
				if (option < 1 || option > 3)
				{
					++status;
					std::cout << "\E[H\E[2J\E[3J" << e1.data();
					continue;
				}
				excel::_arguments(max_row, "Max Row\t", e2);
				excel::_arguments(max_col, "Max Col\t", e3);
				excel e(max_row, max_col, option);
				if (!e._interaction())
					break ;
			}
		}
};

#endif
