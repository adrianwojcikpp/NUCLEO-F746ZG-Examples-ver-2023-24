#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "CuTest.h"
#include "arm_math.h"

#define LEN(x) (sizeof(x)/sizeof(x[0]))

/**
 * @brief Root mean square error
 * @param[in] yref : Reference vector
 * @param[in] y    : Input vector
 * @param[in] len  : Vectors length
 * @return Root mean square error: sqrt(sum( (yref - y)^2 ))
 */
float32_t RMSE(const float32_t* y, const float32_t* yref, const uint32_t len)
{
  float32_t err[len];
  arm_sub_f32(yref, y, err, len);
  float32_t rmse;
  arm_rms_f32(err, len, &rmse);
  return rmse;
}

void TestCmsisDsp_RMSE(CuTest *tc)
{
  const float32_t a[] = { 0.8150f, 0.9060f, 0.1270f };
  const float32_t b[] = { 0.9130f, 0.6320f, 0.0980f };
  const float32_t c_ref = 0.1688402f;

  // CMSIS DSP implementation of root mean square error
  float32_t c = RMSE(a, b, 3);

  CuAssertDblEquals(tc, c_ref, c, 1e-7f);
}

#include "A_mat.h"
#include "B_mat.h"
#include "C_mat.h"
#include "C_REF_mat.h"

void TestCmsisDsp_MAT_MULT(CuTest *tc)
{
  // Initialize matrix instances
  arm_mat_init_f32(&A, A_ROWS, A_COLS, A_DATA);
  arm_mat_init_f32(&B, B_ROWS, B_COLS, B_DATA);
  arm_mat_init_f32(&C, C_ROWS, C_COLS, C_DATA);

  arm_status status = arm_mat_mult_f32(&A, &B, &C);

  CuAssertIntEquals(tc, ARM_MATH_SUCCESS, status);

  float32_t rmse = RMSE((float32_t*)C_REF_DATA, C.pData, C_ROWS*C_COLS);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-7f);
}


#include "FIR1_fir.h"
#include "X1_vec.h"
#include "Y1_vec.h"
#include "Y1_REF_vec.h"

#define USE_SWV_FIR 0

#if USE_SWV_FIR
float32_t SWV_FIR1;
#include "stm32f7xx_hal.h"
#endif

void TestCmsisDsp_FIR(CuTest *tc)
{
  // Initialize FIR filter instance
  arm_fir_init_f32(&FIR1, FIR1_NUM_TAPS, FIR1_COEFFS, FIR1_STATE, FIR1_BLOCK_SIZE);

  // Filter test signal sample by sample
  for(uint32_t i = 0; i < X1_LEN; i++)
  {
    arm_fir_f32(&FIR1, &X1[i], &Y1[i], FIR1_BLOCK_SIZE);
    #if USE_SWV_FIR
    SWV_FIR1 = Y1[i];
    HAL_Delay(0);
    #endif
  }

  float32_t rmse = RMSE(Y1_REF, Y1, Y1_LEN);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-6f);
}

#include "IIR1_biquad_df1.h"
#include "X2_vec.h"
#include "Y2_vec.h"
#include "Y2_REF_vec.h"

#define USE_SWV_IIR 0

#if USE_SWV_IIR
float32_t SWV_IIR1;
#include "stm32f7xx_hal.h"
#endif

void TestCmsisDsp_IIR(CuTest *tc)
{
  // Initialize FIR filter instance
  arm_biquad_cascade_df1_init_f32(&IIR1, IIR1_NUM_STAGES, IIR1_COEFFS, IIR1_STATE);

  // Filter test signal sample by sample
  for(uint32_t i = 0; i < X2_LEN; i++)
  {
    arm_biquad_cascade_df1_f32(&IIR1, &X2[i], &Y2[i], IIR1_BLOCK_SIZE);
    #if USE_SWV_IIR
    SWV_IIR1 = Y2[i];
    HAL_Delay(0);
    #endif
  }

  float32_t rmse = RMSE(Y2_REF, Y2, Y2_LEN);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-4f);
}

#include "PID1_pid.h"
#include "X3_vec.h"
#include "Y3_vec.h"
#include "Y3_REF_vec.h"

#define USE_SWV_PID 0

#if USE_SWV_PID
float32_t SWV_PID1;
#include "stm32f7xx_hal.h"
#endif

void TestCmsisDsp_PID(CuTest *tc)
{
  // Set PID controller gains
  PID1.Kp = PID1_KP;
  PID1.Ki = PID1_KI;
  PID1.Kd = PID1_KD;

  // Initialize PID controller instance */
  /** This function computes the structure fields: A0, A1 A2
   *  using the proportional gain (Kp), integral gain (Ki)
   *  and derivative gain (Kd); also sets the state variables to zeros.
   */
  arm_pid_init_f32(&PID1, 1);

  /* Generate control signal sample by sample */
  for(uint32_t i = 0; i < X3_LEN; i++)
  {
    Y3[i] = arm_pid_f32(&PID1, X3[i]);
    #if USE_SWV_PID
    SWV_PID1 = Y3[i];
    HAL_Delay(0);
    #endif
  }

  float32_t rmse = RMSE(Y3_REF, Y3, Y3_LEN);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-10f);
}


CuSuite* CuGetCmsisDspSuite(void)
{
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestCmsisDsp_RMSE);
  // L10: CMSIS DSP pt. 1
  SUITE_ADD_TEST(suite, TestCmsisDsp_MAT_MULT);
  SUITE_ADD_TEST(suite, TestCmsisDsp_FIR);
  // L11: CMSIS DSP pt. 2
  SUITE_ADD_TEST(suite, TestCmsisDsp_IIR);
  SUITE_ADD_TEST(suite, TestCmsisDsp_PID);

  return suite;
}
