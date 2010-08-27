#ifndef _Timer_H_
#define _Timer_H_

class Timer
{
private:
	double start_time;
	void setTime();
public:
	Timer();
	void Touch() { setTime(); }
	double Ago();
};

#endif
