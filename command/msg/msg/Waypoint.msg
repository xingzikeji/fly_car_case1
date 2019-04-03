# New waypoint, input to path manager

# @warning w and Va_d always have to be valid; the chi_d is optional.
float32[3] w		# Waypoint in local NED (m) target location

# add by kobe
float32 lat		# latitude
float32 lon		# longtitude
 
float32 chi_d		# Desired course at this waypoint (rad)
bool chi_valid		# Desired course valid (dubin or fillet paths)
float32 Va_d		# Desired airspeed (m/s)
bool set_current	# Sets this waypoint to be executed now! Starts a new list
bool landing            #
bool takeoff            #
bool clear_wp_list  # Removes all waypoints and returns to origin.  The rest of
int64 uid           #Record the UAV id who get the waypoint
int64 result        #task result 0:fail,1:success,-1:not use
int64 tid           #the task id
int64 t_state       #the task state

