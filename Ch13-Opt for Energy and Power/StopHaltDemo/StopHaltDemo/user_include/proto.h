/* function prototypes */
void sim_motion(void);
void Find_Nearest_Waypoint(float cur_pos_lat, float cur_pos_lon, 
                            float * distance, float * bearing, 
	                          char  * * name);

float cos_32(float x);
float cos_52(float x);
double cos_73(double x);
double cos_121(double x);

float sin_32(float x);
float sin_52(float x);
double sin_73(double x);
double sin_121(double x);
