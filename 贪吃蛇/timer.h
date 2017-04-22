#pragma once
#include<functional>
#include<thread>
#include<utility> 
#include<mutex>

template<class Fn, class... Arg>
class Timer
{ 
	typedef decltype(std::declval<Fn>()) RefFun;
public:
	enum State
	{
		ready,
		running,
		paused,
		destroyed
	};
public:
	//if arg is T&,Arg should be T&, if arg is T&&,Arg should be T
	Timer(int millisecond, RefFun&& fun, Arg&&... arg) :
		_interval(millisecond),
		_state(ready),
		_fun(std::bind(std::forward<RefFun>(fun), std::forward<Arg>(arg)...)),
		_thread(std::bind(&Timer<Fn,Arg...>::caller,this))
	{ 
	}
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	~Timer()
	{
		finish();
		_thread.join(); 
	} 
	void run()
	{
		setState(running);
	} 
	//puase event loop immediately after the latest event finished
	void pause()
	{
		setState(paused);
	}
	//break event loop
	void finish() 
	{
		setState(destroyed);
	}
	State state()const
	{
		return this->_state;
	}
private: 
	void caller()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(_interval));
			switch (_state)
			{
			case ready: 
			case paused:
				std::this_thread::yield();
				break;
			case running:
				_loopSafeMutex.lock();
				_fun();
				_loopSafeMutex.unlock();
				break;
			case destroyed:
				return;
			default:
				break;
			}
		}
	}
	//event loop safe
	void setState(State state)
	{ 
		_loopSafeMutex.lock();
		_state = state;
		_loopSafeMutex.unlock();
	}
	const int _interval;
	State _state; 
	const std::function<typename std::result_of<RefFun(Arg...)>::type()> _fun;
	std::thread _thread;
	std::mutex _loopSafeMutex;
};
 