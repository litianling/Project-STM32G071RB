/*
 * 程序清单：创建/删除、初始化线程
 *
 * 这个例子会创建三个线程，一个动态线程，两个静态线程。
 * 前两个线程一直打印计数，最后一个线程在运行完毕后自动被系统删除
 */
#include <rtthread.h>

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static rt_thread_t tid1 = RT_NULL;

/* 线程1的入口函数 */
static void thread1_entry(void *parameter)
{
	  unsigned char counter0=0;
    while (1)
    {
        /* 线程1采用低优先级运行，一直打印计数值 */
        rt_kprintf("thread1 count: %d\n", counter0++);
        rt_thread_mdelay(500);
    }
}

ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
static struct rt_thread thread2;
/* 线程2入口 */
static void thread2_entry(void *param)
{
	 unsigned char counter1=0;
    while (1)
    {
        /* 线程2采用低优先级运行，一直打印计数值 */
        rt_kprintf("thread2 count: %d\n", counter1++);
        rt_thread_mdelay(500);
    }
}

ALIGN(RT_ALIGN_SIZE)
static char thread3_stack[1024];
static struct rt_thread thread3;
/* 线程3入口 */
static void thread3_entry(void *param)
{
    unsigned char counter2=0;
			for(counter2=0;counter2<20;counter2++)
	    {
           /* 线程3采用高优先级运行，一直打印计数值 */
           rt_kprintf("thread3 count: %d\n", counter2);
      }		  
				rt_kprintf("thread3 exit\n");
}

/* 删除线程示例的初始化 */
int thread_sample(void)
{
    /* 创建线程1，名称是thread1，入口是thread1_entry*/
    tid1 = rt_thread_create("thread1",
                            thread1_entry, 
	                          RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,
                          	THREAD_TIMESLICE);
    
    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* 初始化线程2，名称是thread2，入口是thread2_entry */
    rt_thread_init(&thread2,
                   "thread2",
                   thread2_entry,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY-1, 
									 THREAD_TIMESLICE);
    rt_thread_startup(&thread2);
		
		/* 初始化线程3，名称是thread3，入口是thread3_entry */						 
    rt_thread_init(&thread3,
                   "thread3",
                   thread3_entry,
                   RT_NULL,
                   &thread3_stack[0],
                   sizeof(thread3_stack),
                   THREAD_PRIORITY - 2, 
									 THREAD_TIMESLICE);
    rt_thread_startup(&thread3);
    return 0;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(thread_sample, thread sample);
