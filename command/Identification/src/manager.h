#ifndef TASK_MANAGER
#define TASK_MANAGER
#define UAV_NUM 4//not include the center
#include <iostream>
struct TASK_T
{
	double t_des[3];//The coordinates of the task target
	int t_state;// 0:not start 1:have assigend 2:end
	int priority;//the priority of task,1~5
	int id;//task id,hash by des of target
	int Uid;//who excute the task
};

struct UAV
{
	int id;//unique for each one,1,2,3,4...
	int ability[2];//0:Find,1:Gan
	int is_using;//The state of uav
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
	TASK_T find_task(int id);
};

class UAV_manager
{
private:
	struct UAV u;
    std::vector<UAV> uav_list;
public:
	UAV_manager();//finish uav add
	void add_u(int id, int ability[2]);//tool for UAV_manager()
	bool get_uav(int index);//index is the ability
	int get_uav_num();//get can be used uav num
	void update_states(int id);//is_using 0->1
	UAV get_u();
};
#endif