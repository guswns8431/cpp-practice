#include <iostream>
#include <vector>

std::vector<std::vector<std::string> >			g_storage;
std::vector<std::string>						g_answer;

void	pre_setting(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
}

void	input_action(void)
{
	int											size;

	std::cin >> size;
	g_storage = std::vector<std::vector<std::string> >(size);
	for (auto& i : g_storage)
	{
		std::cin >> size;
		i.resize(size);
		for (auto& j : i)
			std::cin >> j;
	}
}

bool	check_palin(std::string str)
{
	int										size = str.size() / 2;
	auto									iter = str.rbegin();

	for (auto i = str.begin(); i < str.begin() + size; ++i)
	{
		if (*i != *iter)
			return (false);
		++iter;
	}
	return (true);
}

void	find_palin(std::vector<std::string>& v)
{
	for (auto& i : v)
	{
		for (auto& j : v)
		{
			if (&i == &j)
                continue ;
			if (check_palin(i + j))
			{
				g_answer.push_back(i + j);
				return ;
			}
		}
	}
	g_answer.push_back("0");
}

void	solution(void)
{
	for (auto& i : g_storage)
		find_palin(i);
}

void	output_action(void)
{
	for (auto& i : g_answer)
		std::cout << i << '\n';
}

int		main(void)
{
	pre_setting();
	input_action();
	solution();
	output_action();
	return (0);
}
