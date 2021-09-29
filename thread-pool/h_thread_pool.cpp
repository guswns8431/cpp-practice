/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_thread_pool.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:19:42 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 16:52:40 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_thread_pool.hpp"

using tp::thread_pool;

void thread_pool::_run_thread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(_m_jobs);
		_cv_jobs.wait(lock, [this] () { return (!this->_jobs.empty() || this->_stop); } );
		if (_stop && _jobs.empty())
			return ;
		std::function<void()> current = std::move(_jobs.front());
		_jobs.pop();
		lock.unlock();
		current();
	}
}

thread_pool::thread_pool()
	: _stop(false), _num_threads(_default_size)
{
	_worker_threads.reserve(_num_threads);
	for (size_t i = 0 ; i < _num_threads ; ++i)
		_worker_threads.push_back(std::thread( [this] () { this->_run_thread(); } ));
}

thread_pool::thread_pool(size_t num_threads)
	: _stop(false), _num_threads(num_threads)
{
	_worker_threads.reserve(_num_threads);
	for (size_t i = 0 ; i < _num_threads ; ++i)
		_worker_threads.push_back(std::thread( [this] () { this->_run_thread(); } ));
}

thread_pool::~thread_pool()
{
	_stop = true;
	_cv_jobs.notify_all();
	for (auto& t : _worker_threads)
		t.join();
}
