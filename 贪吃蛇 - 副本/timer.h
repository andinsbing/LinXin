#pragma once
#include<functional>
#include<thread>
#include<utility>

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
		_state = destroyed;
		_thread.join(); 
	}
	void run()
	{
		_state = running;
	}
	void pause()
	{
		_state = paused;
	} 
	void stop()
	{
		_state = destroyed;
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
				_fun();
				break;
			case destroyed:
				return;
			default:
				break;
			}
		}
	}
	const int _interval;
	State _state; 
	const std::function<typename std::result_of<RefFun(Arg...)>::type()> _fun;
	std::thread _thread;
};
 