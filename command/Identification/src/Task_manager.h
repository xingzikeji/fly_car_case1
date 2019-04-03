#ifndef TASK_MANAGER
#define TASK_MANAGER

#include <iostream>
struct TASK_T
{
	double t_des[3];//The coordinates of the task target
	int t_state;// 0:not start 1:have assigend 2:end
	int priority;//the priority of task,1~5
	int id;//task id,hash by des of target
};

class Task_manager
{
private:
	struct TASK_T t;
	std::vector<TASK_T> task_list;
public:
	Task_manager();
	void add_t(double des[3], int priority);
	bool del_t(int id);
	bool update_state(int id);
	int get_id(double x, double y);
	int get_num_tasks();
	TASK_T get_task();
	bool task_empty();
	void task_reset();
	TASK_T assign(int index);
};
#endif