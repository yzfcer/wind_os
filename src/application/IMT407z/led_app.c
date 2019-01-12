#include "led.h"
#include "wind_debug.h"
#include "wind_timer.h"
#include "wind_chdev.h"
#if (WIND_TIMER_SUPPORT && WIND_DRVFRAME_SUPPORT)
void led0_timer(w_timer_s *timer,void *arg)
{
    w_chdev_s *dev;
    w_uint8_t stat;
    dev = wind_chdev_get("led0");
    wind_chdev_read(dev,&stat,1);
    
    if(stat)
    {
        stat = 0;
        wind_chdev_write(dev,&stat,1);
        wind_timer_set_period(timer,1000);
    }
    else
    {
        stat = 1;
        wind_chdev_write(dev,&stat,1);
        wind_timer_set_period(timer,100);
    }
}


void led_start(void)
{
    w_timer_s *ledtmr;
    w_chdev_s *dev;
    dev = wind_chdev_get("led0");
    wind_chdev_open(dev);
    ledtmr = wind_timer_create("led0tmr",100,led0_timer,W_NULL,1,1);
    if(ledtmr == W_NULL)
        wind_error("create led timer failed.");
}
#else
void led_start(void) {}
#endif
