#include "manager.h"
#include <iostream>

Task_manager::Task_manager()
{
	task_list.clear();
}
int Task_manager::get_id(double x, double y)
{
	int id;
	id = (int)(((x + y) * 1000000) * 10) / 10;
	return id;
}
void Task_manager::add_t(double des[3], int priority)
{
	for (int i = 0; i < 3; i++) t.t_des[i] = des[i];
	t.priority = priority;
	t.t_state = 0;
	t.id = get_id(des[0], des[1]);
	t.Uid = -1;
	task_list.push_back(t);
}

bool Task_manager::del_t(int id)
{
	int i;
	if (task_list.empty()) return false;
	for (i = 0; i<task_list.size(); i++)
	{
		if (task_list[i].id == id)
		{
			task_list.erase(task_list.begin() + i);
			return true;
		}
	}
	std::cout << "No this id in tasks!\n";
	return false;
}

TASK_T Task_manager::find_task(int id)
{
	int i;
	for (i = 0; i<task_list.size(); i++)
	{
		if (task_list[i].id == id)
		{
			return task_list[i];
		}
	}
}

bool Task_manager::update_state(int id)
{
	int i;
	if (task_list.empty()) return false;
	for (i = 0; i<task_list.size(); i++)
	{
		if (task_list[i].id == id)
		{
			task_list[i].t_state = 2;
			return true;
		}
	}
	std::cout << "No this id in tasks!\n";
	return false;
}
int Task_manager::get_num_tasks()
{
	return task_list.size();
}
bool Task_manager::task_empty()
{
	if (task_list.empty()) return true;
	return false;
}
TASK_T Task_manager::get_task()
{
	int i;
	for (i = 0; i<task_list.size(); i++)
	if (task_list[i].t_state == 0)
		return task_list[i];
}
void Task_manager::task_reset()
{
	int i;
	for (i = 0; i<task_list.size(); i++)
		task_list[i].t_state = 0;
		
}
TASK_T Task_manager::assign(int index)
{
	return task_list[index];
}

UAV_manager::UAV_manager()
{
	int ability[2] = {1,1};
	for(int i = 0;i < UAV_NUM; i++) add_u(i, ability);
}
void UAV_manager::add_u(int id, int ability[2])
{
	u.id = id;
	u.is_using = 0;
	for (int i = 0; i < 2; i++) u.ability[i] = ability[i];
	uav_list.push_back(u);
}
bool UAV_manager::get_uav(int index)
{
	UAV temp;
	for (int i = 0; i < uav_list.size(); i++)
	{
		u = uav_list[i];
		if (u.ability[index] == 1 && u.is_using == 0){
			return true;
		}
	}
	u = temp;
	return false;
}
int UAV_manager::get_uav_num()
{
	int count = 0;
	for(int i = 0;i < uav_list.size(); i++)
	{
		if(uav_list[i].is_using == 0) count++;
		return count;
	}
}
void UAV_manager::update_states(int id)
{
	for (int i = 0; i < uav_list.size(); i++){
		if (uav_list[i].id == id)
			uav_list[i].is_using = 1;
	}
}
UAV UAV_manager::get_u()
{
	return u;
}