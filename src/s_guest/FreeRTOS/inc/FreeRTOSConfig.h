#ifndef _FREERTOSCONFIG_H
#define _FREERTOSCONFIG_H

#define XPAR_PS7_SCUGIC_0_BASEADDR 0xF8F00000U

#define configUSE_PREEMPTION 1

#define configUSE_MUTEXES 1

#define configUSE_RECURSIVE_MUTEXES 0

#define configUSE_COUNTING_SEMAPHORES 1

#define configUSE_TIMERS 1

#define configUSE_TIME_SLICING 1

#define configUSE_IDLE_HOOK 1

#define configUSE_TICK_HOOK 0

#define configUSE_MALLOC_FAILED_HOOK 1

#define configSUPPORT_STATIC_ALLOCATION 0

#define configUSE_TRACE_FACILITY 1

#define configUSE_16_BIT_TICKS 0

#define configUSE_APPLICATION_TASK_TAG 0

#define configUSE_CO_ROUTINES 0

#define configTICK_RATE_HZ (1)

#define configCPU_CLOCK_HZ 650000000UL

#define configPERIPHERAL_CLOCK_HZ  				( 33333000UL )

#define configMAX_PRIORITIES (7)

#define configMAX_CO_ROUTINE_PRIORITIES 2

#define configMINIMAL_STACK_SIZE ( ( unsigned short ) 250)

#define configTOTAL_HEAP_SIZE ( ( size_t ) ( 8192 ) )
// #define configTOTAL_HEAP_SIZE ( ( size_t ) ( 95 * 1024) )

#define configMAX_TASK_NAME_LEN 10

#define configIDLE_SHOULD_YIELD 1

#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)

#define configTIMER_QUEUE_LENGTH 10

#define configTIMER_TASK_STACK_DEPTH ((configMINIMAL_STACK_SIZE) * 2)

#define configUSE_QUEUE_SETS 1

#define configCHECK_FOR_STACK_OVERFLOW 2


#define configQUEUE_REGISTRY_SIZE 10

#define configUSE_STATS_FORMATTING_FUNCTIONS 1

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 0
#define configUSE_TASK_FPU_SUPPORT 1

#define configUSE_TICKLESS_IDLE	0
#define configTASK_RETURN_ADDRESS    NULL
#define INCLUDE_vTaskPrioritySet             1
#define INCLUDE_uxTaskPriorityGet            1
#define INCLUDE_vTaskDelete                  1
#define INCLUDE_vTaskCleanUpResources        1
#define INCLUDE_vTaskSuspend                 1
#define INCLUDE_vTaskDelayUntil              1
#define INCLUDE_vTaskDelay                   1
#define INCLUDE_eTaskGetState                1
#define INCLUDE_xTimerPendFunctionCall       1
#define INCLUDE_pcTaskGetTaskName            1
#define configMAX_API_CALL_INTERRUPT_PRIORITY (1)

#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0

#define configINTERRUPT_CONTROLLER_BASE_ADDRESS         ( 0xF8F01000)
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET ( -0xf00 )


#define configUNIQUE_INTERRUPT_PRIORITIES                32
#define configEOI_ADDRESS                               ( 0xF8F00110 )

void vFreeRTOS_SetupTickInterrupt( void );
void vFreeRTOS_ClearTickInterrupt( void );

#define configSETUP_TICK_INTERRUPT() vFreeRTOS_SetupTickInterrupt()
#define configCLEAR_TICK_INTERRUPT()	vFreeRTOS_ClearTickInterrupt()

#endif
