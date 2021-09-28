/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:41:49 by jseo              #+#    #+#             */
/*   Updated: 2021/09/28 16:41:06 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.hpp"

using tp::thread_pool;

int task(int i)
{
	static int						sleep_time = 3;

	printf("sleep start %d\n", i);
	std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
	printf("sleep end %d\n", i);
	return (i);
}

int main(void)
{
	thread_pool						clusters;
	std::vector<std::future<int> >	data;

	data.reserve(10);
	for (int i = 0; i < 10; ++i)
		data.push_back(clusters.enque(task, i));
	for (auto& i : data)
		printf("return %d value\n", i.get());
	return (0);
}
