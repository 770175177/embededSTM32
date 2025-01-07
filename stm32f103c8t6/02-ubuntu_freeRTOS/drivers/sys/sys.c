#include "sys.h"

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

void MSR_MSP(u32 addr) 
{
	__ASM volatile("MSR MSP, r0"); 			// set Main Stack value
	__ASM volatile("BX r14");
}
