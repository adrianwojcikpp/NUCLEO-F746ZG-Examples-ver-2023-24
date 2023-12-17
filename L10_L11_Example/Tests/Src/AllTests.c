#include "usart.h"

#include "CuTest.h"

CuSuite* CuGetCmsisDspSuite(void);

int RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CuGetCmsisDspSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	HAL_UART_Transmit(&huart3, (uint8_t*)output->buffer, output->length, 0xffff);
	return suite->failCount;
}
