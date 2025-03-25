#ifndef  _PID_h_
#define  _PID_h_

typedef struct {
    float kp;    //P
    float ki;    //I
    float kd;    //D
    float i_max; //i p dÏÞ·ù
    float p_max; 
    float d_max; 

    float low_pass;//ÔÝÊ±Î´ÓÃ

    float out_p;
    float out_i;
    float out_d;
    
    float error;
    float pre_error;
    float pre_pre_error;
} _Pid_param_t;

extern _Pid_param_t pid1,pid2,pid3,pid4,pid5,pid6,pid7;

float common_pid(_Pid_param_t *pid, float error);
float new_common_pid(_Pid_param_t *pid, float error);
float increment_pid(_Pid_param_t *pid, float error);

float limit(float a,float b);

float PID_Set(int PID1_target,int PID1_actual);


#endif