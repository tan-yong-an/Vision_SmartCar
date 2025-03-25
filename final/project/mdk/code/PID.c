#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

_Pid_param_t pid1 = {.kp=10.5, .ki=0.3, .kd=0,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
			.p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0};
_Pid_param_t pid2 = {.kp=10.5, .ki=0.3, .kd=0,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
            .p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0};
_Pid_param_t pid3 = {.kp=10.5, .ki=0.3, .kd=0,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
            .p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0};
_Pid_param_t pid4 = {.kp=10.5, .ki=0.3, .kd=0,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
            .p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0};

_Pid_param_t pid5 = {.kp=0.26, .ki=0.2, .kd=0.65,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
            .p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0}; //MCX

_Pid_param_t pid6 = {.kp=0.15,.ki=0.03, .kd=0.15,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
            .p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0};//mini_x

_Pid_param_t pid7 = {.kp=0.15,.ki=0.03, .kd=0.15,.low_pass=1,.out_d=0,.out_i=0,.out_p=0,\
            .p_max=PWM_DUTY_MAX,.i_max=PWM_DUTY_MAX,.d_max=PWM_DUTY_MAX,.pre_error=0,.pre_pre_error=0};//mini_y
			

// 常规PID 位置
float common_pid(_Pid_param_t *pid, float error) 
{
    pid->out_d = (error - pid->out_p);
    pid->out_p = error;
    pid->out_i += error;
    return limit(pid->kp * pid->out_p + pid->kd * pid->out_d,130);// pid->ki * pid->out_i;// + pid->kd * pid->out_d;
}

float new_common_pid(_Pid_param_t *pid, float error) {
    pid->out_d = (error - pid->out_p);
    pid->out_p = error;
    pid->out_i += error;
    return limit(pid->kp * pid->out_p + pid->kd * pid->out_d,20);// pid->ki * pid->out_i;// + pid->kd * pid->out_d;
}

// 增量式PID
float increment_pid(_Pid_param_t *pid, float error) 
{
    pid->out_p = pid->kp * (error - pid->pre_error);
    pid->out_i =(pid->ki) * error;
    pid->out_d =pid->kd*(error-2*pid->pre_error+pid->pre_pre_error);
    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;
	  return limit(pid->out_p + pid->out_i+pid->out_d ,130);
}

float limit(float a,float b)
{
	if (a>=0)
    {
        if (a>=b)
        {
            a = b;
        }
    }
    else if (a<=0)
    {
        if (a<-b)
        {
            a = -b;
        }
    }
    return a;
}

float PID_Set(int PID_target,int PID_actual)   //增量式
{
	
	float Kp =1.88,Ki =0.15;  //2.88
	static int error,err_last;
	static float out;
	
    error=PID_target-PID_actual;
    out += Kp * (error - err_last) + Ki * error;
	err_last = error; 
	if(out>=400) out=400;
	if(out<=-400) out = -400;
    return out;
}
