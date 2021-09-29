/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_thread_pool.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:33:50 by jseo              #+#    #+#             */
/*   Updated: 2021/09/29 16:52:38 by jseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <chrono>
# include <condition_variable>
# include <cstdio>
# include <functional>
# include <future>
# include <mutex>
# include <queue>
# include <thread>
# include <vector>

namespace tp
{
	class thread_pool
	{
		private:
			static const size_t						_default_size = 4;

			bool									_stop;
			size_t									_num_threads;
			std::vector<std::thread>				_worker_threads;
			std::condition_variable					_cv_jobs;
			std::mutex								_m_jobs;
			std::queue<std::function<void()> >		_jobs;

			void _run_thread();

		public:
			thread_pool();
			thread_pool(size_t num_threads);
			~thread_pool();

			template <typename F, typename... Args>
			std::future<typename std::result_of<F(Args...)>::type> enque(F&& f, Args&&... args);
	};

	template <typename F, typename... Args>
	std::future<typename std::result_of<F(Args...)>::type> thread_pool::enque(F&& f, Args&&... args)
	{
		if (_stop)
			throw std::runtime_error("Thread Pool Stopped");
		using return_type = typename std::result_of<F(Args...)>::type;
		auto wrapped_job = std::make_shared<std::packaged_task<return_type()> >(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		std::future<return_type> future_job = wrapped_job->get_future();
		{
			std::lock_guard<std::mutex> lock(_m_jobs);
			_jobs.push([wrapped_job] () { (*wrapped_job)(); });
		}
		_cv_jobs.notify_one();
		return (future_job);
	}
}

#endif
