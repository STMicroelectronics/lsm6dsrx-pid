/**
  ******************************************************************************
  * @file    lsm6dsrx_reg.c
  * @author  Sensors Software Solution Team
  * @brief   LSM6DSRX driver file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "lsm6dsrx_reg.h"

/**
  * @defgroup    LSM6DSRX
  * @brief       This file provides a set of functions needed to drive the
  *              lsm6dsrx enhanced inertial module.
  * @{
  *
  */

/**
  * @defgroup    LSM6DSRX_Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak lsm6dsrx_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                 uint8_t *data,
                                 uint16_t len)
{
  int32_t ret;

  if (ctx == NULL)
  {
    return -1;
  }

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak lsm6dsrx_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                  uint8_t *data,
                                  uint16_t len)
{
  int32_t ret;

  if (ctx == NULL)
  {
    return -1;
  }

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup    LSM6DSRX_Sensitivity
  * @brief       These functions convert raw-data into engineering units.
  * @{
  *
  */

float_t lsm6dsrx_from_fs2g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.061f);
}

float_t lsm6dsrx_from_fs4g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.122f);
}

float_t lsm6dsrx_from_fs8g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.244f);
}

float_t lsm6dsrx_from_fs16g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.488f);
}

float_t lsm6dsrx_from_fs125dps_to_mdps(int16_t lsb)
{
  return ((float_t)lsb * 4.375f);
}

float_t lsm6dsrx_from_fs250dps_to_mdps(int16_t lsb)
{
  return ((float_t)lsb * 8.75f);
}

float_t lsm6dsrx_from_fs500dps_to_mdps(int16_t lsb)
{
  return ((float_t)lsb * 17.50f);
}

float_t lsm6dsrx_from_fs1000dps_to_mdps(int16_t lsb)
{
  return ((float_t)lsb * 35.0f);
}

float_t lsm6dsrx_from_fs2000dps_to_mdps(int16_t lsb)
{
  return ((float_t)lsb * 70.0f);
}

float_t lsm6dsrx_from_fs4000dps_to_mdps(int16_t lsb)
{
  return ((float_t)lsb * 140.0f);
}

float_t lsm6dsrx_from_lsb_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 256.0f) + 25.0f);
}

uint64_t lsm6dsrx_from_lsb_to_nsec(uint32_t lsb)
{
  return ((uint64_t)lsb * 25000ULL);
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM9DS1_Data_generation
  * @brief      This section groups all the functions concerning data
  *             generation
  * @{
  *
  */

/**
  * @brief  Accelerometer full-scale selection[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fs_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_full_scale_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_fs_xl_t val)
{
  lsm6dsrx_ctrl1_xl_t ctrl1_xl;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_XL,
                          (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.fs_xl = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer full-scale selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fs_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_full_scale_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_fs_xl_t *val)
{
  lsm6dsrx_ctrl1_xl_t ctrl1_xl;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_XL,
                          (uint8_t *)&ctrl1_xl, 1);

  switch (ctrl1_xl.fs_xl)
  {
    case LSM6DSRX_2g:
      *val = LSM6DSRX_2g;
      break;

    case LSM6DSRX_16g:
      *val = LSM6DSRX_16g;
      break;

    case LSM6DSRX_4g:
      *val = LSM6DSRX_4g;
      break;

    case LSM6DSRX_8g:
      *val = LSM6DSRX_8g;
      break;

    default:
      *val = LSM6DSRX_2g;
      break;
  }

  return ret;
}

/**
  * @brief  Accelerometer UI data rate selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odr_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_data_rate_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_odr_xl_t val)
{
  lsm6dsrx_odr_xl_t odr_xl =  val;
  lsm6dsrx_emb_fsm_enable_t fsm_enable;
  lsm6dsrx_fsm_odr_t fsm_odr;
  uint8_t mlc_enable;
  lsm6dsrx_mlc_odr_t mlc_odr;
  lsm6dsrx_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  /* Check the Finite State Machine data rate constraints */
  ret =  lsm6dsrx_fsm_enable_get(ctx, &fsm_enable);

  if (ret == 0)
  {
    if ((fsm_enable.fsm_enable_a.fsm1_en  |
         fsm_enable.fsm_enable_a.fsm2_en  |
         fsm_enable.fsm_enable_a.fsm3_en  |
         fsm_enable.fsm_enable_a.fsm4_en  |
         fsm_enable.fsm_enable_a.fsm5_en  |
         fsm_enable.fsm_enable_a.fsm6_en  |
         fsm_enable.fsm_enable_a.fsm7_en  |
         fsm_enable.fsm_enable_a.fsm8_en  |
         fsm_enable.fsm_enable_b.fsm9_en  |
         fsm_enable.fsm_enable_b.fsm10_en |
         fsm_enable.fsm_enable_b.fsm11_en |
         fsm_enable.fsm_enable_b.fsm12_en |
         fsm_enable.fsm_enable_b.fsm13_en |
         fsm_enable.fsm_enable_b.fsm14_en |
         fsm_enable.fsm_enable_b.fsm15_en |
         fsm_enable.fsm_enable_b.fsm16_en) == PROPERTY_ENABLE)
    {
      ret =  lsm6dsrx_fsm_data_rate_get(ctx, &fsm_odr);

      if (ret == 0)
      {
        switch (fsm_odr)
        {
          case LSM6DSRX_ODR_FSM_12Hz5:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_12Hz5;
            }

            else
            {
              odr_xl = val;
            }

            break;

          case LSM6DSRX_ODR_FSM_26Hz:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_26Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_12Hz5)
            {
              odr_xl = LSM6DSRX_XL_ODR_26Hz;
            }

            else
            {
              odr_xl = val;
            }

            break;

          case LSM6DSRX_ODR_FSM_52Hz:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_52Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_12Hz5)
            {
              odr_xl = LSM6DSRX_XL_ODR_52Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_26Hz)
            {
              odr_xl = LSM6DSRX_XL_ODR_52Hz;
            }

            else
            {
              odr_xl = val;
            }

            break;

          case LSM6DSRX_ODR_FSM_104Hz:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_12Hz5)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_26Hz)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_52Hz)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else
            {
              odr_xl = val;
            }

            break;

          default:
            odr_xl = val;
            break;
        }
      }
    }
  }

  /* Check the Machine Learning Core data rate constraints */
  mlc_enable = PROPERTY_DISABLE;

  if (ret == 0)
  {
    ret =  lsm6dsrx_mlc_get(ctx, &mlc_enable);

    if (mlc_enable == PROPERTY_ENABLE)
    {
      ret =  lsm6dsrx_mlc_data_rate_get(ctx, &mlc_odr);

      if (ret == 0)
      {
        switch (mlc_odr)
        {
          case LSM6DSRX_ODR_PRGS_12Hz5:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_12Hz5;
            }

            else
            {
              odr_xl = val;
            }

            break;

          case LSM6DSRX_ODR_PRGS_26Hz:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_26Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_12Hz5)
            {
              odr_xl = LSM6DSRX_XL_ODR_26Hz;
            }

            else
            {
              odr_xl = val;
            }

            break;

          case LSM6DSRX_ODR_PRGS_52Hz:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_52Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_12Hz5)
            {
              odr_xl = LSM6DSRX_XL_ODR_52Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_26Hz)
            {
              odr_xl = LSM6DSRX_XL_ODR_52Hz;
            }

            else
            {
              odr_xl = val;
            }

            break;

          case LSM6DSRX_ODR_PRGS_104Hz:
            if (val == LSM6DSRX_XL_ODR_OFF)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_12Hz5)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_26Hz)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else if (val == LSM6DSRX_XL_ODR_52Hz)
            {
              odr_xl = LSM6DSRX_XL_ODR_104Hz;
            }

            else
            {
              odr_xl = val;
            }

            break;

          default:
            odr_xl = val;
            break;
        }
      }
    }
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_XL,
                            (uint8_t *)&ctrl1_xl, 1);
  }

  if (ret == 0)
  {
    ctrl1_xl.odr_xl = (uint8_t)odr_xl;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer UI data rate selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_data_rate_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_odr_xl_t *val)
{
  lsm6dsrx_ctrl1_xl_t ctrl1_xl;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_XL,
                          (uint8_t *)&ctrl1_xl, 1);

  switch (ctrl1_xl.odr_xl)
  {
    case LSM6DSRX_XL_ODR_OFF:
      *val = LSM6DSRX_XL_ODR_OFF;
      break;

    case LSM6DSRX_XL_ODR_12Hz5:
      *val = LSM6DSRX_XL_ODR_12Hz5;
      break;

    case LSM6DSRX_XL_ODR_26Hz:
      *val = LSM6DSRX_XL_ODR_26Hz;
      break;

    case LSM6DSRX_XL_ODR_52Hz:
      *val = LSM6DSRX_XL_ODR_52Hz;
      break;

    case LSM6DSRX_XL_ODR_104Hz:
      *val = LSM6DSRX_XL_ODR_104Hz;
      break;

    case LSM6DSRX_XL_ODR_208Hz:
      *val = LSM6DSRX_XL_ODR_208Hz;
      break;

    case LSM6DSRX_XL_ODR_416Hz:
      *val = LSM6DSRX_XL_ODR_416Hz;
      break;

    case LSM6DSRX_XL_ODR_833Hz:
      *val = LSM6DSRX_XL_ODR_833Hz;
      break;

    case LSM6DSRX_XL_ODR_1666Hz:
      *val = LSM6DSRX_XL_ODR_1666Hz;
      break;

    case LSM6DSRX_XL_ODR_3332Hz:
      *val = LSM6DSRX_XL_ODR_3332Hz;
      break;

    case LSM6DSRX_XL_ODR_6667Hz:
      *val = LSM6DSRX_XL_ODR_6667Hz;
      break;

    case LSM6DSRX_XL_ODR_1Hz6:
      *val = LSM6DSRX_XL_ODR_1Hz6;
      break;

    default:
      *val = LSM6DSRX_XL_ODR_OFF;
      break;
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fs_g in reg CTRL2_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_full_scale_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_fs_g_t val)
{
  lsm6dsrx_ctrl2_g_t ctrl2_g;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_G,
                          (uint8_t *)&ctrl2_g, 1);

  if (ret == 0)
  {
    ctrl2_g.fs_g = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL2_G,
                             (uint8_t *)&ctrl2_g, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fs_g in reg CTRL2_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_full_scale_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_fs_g_t *val)
{
  lsm6dsrx_ctrl2_g_t ctrl2_g;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_G,
                          (uint8_t *)&ctrl2_g, 1);

  switch (ctrl2_g.fs_g)
  {
    case LSM6DSRX_125dps:
      *val = LSM6DSRX_125dps;
      break;

    case LSM6DSRX_250dps:
      *val = LSM6DSRX_250dps;
      break;

    case LSM6DSRX_500dps:
      *val = LSM6DSRX_500dps;
      break;

    case LSM6DSRX_1000dps:
      *val = LSM6DSRX_1000dps;
      break;

    case LSM6DSRX_2000dps:
      *val = LSM6DSRX_2000dps;
      break;

    case LSM6DSRX_4000dps:
      *val = LSM6DSRX_4000dps;
      break;

    default:
      *val = LSM6DSRX_125dps;
      break;
  }

  return ret;
}

/**
  * @brief  Gyroscope data rate.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odr_g in reg CTRL2_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_data_rate_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_odr_g_t val)
{
  lsm6dsrx_odr_g_t odr_gy =  val;
  lsm6dsrx_emb_fsm_enable_t fsm_enable;
  lsm6dsrx_fsm_odr_t fsm_odr;
  uint8_t mlc_enable;
  lsm6dsrx_mlc_odr_t mlc_odr;
  lsm6dsrx_ctrl2_g_t ctrl2_g;
  int32_t ret;

  /* Check the Finite State Machine data rate constraints */
  ret =  lsm6dsrx_fsm_enable_get(ctx, &fsm_enable);

  if (ret == 0)
  {
    if ((fsm_enable.fsm_enable_a.fsm1_en  |
         fsm_enable.fsm_enable_a.fsm2_en  |
         fsm_enable.fsm_enable_a.fsm3_en  |
         fsm_enable.fsm_enable_a.fsm4_en  |
         fsm_enable.fsm_enable_a.fsm5_en  |
         fsm_enable.fsm_enable_a.fsm6_en  |
         fsm_enable.fsm_enable_a.fsm7_en  |
         fsm_enable.fsm_enable_a.fsm8_en  |
         fsm_enable.fsm_enable_b.fsm9_en  |
         fsm_enable.fsm_enable_b.fsm10_en |
         fsm_enable.fsm_enable_b.fsm11_en |
         fsm_enable.fsm_enable_b.fsm12_en |
         fsm_enable.fsm_enable_b.fsm13_en |
         fsm_enable.fsm_enable_b.fsm14_en |
         fsm_enable.fsm_enable_b.fsm15_en |
         fsm_enable.fsm_enable_b.fsm16_en) == PROPERTY_ENABLE)
    {
      ret =  lsm6dsrx_fsm_data_rate_get(ctx, &fsm_odr);

      if (ret == 0)
      {
        switch (fsm_odr)
        {
          case LSM6DSRX_ODR_FSM_12Hz5:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_12Hz5;
            }

            else
            {
              odr_gy = val;
            }

            break;

          case LSM6DSRX_ODR_FSM_26Hz:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_26Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_12Hz5)
            {
              odr_gy = LSM6DSRX_GY_ODR_26Hz;
            }

            else
            {
              odr_gy = val;
            }

            break;

          case LSM6DSRX_ODR_FSM_52Hz:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_52Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_12Hz5)
            {
              odr_gy = LSM6DSRX_GY_ODR_52Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_26Hz)
            {
              odr_gy = LSM6DSRX_GY_ODR_52Hz;
            }

            else
            {
              odr_gy = val;
            }

            break;

          case LSM6DSRX_ODR_FSM_104Hz:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_12Hz5)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_26Hz)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_52Hz)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else
            {
              odr_gy = val;
            }

            break;

          default:
            odr_gy = val;
            break;
        }
      }
    }
  }

  /* Check the Machine Learning Core data rate constraints */
  mlc_enable = PROPERTY_DISABLE;

  if (ret == 0)
  {
    ret =  lsm6dsrx_mlc_get(ctx, &mlc_enable);

    if (mlc_enable == PROPERTY_ENABLE)
    {
      ret =  lsm6dsrx_mlc_data_rate_get(ctx, &mlc_odr);

      if (ret == 0)
      {
        switch (mlc_odr)
        {
          case LSM6DSRX_ODR_PRGS_12Hz5:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_12Hz5;
            }

            else
            {
              odr_gy = val;
            }

            break;

          case LSM6DSRX_ODR_PRGS_26Hz:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_26Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_12Hz5)
            {
              odr_gy = LSM6DSRX_GY_ODR_26Hz;
            }

            else
            {
              odr_gy = val;
            }

            break;

          case LSM6DSRX_ODR_PRGS_52Hz:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_52Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_12Hz5)
            {
              odr_gy = LSM6DSRX_GY_ODR_52Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_26Hz)
            {
              odr_gy = LSM6DSRX_GY_ODR_52Hz;
            }

            else
            {
              odr_gy = val;
            }

            break;

          case LSM6DSRX_ODR_PRGS_104Hz:
            if (val == LSM6DSRX_GY_ODR_OFF)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_12Hz5)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_26Hz)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else if (val == LSM6DSRX_GY_ODR_52Hz)
            {
              odr_gy = LSM6DSRX_GY_ODR_104Hz;
            }

            else
            {
              odr_gy = val;
            }

            break;

          default:
            odr_gy = val;
            break;
        }
      }
    }
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_G,
                            (uint8_t *)&ctrl2_g, 1);
  }

  if (ret == 0)
  {
    ctrl2_g.odr_g = (uint8_t)odr_gy;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL2_G,
                             (uint8_t *)&ctrl2_g, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope data rate.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_g in reg CTRL2_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_data_rate_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_odr_g_t *val)
{
  lsm6dsrx_ctrl2_g_t ctrl2_g;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_G,
                          (uint8_t *)&ctrl2_g, 1);

  switch (ctrl2_g.odr_g)
  {
    case LSM6DSRX_GY_ODR_OFF:
      *val = LSM6DSRX_GY_ODR_OFF;
      break;

    case LSM6DSRX_GY_ODR_12Hz5:
      *val = LSM6DSRX_GY_ODR_12Hz5;
      break;

    case LSM6DSRX_GY_ODR_26Hz:
      *val = LSM6DSRX_GY_ODR_26Hz;
      break;

    case LSM6DSRX_GY_ODR_52Hz:
      *val = LSM6DSRX_GY_ODR_52Hz;
      break;

    case LSM6DSRX_GY_ODR_104Hz:
      *val = LSM6DSRX_GY_ODR_104Hz;
      break;

    case LSM6DSRX_GY_ODR_208Hz:
      *val = LSM6DSRX_GY_ODR_208Hz;
      break;

    case LSM6DSRX_GY_ODR_416Hz:
      *val = LSM6DSRX_GY_ODR_416Hz;
      break;

    case LSM6DSRX_GY_ODR_833Hz:
      *val = LSM6DSRX_GY_ODR_833Hz;
      break;

    case LSM6DSRX_GY_ODR_1666Hz:
      *val = LSM6DSRX_GY_ODR_1666Hz;
      break;

    case LSM6DSRX_GY_ODR_3332Hz:
      *val = LSM6DSRX_GY_ODR_3332Hz;
      break;

    case LSM6DSRX_GY_ODR_6667Hz:
      *val = LSM6DSRX_GY_ODR_6667Hz;
      break;

    default:
      *val = LSM6DSRX_GY_ODR_OFF;
      break;
  }

  return ret;
}

/**
  * @brief  Block data update.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdu in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_block_data_update_set(const stmdev_ctx_t *ctx,
                                       uint8_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.bdu = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Block data update.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdu in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_block_data_update_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.bdu;

  return ret;
}

/**
  * @brief  Weight of XL user offset bits of registers X_OFS_USR (73h),
  *         Y_OFS_USR (74h), Z_OFS_USR (75h).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_w in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_offset_weight_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_usr_off_w_t val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  if (ret == 0)
  {
    ctrl6_c.usr_off_w = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL6_C,
                             (uint8_t *)&ctrl6_c, 1);
  }

  return ret;
}

/**
  * @brief  Weight of XL user offset bits of registers X_OFS_USR (73h),
  *         Y_OFS_USR (74h), Z_OFS_USR (75h).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of usr_off_w in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_offset_weight_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_usr_off_w_t *val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  switch (ctrl6_c.usr_off_w)
  {
    case LSM6DSRX_LSb_1mg:
      *val = LSM6DSRX_LSb_1mg;
      break;

    case LSM6DSRX_LSb_16mg:
      *val = LSM6DSRX_LSb_16mg;
      break;

    default:
      *val = LSM6DSRX_LSb_1mg;
      break;
  }

  return ret;
}

/**
  * @brief  Accelerometer power mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of xl_hm_mode in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_power_mode_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_xl_hm_mode_t val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  if (ret == 0)
  {
    ctrl6_c.xl_hm_mode = (uint8_t)val & 0x01U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL6_C,
                             (uint8_t *)&ctrl6_c, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer power mode[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of xl_hm_mode in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_power_mode_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_xl_hm_mode_t *val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  switch (ctrl6_c.xl_hm_mode)
  {
    case LSM6DSRX_HIGH_PERFORMANCE_MD:
      *val = LSM6DSRX_HIGH_PERFORMANCE_MD;
      break;

    case LSM6DSRX_LOW_NORMAL_POWER_MD:
      *val = LSM6DSRX_LOW_NORMAL_POWER_MD;
      break;

    default:
      *val = LSM6DSRX_HIGH_PERFORMANCE_MD;
      break;
  }

  return ret;
}

/**
  * @brief  Operating mode for gyroscope.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of g_hm_mode in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_power_mode_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_g_hm_mode_t val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ctrl7_g.g_hm_mode = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL7_G,
                             (uint8_t *)&ctrl7_g, 1);
  }

  return ret;
}

/**
  * @brief  gy_power_mode: [get]  Operating mode for gyroscope.
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of g_hm_mode in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_power_mode_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_g_hm_mode_t *val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  switch (ctrl7_g.g_hm_mode)
  {
    case LSM6DSRX_GY_HIGH_PERFORMANCE:
      *val = LSM6DSRX_GY_HIGH_PERFORMANCE;
      break;

    case LSM6DSRX_GY_NORMAL:
      *val = LSM6DSRX_GY_NORMAL;
      break;

    default:
      *val = LSM6DSRX_GY_HIGH_PERFORMANCE;
      break;
  }

  return ret;
}

/**
  * @brief  Read all the interrupt flag of the device.
  *[get]
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get registers ALL_INT_SRC; WAKE_UP_SRC;
  *                              TAP_SRC; D6D_SRC; STATUS_REG;
  *                              MLC_STATUS_MAINPAGE;
  *                              EMB_FUNC_STATUS; FSM_STATUS_A/B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_all_sources_get(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_all_sources_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_ALL_INT_SRC,
                          (uint8_t *)&val->all_int_src, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_SRC,
                            (uint8_t *)&val->wake_up_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_SRC,
                            (uint8_t *)&val->tap_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_D6D_SRC,
                            (uint8_t *)&val->d6d_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_REG,
                            (uint8_t *)&val->status_reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MLC_STATUS_MAINPAGE,
                            (uint8_t *)&val->mlc_status, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_STATUS,
                            (uint8_t *)&val->emb_func_status, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_STATUS_A,
                            (uint8_t *)&val->fsm_status_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_STATUS_B,
                            (uint8_t *)&val->fsm_status_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  The STATUS_REG register is read by the primary interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get register STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_status_reg_get(const stmdev_ctx_t *ctx,
                                lsm6dsrx_status_reg_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_REG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Accelerometer new data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of xlda in reg STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dsrx_status_reg_t status_reg;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_REG,
                          (uint8_t *)&status_reg, 1);
  *val = status_reg.xlda;

  return ret;
}

/**
  * @brief  Gyroscope new data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of gda in reg STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dsrx_status_reg_t status_reg;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_REG,
                          (uint8_t *)&status_reg, 1);
  *val = status_reg.gda;

  return ret;
}

/**
  * @brief  Temperature new data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tda in reg STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_temp_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                          uint8_t *val)
{
  lsm6dsrx_status_reg_t status_reg;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_REG,
                          (uint8_t *)&status_reg, 1);
  *val = status_reg.tda;

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_x_set(const stmdev_ctx_t *ctx,
                                     uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_X_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_x_get(const stmdev_ctx_t *ctx,
                                     uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_X_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Y-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_y_set(const stmdev_ctx_t *ctx,
                                     uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_Y_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Y-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_y_get(const stmdev_ctx_t *ctx,
                                     uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_Y_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Z-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_z_set(const stmdev_ctx_t *ctx,
                                     uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_Z_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_z_get(const stmdev_ctx_t *ctx,
                                     uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_Z_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Enables user offset on out.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_on_out in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ctrl7_g.usr_off_on_out = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL7_G,
                             (uint8_t *)&ctrl7_g, 1);
  }

  return ret;
}

/**
  * @brief  Get user offset on out flag.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get values of usr_off_on_out in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);
  *val = ctrl7_g.usr_off_on_out;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_Timestamp
  * @brief      This section groups all the functions that manage the
  *             timestamp generation.
  * @{
  *
  */

/**
  * @brief  Reset timestamp counter.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_timestamp_rst(const stmdev_ctx_t *ctx)
{
  uint8_t rst_val = 0xAA;
  return lsm6dsrx_write_reg(ctx, LSM6DSRX_TIMESTAMP2, &rst_val, 1);
}

/**
  * @brief  Enables timestamp counter.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of timestamp_en in reg CTRL10_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_timestamp_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl10_c_t ctrl10_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL10_C,
                          (uint8_t *)&ctrl10_c, 1);

  if (ret == 0)
  {
    ctrl10_c.timestamp_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL10_C,
                             (uint8_t *)&ctrl10_c, 1);
  }

  return ret;
}

/**
  * @brief  Enables timestamp counter.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of timestamp_en in reg CTRL10_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_timestamp_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl10_c_t ctrl10_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL10_C,
                          (uint8_t *)&ctrl10_c, 1);
  *val = ctrl10_c.timestamp_en;

  return ret;
}

/**
  * @brief  Timestamp first data output register (r).
  *         The value is expressed as a 32-bit word and the bit resolution
  *         is 25 us.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_timestamp_raw_get(const stmdev_ctx_t *ctx, uint32_t *val)
{
  uint8_t buff[4];
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TIMESTAMP0, buff, 4);
  *val = buff[3];
  *val = (*val * 256U) +  buff[2];
  *val = (*val * 256U) +  buff[1];
  *val = (*val * 256U) +  buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_Data output
  * @brief      This section groups all the data output functions.
  * @{
  *
  */

/**
  * @brief  Circular burst-mode (rounding) read of the output registers.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rounding in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_rounding_mode_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_rounding_t val)
{
  lsm6dsrx_ctrl5_c_t ctrl5_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL5_C,
                          (uint8_t *)&ctrl5_c, 1);

  if (ret == 0)
  {
    ctrl5_c.rounding = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL5_C,
                             (uint8_t *)&ctrl5_c, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of rounding in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_rounding_mode_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_rounding_t *val)
{
  lsm6dsrx_ctrl5_c_t ctrl5_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL5_C,
                          (uint8_t *)&ctrl5_c, 1);

  switch (ctrl5_c.rounding)
  {
    case LSM6DSRX_NO_ROUND:
      *val = LSM6DSRX_NO_ROUND;
      break;

    case LSM6DSRX_ROUND_XL:
      *val = LSM6DSRX_ROUND_XL;
      break;

    case LSM6DSRX_ROUND_GY:
      *val = LSM6DSRX_ROUND_GY;
      break;

    case LSM6DSRX_ROUND_GY_XL:
      *val = LSM6DSRX_ROUND_GY_XL;
      break;

    default:
      *val = LSM6DSRX_NO_ROUND;
      break;
  }

  return ret;
}

/**
  * @brief  Temperature data output register (r).
  *         L and H registers together express a 16-bit word in two's
  *         complement.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_temperature_raw_get(const stmdev_ctx_t *ctx,
                                     int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_OUT_TEMP_L, buff, 2);
  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Angular rate sensor. The value is expressed as a 16-bit
  *         word in two's complement.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_angular_rate_raw_get(const stmdev_ctx_t *ctx,
                                      int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_OUTX_L_G, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  Linear acceleration output register. The value is expressed as a
  *         16-bit word in two's complement.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_acceleration_raw_get(const stmdev_ctx_t *ctx,
                                      int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_OUTX_L_A, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  FIFO data output.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_out_raw_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_DATA_OUT_X_L, buff, 6);

  return ret;
}

/**
  * @brief  Step counter output register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_number_of_steps_get(const stmdev_ctx_t *ctx,
                                     uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STEP_COUNTER_L, buff, 2);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Reset step counter register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_steps_reset(const stmdev_ctx_t *ctx)
{
  lsm6dsrx_emb_func_src_t emb_func_src;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_SRC,
                            (uint8_t *)&emb_func_src, 1);
  }

  if (ret == 0)
  {
    emb_func_src.pedo_rst_step = PROPERTY_ENABLE;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_SRC,
                             (uint8_t *)&emb_func_src, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_common
  * @brief      This section groups common useful functions.
  * @{
  *
  */

/**
  * @brief  Difference in percentage of the effective ODR (and timestamp rate)
  *         with respect to the typical.[get]
  *         Step:  0.15%. 8-bit format, 2's complement.
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of freq_fine in reg INTERNAL_FREQ_FINE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_odr_cal_reg_get(const stmdev_ctx_t *ctx, int8_t *val)
{
  lsm6dsrx_internal_freq_fine_t internal_freq_fine;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INTERNAL_FREQ_FINE,
                          (uint8_t *)&internal_freq_fine, 1);
  *val = (int8_t)internal_freq_fine.freq_fine;

  return ret;
}

/**
  * @brief  Enable access to the embedded functions/sensor hub configuration
  *         registers.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of reg_access in reg FUNC_CFG_ACCESS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mem_bank_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_reg_access_t val)
{
  lsm6dsrx_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FUNC_CFG_ACCESS,
                          (uint8_t *)&func_cfg_access, 1);

  if (ret == 0)
  {
    func_cfg_access.reg_access = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FUNC_CFG_ACCESS,
                             (uint8_t *)&func_cfg_access, 1);
  }

  return ret;
}

/**
  * @brief  Enable access to the embedded functions/sensor hub configuration
  *         registers.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of reg_access in reg FUNC_CFG_ACCESS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mem_bank_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_reg_access_t *val)
{
  lsm6dsrx_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FUNC_CFG_ACCESS,
                          (uint8_t *)&func_cfg_access, 1);

  switch (func_cfg_access.reg_access)
  {
    case LSM6DSRX_USER_BANK:
      *val = LSM6DSRX_USER_BANK;
      break;

    case LSM6DSRX_SENSOR_HUB_BANK:
      *val = LSM6DSRX_SENSOR_HUB_BANK;
      break;

    case LSM6DSRX_EMBEDDED_FUNC_BANK:
      *val = LSM6DSRX_EMBEDDED_FUNC_BANK;
      break;

    default:
      *val = LSM6DSRX_USER_BANK;
      break;
  }

  return ret;
}

/**
  * @brief  Write a line(byte) in a page.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  add    Page line address
  * @param  val    Value to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ln_pg_write_byte(const stmdev_ctx_t *ctx, uint16_t add,
                                  uint8_t *val)
{
  lsm6dsrx_page_rw_t page_rw;
  lsm6dsrx_page_sel_t page_sel;
  lsm6dsrx_page_address_t page_address;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.page_rw = 0x02U; /* page_write enable */
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_SEL,
                            (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    page_sel.page_sel = (uint8_t)((add / 256U) & 0x0FU);
    page_sel.not_used_01 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_SEL,
                             (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    page_address.page_addr = (uint8_t)(add - (page_sel.page_sel * 256U));
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_ADDRESS,
                             (uint8_t *)&page_address, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_VALUE, val, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.page_rw = 0x00; /* page_write disable */
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Write buffer in a page.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buf    Page line address.(ptr)
  * @param  val    Value to write.
  * @param  len    buffer length.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ln_pg_write(const stmdev_ctx_t *ctx, uint16_t add,
                             uint8_t *buf, uint8_t len)
{
  lsm6dsrx_page_rw_t page_rw;
  lsm6dsrx_page_sel_t page_sel;
  lsm6dsrx_page_address_t page_address;
  uint8_t msb;
  uint8_t lsb;
  int32_t ret;
  uint8_t i ;

  msb = (uint8_t)((add / 256U) & 0x0FU);
  lsb = (uint8_t)(add - (msb * 256U));
  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.page_rw = 0x02U; /* page_write enable*/
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_SEL,
                            (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    page_sel.page_sel = msb;
    page_sel.not_used_01 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_SEL,
                             (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    page_address.page_addr = lsb;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_ADDRESS,
                             (uint8_t *)&page_address, 1);
  }

  for (i = 0; i < len; i++)
  {
    if (ret == 0)
    {
      ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_VALUE, &buf[i], 1);

      if (ret == 0)
      {
        /* Check if page wrap */
        if (lsb == 0x00U)
        {
          msb++;
          ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_SEL,
                                  (uint8_t *)&page_sel, 1);
        }

        lsb++;
      }

      if (ret == 0)
      {
        page_sel.page_sel = msb;
        page_sel.not_used_01 = 1;
        ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_SEL,
                                 (uint8_t *)&page_sel, 1);
      }
    }
  }

  if (ret == 0)
  {
    page_sel.page_sel = 0;
    page_sel.not_used_01 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_SEL,
                             (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.page_rw = 0x00U; /* page_write disable */
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Read a line(byte) in a page.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  add    Page line address.
  * @param  val    Read value.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ln_pg_read_byte(const stmdev_ctx_t *ctx, uint16_t add,
                                 uint8_t *val)
{
  lsm6dsrx_page_rw_t page_rw;
  lsm6dsrx_page_sel_t page_sel;
  lsm6dsrx_page_address_t page_address;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.page_rw = 0x01U; /* page_read enable*/
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_SEL,
                            (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    page_sel.page_sel = (uint8_t)((add / 256U) & 0x0FU);
    page_sel.not_used_01 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_SEL,
                             (uint8_t *)&page_sel, 1);
  }

  if (ret == 0)
  {
    page_address.page_addr = (uint8_t)(add - (page_sel.page_sel * 256U));
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_ADDRESS,
                             (uint8_t *)&page_address, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_VALUE, val, 2);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.page_rw = 0x00U; /* page_read disable */
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Data-ready pulsed / letched mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of dataready_pulsed in
  *                reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_data_ready_mode_set(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_dataready_pulsed_t val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.dataready_pulsed = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                             (uint8_t *)&counter_bdr_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Data-ready pulsed / letched mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of dataready_pulsed in
  *                reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_data_ready_mode_get(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_dataready_pulsed_t *val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  switch (counter_bdr_reg1.dataready_pulsed)
  {
    case LSM6DSRX_DRDY_LATCHED:
      *val = LSM6DSRX_DRDY_LATCHED;
      break;

    case LSM6DSRX_DRDY_PULSED:
      *val = LSM6DSRX_DRDY_PULSED;
      break;

    default:
      *val = LSM6DSRX_DRDY_LATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Device Who am I.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_device_id_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WHO_AM_I, buff, 1);

  return ret;
}

/**
  * @brief  Software reset. Restore the default values in user registers.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sw_reset in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_reset_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.sw_reset = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Software reset. Restore the default values in user registers.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sw_reset in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_reset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.sw_reset;

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte
  *         access with a serial interface.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of if_inc in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_auto_increment_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.if_inc = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte
  *         access with a serial interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of if_inc in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_auto_increment_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.if_inc;

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of boot in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_boot_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.boot = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of boot in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_boot_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.boot;

  return ret;
}



/**
  * @brief  Linear acceleration sensor self-test enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of st_xl in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_self_test_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_st_xl_t val)
{
  lsm6dsrx_ctrl5_c_t ctrl5_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL5_C,
                          (uint8_t *)&ctrl5_c, 1);

  if (ret == 0)
  {
    ctrl5_c.st_xl = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL5_C,
                             (uint8_t *)&ctrl5_c, 1);
  }

  return ret;
}

/**
  * @brief  Linear acceleration sensor self-test enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of st_xl in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_self_test_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_st_xl_t *val)
{
  lsm6dsrx_ctrl5_c_t ctrl5_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL5_C,
                          (uint8_t *)&ctrl5_c, 1);

  switch (ctrl5_c.st_xl)
  {
    case LSM6DSRX_XL_ST_DISABLE:
      *val = LSM6DSRX_XL_ST_DISABLE;
      break;

    case LSM6DSRX_XL_ST_POSITIVE:
      *val = LSM6DSRX_XL_ST_POSITIVE;
      break;

    case LSM6DSRX_XL_ST_NEGATIVE:
      *val = LSM6DSRX_XL_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSRX_XL_ST_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Angular rate sensor self-test enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of st_g in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_self_test_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_st_g_t val)
{
  lsm6dsrx_ctrl5_c_t ctrl5_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL5_C,
                          (uint8_t *)&ctrl5_c, 1);

  if (ret == 0)
  {
    ctrl5_c.st_g = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL5_C,
                             (uint8_t *)&ctrl5_c, 1);
  }

  return ret;
}

/**
  * @brief  Angular rate sensor self-test enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of st_g in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_self_test_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_st_g_t *val)
{
  lsm6dsrx_ctrl5_c_t ctrl5_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL5_C,
                          (uint8_t *)&ctrl5_c, 1);

  switch (ctrl5_c.st_g)
  {
    case LSM6DSRX_GY_ST_DISABLE:
      *val = LSM6DSRX_GY_ST_DISABLE;
      break;

    case LSM6DSRX_GY_ST_POSITIVE:
      *val = LSM6DSRX_GY_ST_POSITIVE;
      break;

    case LSM6DSRX_GY_ST_NEGATIVE:
      *val = LSM6DSRX_GY_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSRX_GY_ST_DISABLE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_filters
  * @brief      This section group all the functions concerning the
  *             filters configuration
  * @{
  *
  */

/**
  * @brief  Accelerometer output from LPF2 filtering stage selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lpf2_xl_en in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_filter_lp2_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_XL,
                          (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.lpf2_xl_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_XL,
                             (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer output from LPF2 filtering stage selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lpf2_xl_en in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_filter_lp2_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl1_xl_t ctrl1_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_XL,
                          (uint8_t *)&ctrl1_xl, 1);
  *val = ctrl1_xl.lpf2_xl_en;

  return ret;
}

/**
  * @brief  Enables gyroscope digital LPF1 if auxiliary SPI is disabled;
  *         the bandwidth can be selected through FTYPE [2:0] in CTRL6_C.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lpf1_sel_g in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_filter_lp1_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.lpf1_sel_g = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL4_C,
                             (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  Enables gyroscope digital LPF1 if auxiliary SPI is disabled;
  *         the bandwidth can be selected through FTYPE [2:0] in CTRL6_C.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lpf1_sel_g in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_filter_lp1_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);
  *val = ctrl4_c.lpf1_sel_g;

  return ret;
}

/**
  * @brief  Mask DRDY on pin (both XL & Gyro) until filter settling ends
  *         (XL and Gyro independently masked).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of drdy_mask in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_drdy_mask_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.drdy_mask = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL4_C,
                             (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  Mask DRDY on pin (both XL & Gyro) until filter settling ends
  *         (XL and Gyro independently masked).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of drdy_mask in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_drdy_mask_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);
  *val = ctrl4_c.drdy_mask;

  return ret;
}

/**
  * @brief  Gyroscope low pass filter 1 bandwidth.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ftype in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_lp1_bandwidth_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_ftype_t val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  if (ret == 0)
  {
    ctrl6_c.ftype = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL6_C,
                             (uint8_t *)&ctrl6_c, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope low pass filter 1 bandwidth.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of ftype in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_lp1_bandwidth_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_ftype_t *val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  switch (ctrl6_c.ftype)
  {
    case LSM6DSRX_ULTRA_LIGHT:
      *val = LSM6DSRX_ULTRA_LIGHT;
      break;

    case LSM6DSRX_VERY_LIGHT:
      *val = LSM6DSRX_VERY_LIGHT;
      break;

    case LSM6DSRX_LIGHT:
      *val = LSM6DSRX_LIGHT;
      break;

    case LSM6DSRX_MEDIUM:
      *val = LSM6DSRX_MEDIUM;
      break;

    case LSM6DSRX_STRONG:
      *val = LSM6DSRX_STRONG;
      break;

    case LSM6DSRX_VERY_STRONG:
      *val = LSM6DSRX_VERY_STRONG;
      break;

    case LSM6DSRX_AGGRESSIVE:
      *val = LSM6DSRX_AGGRESSIVE;
      break;

    case LSM6DSRX_XTREME:
      *val = LSM6DSRX_XTREME;
      break;

    default:
      *val = LSM6DSRX_ULTRA_LIGHT;
      break;
  }

  return ret;
}

/**
  * @brief  Low pass filter 2 on 6D function selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of low_pass_on_6d in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_lp2_on_6d_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL8_XL,
                          (uint8_t *)&ctrl8_xl, 1);

  if (ret == 0)
  {
    ctrl8_xl.low_pass_on_6d = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL8_XL,
                             (uint8_t *)&ctrl8_xl, 1);
  }

  return ret;
}

/**
  * @brief  Low pass filter 2 on 6D function selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of low_pass_on_6d in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_lp2_on_6d_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL8_XL,
                          (uint8_t *)&ctrl8_xl, 1);
  *val = ctrl8_xl.low_pass_on_6d;

  return ret;
}

/**
  * @brief  Accelerometer slope filter / high-pass filter selection
  *         on output.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of hp_slope_xl_en in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_hp_path_on_out_set(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_hp_slope_xl_en_t val)
{
  lsm6dsrx_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL8_XL,
                          (uint8_t *)&ctrl8_xl, 1);

  if (ret == 0)
  {
    ctrl8_xl.hp_slope_xl_en = (((uint8_t)val & 0x10U) >> 4);
    ctrl8_xl.hp_ref_mode_xl = (((uint8_t)val & 0x20U) >> 5);
    ctrl8_xl.hpcf_xl = (uint8_t)val & 0x07U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL8_XL,
                             (uint8_t *)&ctrl8_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer slope filter / high-pass filter selection on
  *         output.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of hp_slope_xl_en in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_hp_path_on_out_get(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_hp_slope_xl_en_t *val)
{
  lsm6dsrx_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL8_XL,
                          (uint8_t *)&ctrl8_xl, 1);

  switch (((ctrl8_xl.hp_ref_mode_xl << 5) + (ctrl8_xl.hp_slope_xl_en <<
                                             4) +
           ctrl8_xl.hpcf_xl))
  {
    case LSM6DSRX_HP_PATH_DISABLE_ON_OUT:
      *val = LSM6DSRX_HP_PATH_DISABLE_ON_OUT;
      break;

    case LSM6DSRX_SLOPE_ODR_DIV_4:
      *val = LSM6DSRX_SLOPE_ODR_DIV_4;
      break;

    case LSM6DSRX_HP_ODR_DIV_10:
      *val = LSM6DSRX_HP_ODR_DIV_10;
      break;

    case LSM6DSRX_HP_ODR_DIV_20:
      *val = LSM6DSRX_HP_ODR_DIV_20;
      break;

    case LSM6DSRX_HP_ODR_DIV_45:
      *val = LSM6DSRX_HP_ODR_DIV_45;
      break;

    case LSM6DSRX_HP_ODR_DIV_100:
      *val = LSM6DSRX_HP_ODR_DIV_100;
      break;

    case LSM6DSRX_HP_ODR_DIV_200:
      *val = LSM6DSRX_HP_ODR_DIV_200;
      break;

    case LSM6DSRX_HP_ODR_DIV_400:
      *val = LSM6DSRX_HP_ODR_DIV_400;
      break;

    case LSM6DSRX_HP_ODR_DIV_800:
      *val = LSM6DSRX_HP_ODR_DIV_800;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_10:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_10;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_20:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_20;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_45:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_45;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_100:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_100;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_200:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_200;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_400:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_400;
      break;

    case LSM6DSRX_HP_REF_MD_ODR_DIV_800:
      *val = LSM6DSRX_HP_REF_MD_ODR_DIV_800;
      break;

    case LSM6DSRX_LP_ODR_DIV_10:
      *val = LSM6DSRX_LP_ODR_DIV_10;
      break;

    case LSM6DSRX_LP_ODR_DIV_20:
      *val = LSM6DSRX_LP_ODR_DIV_20;
      break;

    case LSM6DSRX_LP_ODR_DIV_45:
      *val = LSM6DSRX_LP_ODR_DIV_45;
      break;

    case LSM6DSRX_LP_ODR_DIV_100:
      *val = LSM6DSRX_LP_ODR_DIV_100;
      break;

    case LSM6DSRX_LP_ODR_DIV_200:
      *val = LSM6DSRX_LP_ODR_DIV_200;
      break;

    case LSM6DSRX_LP_ODR_DIV_400:
      *val = LSM6DSRX_LP_ODR_DIV_400;
      break;

    case LSM6DSRX_LP_ODR_DIV_800:
      *val = LSM6DSRX_LP_ODR_DIV_800;
      break;

    default:
      *val = LSM6DSRX_HP_PATH_DISABLE_ON_OUT;
      break;
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode.
  *         The filter sets the second samples after writing this bit.
  *         Active only during device exit from powerdown mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fastsettl_mode_xl in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_fast_settling_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL8_XL,
                          (uint8_t *)&ctrl8_xl, 1);

  if (ret == 0)
  {
    ctrl8_xl.fastsettl_mode_xl = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL8_XL,
                             (uint8_t *)&ctrl8_xl, 1);
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode.
  *         The filter sets the second samples after writing
  *         this bit. Active only during device exit from powerdown mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fastsettl_mode_xl in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_fast_settling_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_ctrl8_xl_t ctrl8_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL8_XL,
                          (uint8_t *)&ctrl8_xl, 1);
  *val = ctrl8_xl.fastsettl_mode_xl;

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity
  *         functions.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of slope_fds in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_hp_path_internal_set(const stmdev_ctx_t *ctx,
                                         lsm6dsrx_slope_fds_t val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.slope_fds = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG0,
                             (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity
  *         functions.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of slope_fds in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_hp_path_internal_get(const stmdev_ctx_t *ctx,
                                         lsm6dsrx_slope_fds_t *val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  switch (tap_cfg0.slope_fds)
  {
    case LSM6DSRX_USE_SLOPE:
      *val = LSM6DSRX_USE_SLOPE;
      break;

    case LSM6DSRX_USE_HPF:
      *val = LSM6DSRX_USE_HPF;
      break;

    default:
      *val = LSM6DSRX_USE_SLOPE;
      break;
  }

  return ret;
}

/**
  * @brief  Enables gyroscope digital high-pass filter. The filter is enabled
  *         only if the gyro is in HP mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of hp_en_g and hp_en_g in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_hp_path_internal_set(const stmdev_ctx_t *ctx,
                                         lsm6dsrx_hpm_g_t val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ctrl7_g.hp_en_g = (((uint8_t)val & 0x80U) >> 7);
    ctrl7_g.hpm_g = (uint8_t)val & 0x03U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL7_G,
                             (uint8_t *)&ctrl7_g, 1);
  }

  return ret;
}

/**
  * @brief    Enables gyroscope digital high-pass filter. The filter is
  *           enabled only if the gyro is in HP mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of hp_en_g and hp_en_g in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_hp_path_internal_get(const stmdev_ctx_t *ctx,
                                         lsm6dsrx_hpm_g_t *val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  switch ((ctrl7_g.hp_en_g << 7) + ctrl7_g.hpm_g)
  {
    case LSM6DSRX_HP_FILTER_NONE:
      *val = LSM6DSRX_HP_FILTER_NONE;
      break;

    case LSM6DSRX_HP_FILTER_16mHz:
      *val = LSM6DSRX_HP_FILTER_16mHz;
      break;

    case LSM6DSRX_HP_FILTER_65mHz:
      *val = LSM6DSRX_HP_FILTER_65mHz;
      break;

    case LSM6DSRX_HP_FILTER_260mHz:
      *val = LSM6DSRX_HP_FILTER_260mHz;
      break;

    case LSM6DSRX_HP_FILTER_1Hz04:
      *val = LSM6DSRX_HP_FILTER_1Hz04;
      break;

    default:
      *val = LSM6DSRX_HP_FILTER_NONE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_ Auxiliary_interface
  * @brief      This section groups all the functions concerning
  *             auxiliary interface.
  * @{
  *
  */

/**
  * @brief  On auxiliary interface connect/disconnect SDO and OCS
  *         internal pull-up.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ois_pu_dis in reg PIN_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_sdo_ocs_mode_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_ois_pu_dis_t val)
{
  lsm6dsrx_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PIN_CTRL,
                          (uint8_t *)&pin_ctrl, 1);

  if (ret == 0)
  {
    pin_ctrl.ois_pu_dis = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PIN_CTRL,
                             (uint8_t *)&pin_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  On auxiliary interface connect/disconnect SDO and OCS
  *         internal pull-up.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of ois_pu_dis in reg PIN_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_sdo_ocs_mode_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_ois_pu_dis_t *val)
{
  lsm6dsrx_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PIN_CTRL,
                          (uint8_t *)&pin_ctrl, 1);

  switch (pin_ctrl.ois_pu_dis)
  {
    case LSM6DSRX_AUX_PULL_UP_DISC:
      *val = LSM6DSRX_AUX_PULL_UP_DISC;
      break;

    case LSM6DSRX_AUX_PULL_UP_CONNECT:
      *val = LSM6DSRX_AUX_PULL_UP_CONNECT;
      break;

    default:
      *val = LSM6DSRX_AUX_PULL_UP_DISC;
      break;
  }

  return ret;
}

/**
  * @brief  OIS chain on aux interface power on mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ois_on in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_pw_on_ctrl_set(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_ois_on_t val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  if (ret == 0)
  {
    ctrl7_g.ois_on_en = (uint8_t)val & 0x01U;
    ctrl7_g.ois_on = (uint8_t)val & 0x01U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL7_G,
                             (uint8_t *)&ctrl7_g, 1);
  }

  return ret;
}

/**
  * @brief  OIS chain on aux interface power on mode[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of ois_on in reg CTRL7_G
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_pw_on_ctrl_get(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_ois_on_t *val)
{
  lsm6dsrx_ctrl7_g_t ctrl7_g;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL7_G,
                          (uint8_t *)&ctrl7_g, 1);

  switch (ctrl7_g.ois_on)
  {
    case LSM6DSRX_AUX_ON:
      *val = LSM6DSRX_AUX_ON;
      break;

    case LSM6DSRX_AUX_ON_BY_AUX_INTERFACE:
      *val = LSM6DSRX_AUX_ON_BY_AUX_INTERFACE;
      break;

    default:
      *val = LSM6DSRX_AUX_ON;
      break;
  }

  return ret;
}

/**
  * @brief  The STATUS_SPIAux register is read by the auxiliary SPI.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  lsm6dsrx_status_spiaux_t: registers STATUS_SPIAUX
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_status_reg_get(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_status_spiaux_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_SPIAUX,
                          (uint8_t *)val, 1);

  return ret;
}

/**
  * @brief  AUX accelerometer data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of xlda in reg STATUS_SPIAUX
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                            uint8_t *val)
{
  lsm6dsrx_status_spiaux_t status_spiaux;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_SPIAUX,
                          (uint8_t *)&status_spiaux, 1);
  *val = status_spiaux.xlda;

  return ret;
}

/**
  * @brief  AUX gyroscope data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of gda in reg STATUS_SPIAUX
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                            uint8_t *val)
{
  lsm6dsrx_status_spiaux_t status_spiaux;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_SPIAUX,
                          (uint8_t *)&status_spiaux, 1);
  *val = status_spiaux.gda;

  return ret;
}

/**
  * @brief  High when the gyroscope output is in the settling phase.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of gyro_settling in reg STATUS_SPIAUX
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_flag_settling_get(const stmdev_ctx_t *ctx,
                                          uint8_t *val)
{
  lsm6dsrx_status_spiaux_t status_spiaux;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_SPIAUX,
                          (uint8_t *)&status_spiaux, 1);
  *val = status_spiaux.gyro_settling;

  return ret;
}

/**
  * @brief  Selects accelerometer self-test. Effective only if XL OIS chain is
  *         enabled.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of st_xl_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_self_test_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_st_xl_ois_t val)
{
  lsm6dsrx_int_ois_t int_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  if (ret == 0)
  {
    int_ois.st_xl_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_OIS,
                             (uint8_t *)&int_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects accelerometer self-test. Effective only if XL OIS chain
  *         is enabled.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of st_xl_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_self_test_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_st_xl_ois_t *val)
{
  lsm6dsrx_int_ois_t int_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  switch (int_ois.st_xl_ois)
  {
    case LSM6DSRX_AUX_XL_DISABLE:
      *val = LSM6DSRX_AUX_XL_DISABLE;
      break;

    case LSM6DSRX_AUX_XL_POS:
      *val = LSM6DSRX_AUX_XL_POS;
      break;

    case LSM6DSRX_AUX_XL_NEG:
      *val = LSM6DSRX_AUX_XL_NEG;
      break;

    default:
      *val = LSM6DSRX_AUX_XL_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Indicates polarity of DEN signal on OIS chain.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_lh_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_den_polarity_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_den_lh_ois_t val)
{
  lsm6dsrx_int_ois_t int_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  if (ret == 0)
  {
    int_ois.den_lh_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_OIS,
                             (uint8_t *)&int_ois, 1);
  }

  return ret;
}

/**
  * @brief  Indicates polarity of DEN signal on OIS chain.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of den_lh_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_den_polarity_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_den_lh_ois_t *val)
{
  lsm6dsrx_int_ois_t int_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  switch (int_ois.den_lh_ois)
  {
    case LSM6DSRX_AUX_DEN_ACTIVE_LOW:
      *val = LSM6DSRX_AUX_DEN_ACTIVE_LOW;
      break;

    case LSM6DSRX_AUX_DEN_ACTIVE_HIGH:
      *val = LSM6DSRX_AUX_DEN_ACTIVE_HIGH;
      break;

    default:
      *val = LSM6DSRX_AUX_DEN_ACTIVE_LOW;
      break;
  }

  return ret;
}

/**
  * @brief  Configure DEN mode on the OIS chain.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lvl2_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_den_mode_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_lvl2_ois_t val)
{
  lsm6dsrx_int_ois_t int_ois;
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  if (ret == 0)
  {
    int_ois.lvl2_ois = (uint8_t)val & 0x01U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_OIS,
                             (uint8_t *)&int_ois, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                            (uint8_t *)&ctrl1_ois, 1);
  }

  if (ret == 0)
  {
    ctrl1_ois.lvl1_ois = ((uint8_t)val & 0x02U) >> 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_OIS,
                             (uint8_t *)&ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  Configure DEN mode on the OIS chain.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of lvl2_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_den_mode_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_lvl2_ois_t *val)
{
  lsm6dsrx_int_ois_t int_ois;
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                            (uint8_t *)&ctrl1_ois, 1);
  }

  switch ((ctrl1_ois.lvl1_ois << 1) + int_ois.lvl2_ois)
  {
    case LSM6DSRX_AUX_DEN_DISABLE:
      *val = LSM6DSRX_AUX_DEN_DISABLE;
      break;

    case LSM6DSRX_AUX_DEN_LEVEL_LATCH:
      *val = LSM6DSRX_AUX_DEN_LEVEL_LATCH;
      break;

    case LSM6DSRX_AUX_DEN_LEVEL_TRIG:
      *val = LSM6DSRX_AUX_DEN_LEVEL_TRIG;
      break;

    default:
      *val = LSM6DSRX_AUX_DEN_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Enables/Disable OIS chain DRDY on INT2 pin. This setting has
  *         priority over all other INT2 settings.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of int2_drdy_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_drdy_on_int2_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_int_ois_t int_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);

  if (ret == 0)
  {
    int_ois.int2_drdy_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_OIS,
                             (uint8_t *)&int_ois, 1);
  }

  return ret;
}

/**
  * @brief  Enables/Disable OIS chain DRDY on INT2 pin. This setting has
  *         priority over all other INT2 settings.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of int2_drdy_ois in reg INT_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_drdy_on_int2_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_int_ois_t int_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_OIS,
                          (uint8_t *)&int_ois, 1);
  *val = int_ois.int2_drdy_ois;

  return ret;
}

/**
  * @brief  Enables OIS chain data processing for gyro in Mode 3 and Mode 4
  *         (mode4_en = 1) and accelerometer data in and Mode 4 (mode4_en = 1).
  *         When the OIS chain is enabled, the OIS outputs are available
  *         through the SPI2 in registers OUTX_L_G (22h) through OUTZ_H_G(27h)
  *         and STATUS_REG (1Eh) / STATUS_SPIAux, and LPF1 is dedicated to
  *         this chain.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ois_en_spi2 in reg CTRL1_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_mode_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_ois_en_spi2_t val)
{
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                          (uint8_t *)&ctrl1_ois, 1);

  if (ret == 0)
  {
    ctrl1_ois.ois_en_spi2 = (uint8_t)val & 0x01U;
    ctrl1_ois.mode4_en = ((uint8_t)val & 0x02U) >> 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_OIS,
                             (uint8_t *)&ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  Enables OIS chain data processing for gyro in Mode 3 and Mode 4
  *         (mode4_en = 1) and accelerometer data in and Mode 4 (mode4_en = 1).
  *         When the OIS chain is enabled, the OIS outputs are available
  *         through the SPI2 in registers OUTX_L_G (22h) through OUTZ_H_G(27h)
  *         and STATUS_REG (1Eh) / STATUS_SPIAux, and LPF1 is dedicated to
  *         this chain.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of ois_en_spi2 in
  *                                reg CTRL1_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_mode_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_ois_en_spi2_t *val)
{
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                          (uint8_t *)&ctrl1_ois, 1);

  switch (((ctrl1_ois.mode4_en << 1) + ctrl1_ois.ois_en_spi2))
  {
    case LSM6DSRX_AUX_DISABLE:
      *val = LSM6DSRX_AUX_DISABLE;
      break;

    case LSM6DSRX_MODE_3_GY:
      *val = LSM6DSRX_MODE_3_GY;
      break;

    case LSM6DSRX_MODE_4_GY_XL:
      *val = LSM6DSRX_MODE_4_GY_XL;
      break;

    default:
      *val = LSM6DSRX_AUX_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Selects gyroscope OIS chain full-scale.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fs_g_ois in reg CTRL1_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_full_scale_set(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_fs_g_ois_t val)
{
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                          (uint8_t *)&ctrl1_ois, 1);

  if (ret == 0)
  {
    ctrl1_ois.fs_g_ois = (uint8_t)val & 0x03U;
    ctrl1_ois.fs_125_ois = ((uint8_t)val & 0x04U) >> 2;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_OIS,
                             (uint8_t *)&ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects gyroscope OIS chain full-scale.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fs_g_ois in reg CTRL1_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_full_scale_get(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_fs_g_ois_t *val)
{
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                          (uint8_t *)&ctrl1_ois, 1);

  switch ((ctrl1_ois.fs_125_ois << 2) + ctrl1_ois.fs_g_ois)
  {
    case LSM6DSRX_250dps_AUX:
      *val = LSM6DSRX_250dps_AUX;
      break;

    case LSM6DSRX_125dps_AUX:
      *val = LSM6DSRX_125dps_AUX;
      break;

    case LSM6DSRX_500dps_AUX:
      *val = LSM6DSRX_500dps_AUX;
      break;

    case LSM6DSRX_1000dps_AUX:
      *val = LSM6DSRX_1000dps_AUX;
      break;

    case LSM6DSRX_2000dps_AUX:
      *val = LSM6DSRX_2000dps_AUX;
      break;

    default:
      *val = LSM6DSRX_250dps_AUX;
      break;
  }

  return ret;
}

/**
  * @brief  SPI2 3- or 4-wire interface.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sim_ois in reg CTRL1_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_spi_mode_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sim_ois_t val)
{
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                          (uint8_t *)&ctrl1_ois, 1);

  if (ret == 0)
  {
    ctrl1_ois.sim_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL1_OIS,
                             (uint8_t *)&ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  SPI2 3- or 4-wire interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sim_ois in reg CTRL1_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_spi_mode_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sim_ois_t *val)
{
  lsm6dsrx_ctrl1_ois_t ctrl1_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL1_OIS,
                          (uint8_t *)&ctrl1_ois, 1);

  switch (ctrl1_ois.sim_ois)
  {
    case LSM6DSRX_AUX_SPI_4_WIRE:
      *val = LSM6DSRX_AUX_SPI_4_WIRE;
      break;

    case LSM6DSRX_AUX_SPI_3_WIRE:
      *val = LSM6DSRX_AUX_SPI_3_WIRE;
      break;

    default:
      *val = LSM6DSRX_AUX_SPI_4_WIRE;
      break;
  }

  return ret;
}

/**
  * @brief  Selects gyroscope digital LPF1 filter bandwidth.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ftype_ois in reg CTRL2_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_lp1_bandwidth_set(const stmdev_ctx_t *ctx,
                                          lsm6dsrx_ftype_ois_t val)
{
  lsm6dsrx_ctrl2_ois_t ctrl2_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_OIS,
                          (uint8_t *)&ctrl2_ois, 1);

  if (ret == 0)
  {
    ctrl2_ois.ftype_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL2_OIS,
                             (uint8_t *)&ctrl2_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects gyroscope digital LPF1 filter bandwidth.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of ftype_ois in reg CTRL2_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_lp1_bandwidth_get(const stmdev_ctx_t *ctx,
                                          lsm6dsrx_ftype_ois_t *val)
{
  lsm6dsrx_ctrl2_ois_t ctrl2_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_OIS,
                          (uint8_t *)&ctrl2_ois, 1);

  switch (ctrl2_ois.ftype_ois)
  {
    case LSM6DSRX_351Hz39:
      *val = LSM6DSRX_351Hz39;
      break;

    case LSM6DSRX_236Hz63:
      *val = LSM6DSRX_236Hz63;
      break;

    case LSM6DSRX_172Hz70:
      *val = LSM6DSRX_172Hz70;
      break;

    case LSM6DSRX_937Hz91:
      *val = LSM6DSRX_937Hz91;
      break;

    default:
      *val = LSM6DSRX_351Hz39;
      break;
  }

  return ret;
}

/**
  * @brief  Selects gyroscope OIS chain digital high-pass filter cutoff.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of hpm_ois in reg CTRL2_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_hp_bandwidth_set(const stmdev_ctx_t *ctx,
                                         lsm6dsrx_hpm_ois_t val)
{
  lsm6dsrx_ctrl2_ois_t ctrl2_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_OIS,
                          (uint8_t *)&ctrl2_ois, 1);

  if (ret == 0)
  {
    ctrl2_ois.hpm_ois = (uint8_t)val & 0x03U;
    ctrl2_ois.hp_en_ois = ((uint8_t)val & 0x10U) >> 4;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL2_OIS,
                             (uint8_t *)&ctrl2_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects gyroscope OIS chain digital high-pass filter cutoff.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of hpm_ois in reg CTRL2_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_hp_bandwidth_get(const stmdev_ctx_t *ctx,
                                         lsm6dsrx_hpm_ois_t *val)
{
  lsm6dsrx_ctrl2_ois_t ctrl2_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL2_OIS,
                          (uint8_t *)&ctrl2_ois, 1);

  switch ((ctrl2_ois.hp_en_ois << 4) + ctrl2_ois.hpm_ois)
  {
    case LSM6DSRX_AUX_HP_DISABLE:
      *val = LSM6DSRX_AUX_HP_DISABLE;
      break;

    case LSM6DSRX_AUX_HP_Hz016:
      *val = LSM6DSRX_AUX_HP_Hz016;
      break;

    case LSM6DSRX_AUX_HP_Hz065:
      *val = LSM6DSRX_AUX_HP_Hz065;
      break;

    case LSM6DSRX_AUX_HP_Hz260:
      *val = LSM6DSRX_AUX_HP_Hz260;
      break;

    case LSM6DSRX_AUX_HP_1Hz040:
      *val = LSM6DSRX_AUX_HP_1Hz040;
      break;

    default:
      *val = LSM6DSRX_AUX_HP_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Enable / Disables OIS chain clamp. Enable: All OIS chain
  *         outputs = 8000h during self-test; Disable: OIS chain self-test
  *         outputs dependent from the aux gyro full scale selected.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of st_ois_clampdis in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_clamp_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_st_ois_clampdis_t val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  if (ret == 0)
  {
    ctrl3_ois.st_ois_clampdis = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_OIS,
                             (uint8_t *)&ctrl3_ois, 1);
  }

  return ret;
}

/**
  * @brief  Enable / Disables OIS chain clamp. Enable: All OIS chain
  *         outputs = 8000h during self-test; Disable: OIS chain self-test
  *         outputs dependent from the aux gyro full scale selected.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of st_ois_clampdis in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_clamp_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_st_ois_clampdis_t *val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  switch (ctrl3_ois.st_ois_clampdis)
  {
    case LSM6DSRX_ENABLE_CLAMP:
      *val = LSM6DSRX_ENABLE_CLAMP;
      break;

    case LSM6DSRX_DISABLE_CLAMP:
      *val = LSM6DSRX_DISABLE_CLAMP;
      break;

    default:
      *val = LSM6DSRX_ENABLE_CLAMP;
      break;
  }

  return ret;
}

/**
  * @brief  Selects gyroscope OIS chain self-test.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of st_ois in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_self_test_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_st_ois_t val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  if (ret == 0)
  {
    ctrl3_ois.st_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_OIS,
                             (uint8_t *)&ctrl3_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects gyroscope OIS chain self-test.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of st_ois in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_gy_self_test_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_st_ois_t *val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  switch (ctrl3_ois.st_ois)
  {
    case LSM6DSRX_AUX_GY_DISABLE:
      *val = LSM6DSRX_AUX_GY_DISABLE;
      break;

    case LSM6DSRX_AUX_GY_POS:
      *val = LSM6DSRX_AUX_GY_POS;
      break;

    case LSM6DSRX_AUX_GY_NEG:
      *val = LSM6DSRX_AUX_GY_NEG;
      break;

    default:
      *val = LSM6DSRX_AUX_GY_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel bandwidth.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of filter_xl_conf_ois in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_bandwidth_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_filter_xl_conf_ois_t val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  if (ret == 0)
  {
    ctrl3_ois.filter_xl_conf_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_OIS,
                             (uint8_t *)&ctrl3_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel bandwidth.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of filter_xl_conf_ois in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_bandwidth_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_filter_xl_conf_ois_t *val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  switch (ctrl3_ois.filter_xl_conf_ois)
  {
    case LSM6DSRX_631Hz:
      *val = LSM6DSRX_631Hz;
      break;

    case LSM6DSRX_295Hz:
      *val = LSM6DSRX_295Hz;
      break;

    case LSM6DSRX_140Hz:
      *val = LSM6DSRX_140Hz;
      break;

    case LSM6DSRX_68Hz2:
      *val = LSM6DSRX_68Hz2;
      break;

    case LSM6DSRX_33Hz6:
      *val = LSM6DSRX_33Hz6;
      break;

    case LSM6DSRX_16Hz7:
      *val = LSM6DSRX_16Hz7;
      break;

    case LSM6DSRX_8Hz3:
      *val = LSM6DSRX_8Hz3;
      break;

    case LSM6DSRX_4Hz11:
      *val = LSM6DSRX_4Hz11;
      break;

    default:
      *val = LSM6DSRX_631Hz;
      break;
  }

  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel full-scale.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fs_xl_ois in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_full_scale_set(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_fs_xl_ois_t val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  if (ret == 0)
  {
    ctrl3_ois.fs_xl_ois = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_OIS,
                             (uint8_t *)&ctrl3_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel full-scale.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fs_xl_ois in reg CTRL3_OIS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_aux_xl_full_scale_get(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_fs_xl_ois_t *val)
{
  lsm6dsrx_ctrl3_ois_t ctrl3_ois;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_OIS,
                          (uint8_t *)&ctrl3_ois, 1);

  switch (ctrl3_ois.fs_xl_ois)
  {
    case LSM6DSRX_AUX_2g:
      *val = LSM6DSRX_AUX_2g;
      break;

    case LSM6DSRX_AUX_16g:
      *val = LSM6DSRX_AUX_16g;
      break;

    case LSM6DSRX_AUX_4g:
      *val = LSM6DSRX_AUX_4g;
      break;

    case LSM6DSRX_AUX_8g:
      *val = LSM6DSRX_AUX_8g;
      break;

    default:
      *val = LSM6DSRX_AUX_2g;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_ main_serial_interface
  * @brief      This section groups all the functions concerning main
  *             serial interface management (not auxiliary)
  * @{
  *
  */

/**
  * @brief  Connect/Disconnect SDO/SA0 internal pull-up.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sdo_pu_en in reg PIN_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sdo_sa0_mode_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sdo_pu_en_t val)
{
  lsm6dsrx_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PIN_CTRL,
                          (uint8_t *)&pin_ctrl, 1);

  if (ret == 0)
  {
    pin_ctrl.sdo_pu_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PIN_CTRL,
                             (uint8_t *)&pin_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Connect/Disconnect SDO/SA0 internal pull-up.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sdo_pu_en in reg PIN_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sdo_sa0_mode_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sdo_pu_en_t *val)
{
  lsm6dsrx_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PIN_CTRL,
                          (uint8_t *)&pin_ctrl, 1);

  switch (pin_ctrl.sdo_pu_en)
  {
    case LSM6DSRX_PULL_UP_DISC:
      *val = LSM6DSRX_PULL_UP_DISC;
      break;

    case LSM6DSRX_PULL_UP_CONNECT:
      *val = LSM6DSRX_PULL_UP_CONNECT;
      break;

    default:
      *val = LSM6DSRX_PULL_UP_DISC;
      break;
  }

  return ret;
}

/**
  * @brief  Connect/Disconnect INT1 pull-down.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pd_dis_int1 in reg I3C_BUS_AVB
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_int1_mode_set(const stmdev_ctx_t *ctx,
                               lsm6dsrx_pd_dis_int1_t val)
{
  lsm6dsrx_i3c_bus_avb_t i3c_bus_avb;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_I3C_BUS_AVB,
                          (uint8_t *)&i3c_bus_avb, 1);

  if (ret == 0)
  {
    i3c_bus_avb.pd_dis_int1 = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_I3C_BUS_AVB,
                             (uint8_t *)&i3c_bus_avb, 1);
  }

  return ret;
}

/**
  * @brief  Connect/Disconnect INT1 pull-down.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of pd_dis_int1 in reg I3C_BUS_AVB
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_int1_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dsrx_pd_dis_int1_t *val)
{
  lsm6dsrx_i3c_bus_avb_t i3c_bus_avb;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_I3C_BUS_AVB,
                          (uint8_t *)&i3c_bus_avb, 1);

  switch (i3c_bus_avb.pd_dis_int1)
  {
    case LSM6DSRX_PULL_DOWN_CONNECT:
      *val = LSM6DSRX_PULL_DOWN_CONNECT;
      break;

    case LSM6DSRX_PULL_DOWN_DISC:
      *val = LSM6DSRX_PULL_DOWN_DISC;
      break;

    default:
      *val = LSM6DSRX_PULL_DOWN_CONNECT;
      break;
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sim in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_spi_mode_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_sim_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.sim = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sim in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_spi_mode_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_sim_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  switch (ctrl3_c.sim)
  {
    case LSM6DSRX_SPI_4_WIRE:
      *val = LSM6DSRX_SPI_4_WIRE;
      break;

    case LSM6DSRX_SPI_3_WIRE:
      *val = LSM6DSRX_SPI_3_WIRE;
      break;

    default:
      *val = LSM6DSRX_SPI_4_WIRE;
      break;
  }

  return ret;
}

/**
  * @brief  Disable / Enable I2C interface.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of i2c_disable in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_i2c_interface_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_i2c_disable_t val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.i2c_disable = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL4_C,
                             (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  Disable / Enable I2C interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of i2c reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_i2c_interface_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_i2c_disable_t *val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);

  switch (ctrl4_c.i2c_disable)
  {
    case LSM6DSRX_I2C_ENABLE:
      *val = LSM6DSRX_I2C_ENABLE;
      break;

    case LSM6DSRX_I2C_DISABLE:
      *val = LSM6DSRX_I2C_DISABLE;
      break;

    default:
      *val = LSM6DSRX_I2C_ENABLE;
      break;
  }

  return ret;
}

/**
  * @brief  I3C Enable/Disable communication protocol.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of i3c_disable in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_i3c_disable_set(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_i3c_disable_t val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  lsm6dsrx_i3c_bus_avb_t i3c_bus_avb;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL, (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.i3c_disable = ((uint8_t)val & 0x80U) >> 7;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL9_XL,
                             (uint8_t *)&ctrl9_xl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_I3C_BUS_AVB,
                            (uint8_t *)&i3c_bus_avb, 1);
  }

  if (ret == 0)
  {
    i3c_bus_avb.i3c_bus_avb_sel = (uint8_t)val & 0x03U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_I3C_BUS_AVB,
                             (uint8_t *)&i3c_bus_avb, 1);
  }

  return ret;
}

/**
  * @brief  I3C Enable/Disable communication protocol.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of i3c_disable in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_i3c_disable_get(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_i3c_disable_t *val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  lsm6dsrx_i3c_bus_avb_t i3c_bus_avb;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL, (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_I3C_BUS_AVB,
                            (uint8_t *)&i3c_bus_avb, 1);
  }

  switch ((ctrl9_xl.i3c_disable << 7) + i3c_bus_avb.i3c_bus_avb_sel)
  {
    case LSM6DSRX_I3C_DISABLE:
      *val = LSM6DSRX_I3C_DISABLE;
      break;

    case LSM6DSRX_I3C_ENABLE_T_50us:
      *val = LSM6DSRX_I3C_ENABLE_T_50us;
      break;

    case LSM6DSRX_I3C_ENABLE_T_2us:
      *val = LSM6DSRX_I3C_ENABLE_T_2us;
      break;

    case LSM6DSRX_I3C_ENABLE_T_1ms:
      *val = LSM6DSRX_I3C_ENABLE_T_1ms;
      break;

    case LSM6DSRX_I3C_ENABLE_T_25ms:
      *val = LSM6DSRX_I3C_ENABLE_T_25ms;
      break;

    default:
      *val = LSM6DSRX_I3C_DISABLE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_interrupt_pins
  * @brief      This section groups all the functions that manage
  *             interrupt pins
  * @{
  *
  */

/**
  * @brief   Select the signal that need to route on int1 pad[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers: INT1_CTRL,MD1_CFG,
  *                EMB_FUNC_INT1, FSM_INT1_A, FSM_INT1_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_int1_route_set(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_pin_int1_route_t *val)
{
  lsm6dsrx_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MLC_INT1,
                             (uint8_t *)&val->mlc_int1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_INT1,
                             (uint8_t *)&val->emb_func_int1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_INT1_A,
                             (uint8_t *)&val->fsm_int1_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_INT1_B,
                             (uint8_t *)&val->fsm_int1_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  if (ret == 0)
  {
    if ((val->emb_func_int1.int1_fsm_lc |
         val->emb_func_int1.int1_sig_mot |
         val->emb_func_int1.int1_step_detector |
         val->emb_func_int1.int1_tilt |
         val->fsm_int1_a.int1_fsm1 |
         val->fsm_int1_a.int1_fsm2 |
         val->fsm_int1_a.int1_fsm3 |
         val->fsm_int1_a.int1_fsm4 |
         val->fsm_int1_a.int1_fsm5 |
         val->fsm_int1_a.int1_fsm6 |
         val->fsm_int1_a.int1_fsm7 |
         val->fsm_int1_a.int1_fsm8 |
         val->fsm_int1_b.int1_fsm9 |
         val->fsm_int1_b.int1_fsm10 |
         val->fsm_int1_b.int1_fsm11 |
         val->fsm_int1_b.int1_fsm12 |
         val->fsm_int1_b.int1_fsm13 |
         val->fsm_int1_b.int1_fsm14 |
         val->fsm_int1_b.int1_fsm15 |
         val->fsm_int1_b.int1_fsm16 |
         val->mlc_int1.int1_mlc1 |
         val->mlc_int1.int1_mlc2 |
         val->mlc_int1.int1_mlc3 |
         val->mlc_int1.int1_mlc4 |
         val->mlc_int1.int1_mlc5 |
         val->mlc_int1.int1_mlc6 |
         val->mlc_int1.int1_mlc7 |
         val->mlc_int1.int1_mlc8) != PROPERTY_DISABLE)
    {
      val->md1_cfg.int1_emb_func = PROPERTY_ENABLE;
    }
    else
    {
      val->md1_cfg.int1_emb_func = PROPERTY_DISABLE;
    }

    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT1_CTRL,
                             (uint8_t *)&val->int1_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MD1_CFG,
                             (uint8_t *)&val->md1_cfg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG2,
                            (uint8_t *)&tap_cfg2, 1);

    if ((val->int1_ctrl.den_drdy_flag |
         val->int1_ctrl.int1_boot |
         val->int1_ctrl.int1_cnt_bdr |
         val->int1_ctrl.int1_drdy_g |
         val->int1_ctrl.int1_drdy_xl |
         val->int1_ctrl.int1_fifo_full |
         val->int1_ctrl.int1_fifo_ovr |
         val->int1_ctrl.int1_fifo_th |
         val->md1_cfg.int1_shub |
         val->md1_cfg.int1_6d |
         val->md1_cfg.int1_double_tap |
         val->md1_cfg.int1_ff |
         val->md1_cfg.int1_wu |
         val->md1_cfg.int1_single_tap |
         val->md1_cfg.int1_sleep_change) != PROPERTY_DISABLE)
    {
      tap_cfg2.interrupts_enable = PROPERTY_ENABLE;
    }

    else
    {
      tap_cfg2.interrupts_enable = PROPERTY_DISABLE;
    }
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG2,
                             (uint8_t *)&tap_cfg2, 1);
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int1 pad.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers: INT1_CTRL, MD1_CFG,
  *                EMB_FUNC_INT1, FSM_INT1_A, FSM_INT1_B.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_int1_route_get(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_pin_int1_route_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MLC_INT1,
                            (uint8_t *)&val->mlc_int1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INT1,
                            (uint8_t *)&val->emb_func_int1, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_INT1_A,
                            (uint8_t *)&val->fsm_int1_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_INT1_B,
                            (uint8_t *)&val->fsm_int1_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT1_CTRL,
                            (uint8_t *)&val->int1_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MD1_CFG,
                            (uint8_t *)&val->md1_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers INT2_CTRL,  MD2_CFG,
  *                EMB_FUNC_INT2, FSM_INT2_A, FSM_INT2_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_int2_route_set(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_pin_int2_route_t *val)
{
  lsm6dsrx_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MLC_INT2,
                             (uint8_t *)&val->mlc_int2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_INT2,
                             (uint8_t *)&val->emb_func_int2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_INT2_A,
                             (uint8_t *)&val->fsm_int2_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_INT2_B,
                             (uint8_t *)&val->fsm_int2_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  if (ret == 0)
  {
    if ((val->emb_func_int2.int2_step_detector |
         val->emb_func_int2.int2_tilt |
         val->emb_func_int2.int2_sig_mot |
         val->emb_func_int2.int2_fsm_lc |
         val->fsm_int2_a.int2_fsm1 |
         val->fsm_int2_a.int2_fsm2 |
         val->fsm_int2_a.int2_fsm3 |
         val->fsm_int2_a.int2_fsm4 |
         val->fsm_int2_a.int2_fsm5 |
         val->fsm_int2_a.int2_fsm6 |
         val->fsm_int2_a.int2_fsm7 |
         val->fsm_int2_a.int2_fsm8 |
         val->fsm_int2_b.int2_fsm9 |
         val->fsm_int2_b.int2_fsm10 |
         val->fsm_int2_b.int2_fsm11 |
         val->fsm_int2_b.int2_fsm12 |
         val->fsm_int2_b.int2_fsm13 |
         val->fsm_int2_b.int2_fsm14 |
         val->fsm_int2_b.int2_fsm15 |
         val->fsm_int2_b.int2_fsm16 |
         val->mlc_int2.int2_mlc1 |
         val->mlc_int2.int2_mlc2 |
         val->mlc_int2.int2_mlc3 |
         val->mlc_int2.int2_mlc4 |
         val->mlc_int2.int2_mlc5 |
         val->mlc_int2.int2_mlc6 |
         val->mlc_int2.int2_mlc7 |
         val->mlc_int2.int2_mlc8) != PROPERTY_DISABLE)
    {
      val->md2_cfg.int2_emb_func = PROPERTY_ENABLE;
    }
    else
    {
      val->md2_cfg.int2_emb_func = PROPERTY_DISABLE;
    }

    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT2_CTRL,
                             (uint8_t *)&val->int2_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MD2_CFG,
                             (uint8_t *)&val->md2_cfg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG2,
                            (uint8_t *)&tap_cfg2, 1);
  }

  if (ret == 0)
  {
    if ((val->int2_ctrl.int2_drdy_xl |
         val->int2_ctrl.int2_drdy_g |
         val->int2_ctrl.int2_drdy_temp |
         val->int2_ctrl.int2_fifo_th |
         val->int2_ctrl.int2_fifo_ovr |
         val->int2_ctrl.int2_fifo_full |
         val->int2_ctrl.int2_cnt_bdr |
         val->md2_cfg.int2_6d |
         val->md2_cfg.int2_double_tap |
         val->md2_cfg.int2_ff |
         val->md2_cfg.int2_wu |
         val->md2_cfg.int2_single_tap |
         val->md2_cfg.int2_sleep_change) != PROPERTY_DISABLE)
    {
      tap_cfg2.interrupts_enable = PROPERTY_ENABLE;
    }

    else
    {
      tap_cfg2.interrupts_enable = PROPERTY_DISABLE;
    }

    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG2,
                             (uint8_t *)&tap_cfg2, 1);
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers INT2_CTRL,  MD2_CFG,
  *                EMB_FUNC_INT2, FSM_INT2_A, FSM_INT2_B.[get]
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_int2_route_get(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_pin_int2_route_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MLC_INT2,
                            (uint8_t *)&val->mlc_int2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INT2,
                            (uint8_t *)&val->emb_func_int2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_INT2_A,
                            (uint8_t *)&val->fsm_int2_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_INT2_B,
                            (uint8_t *)&val->fsm_int2_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT2_CTRL,
                            (uint8_t *)&val->int2_ctrl, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MD2_CFG,
                            (uint8_t *)&val->md2_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pp_od in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_mode_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_pp_od_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.pp_od = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of pp_od in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_mode_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_pp_od_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  switch (ctrl3_c.pp_od)
  {
    case LSM6DSRX_PUSH_PULL:
      *val = LSM6DSRX_PUSH_PULL;
      break;

    case LSM6DSRX_OPEN_DRAIN:
      *val = LSM6DSRX_OPEN_DRAIN;
      break;

    default:
      *val = LSM6DSRX_PUSH_PULL;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of h_lactive in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_polarity_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_h_lactive_t val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.h_lactive = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL3_C,
                             (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of h_lactive in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pin_polarity_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_h_lactive_t *val)
{
  lsm6dsrx_ctrl3_c_t ctrl3_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL3_C,
                          (uint8_t *)&ctrl3_c, 1);

  switch (ctrl3_c.h_lactive)
  {
    case LSM6DSRX_ACTIVE_HIGH:
      *val = LSM6DSRX_ACTIVE_HIGH;
      break;

    case LSM6DSRX_ACTIVE_LOW:
      *val = LSM6DSRX_ACTIVE_LOW;
      break;

    default:
      *val = LSM6DSRX_ACTIVE_HIGH;
      break;
  }

  return ret;
}

/**
  * @brief  All interrupt signals become available on INT1 pin.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of int2_on_int1 in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_all_on_int1_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.int2_on_int1 = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL4_C,
                             (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  All interrupt signals become available on INT1 pin.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of int2_on_int1 in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_all_on_int1_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);
  *val = ctrl4_c.int2_on_int1;

  return ret;
}

/**
  * @brief  All interrupt signals notification mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lir in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_int_notification_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_lir_t val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  lsm6dsrx_page_rw_t page_rw;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.lir = (uint8_t)val & 0x01U;
    tap_cfg0.int_clr_on_read = (uint8_t)val & 0x01U;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG0,
                             (uint8_t *)&tap_cfg0, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    page_rw.emb_func_lir = ((uint8_t)val & 0x02U) >> 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_PAGE_RW,
                             (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  All interrupt signals notification mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of lir in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_int_notification_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_lir_t *val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  lsm6dsrx_page_rw_t page_rw;
  int32_t ret;

  *val = LSM6DSRX_ALL_INT_PULSED;
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_PAGE_RW,
                            (uint8_t *)&page_rw, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch ((page_rw.emb_func_lir << 1) + tap_cfg0.lir)
  {
    case LSM6DSRX_ALL_INT_PULSED:
      *val = LSM6DSRX_ALL_INT_PULSED;
      break;

    case LSM6DSRX_BASE_LATCHED_EMB_PULSED:
      *val = LSM6DSRX_BASE_LATCHED_EMB_PULSED;
      break;

    case LSM6DSRX_BASE_PULSED_EMB_LATCHED:
      *val = LSM6DSRX_BASE_PULSED_EMB_LATCHED;
      break;

    case LSM6DSRX_ALL_INT_LATCHED:
      *val = LSM6DSRX_ALL_INT_LATCHED;
      break;

    default:
      *val = LSM6DSRX_ALL_INT_PULSED;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_Wake_Up_event
  * @brief      This section groups all the functions that manage the
  *             Wake Up event generation.
  * @{
  *
  */

/**
  * @brief  Weight of 1 LSB of wakeup threshold.[set]
  *         0: 1 LSB =FS_XL  /  64
  *         1: 1 LSB = FS_XL / 256
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wake_ths_w in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_wkup_ths_weight_set(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_wake_ths_w_t val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.wake_ths_w = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                             (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Weight of 1 LSB of wakeup threshold.[get]
  *         0: 1 LSB =FS_XL  /  64
  *         1: 1 LSB = FS_XL / 256
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of wake_ths_w in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_wkup_ths_weight_get(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_wake_ths_w_t *val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);

  switch (wake_up_dur.wake_ths_w)
  {
    case LSM6DSRX_LSb_FS_DIV_64:
      *val = LSM6DSRX_LSb_FS_DIV_64;
      break;

    case LSM6DSRX_LSb_FS_DIV_256:
      *val = LSM6DSRX_LSb_FS_DIV_256;
      break;

    default:
      *val = LSM6DSRX_LSb_FS_DIV_64;
      break;
  }

  return ret;
}

/**
  * @brief  Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in
  *         WAKE_UP_DUR.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wk_ths in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_wkup_threshold_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                          (uint8_t *)&wake_up_ths, 1);

  if (ret == 0)
  {
    wake_up_ths.wk_ths = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                             (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in
  *         WAKE_UP_DUR.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wk_ths in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_wkup_threshold_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                          (uint8_t *)&wake_up_ths, 1);
  *val = wake_up_ths.wk_ths;

  return ret;
}

/**
  * @brief  Wake up duration event( 1LSb = 1 / ODR ).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_on_wu in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_on_wkup_set(const stmdev_ctx_t *ctx,
                                           uint8_t val)
{
  lsm6dsrx_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                          (uint8_t *)&wake_up_ths, 1);

  if (ret == 0)
  {
    wake_up_ths.usr_off_on_wu = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                             (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  Wake up duration event( 1LSb = 1 / ODR ).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_on_wu in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_xl_usr_offset_on_wkup_get(const stmdev_ctx_t *ctx,
                                           uint8_t *val)
{
  lsm6dsrx_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                          (uint8_t *)&wake_up_ths, 1);
  *val = wake_up_ths.usr_off_on_wu;

  return ret;
}

/**
  * @brief  Wake up duration event(1LSb = 1 / ODR).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wake_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_wkup_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.wake_dur = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                             (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Wake up duration event(1LSb = 1 / ODR).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wake_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_wkup_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);
  *val = wake_up_dur.wake_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_ Activity/Inactivity_detection
  * @brief      This section groups all the functions concerning
  *             activity/inactivity detection.
  * @{
  *
  */

/**
  * @brief  Enables gyroscope Sleep mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_g in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_sleep_mode_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.sleep_g = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL4_C,
                             (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  Enables gyroscope Sleep mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_g in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_gy_sleep_mode_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_ctrl4_c_t ctrl4_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL4_C,
                          (uint8_t *)&ctrl4_c, 1);
  *val = ctrl4_c.sleep_g;

  return ret;
}

/**
  * @brief  Drives the sleep status instead of sleep change on INT pins
  *         (only if INT1_SLEEP_CHANGE or INT2_SLEEP_CHANGE bits
  *         are enabled).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_status_on_int in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_act_pin_notification_set(const stmdev_ctx_t *ctx,
                                          lsm6dsrx_sleep_status_on_int_t val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0. sleep_status_on_int = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG0,
                             (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  Drives the sleep status instead of sleep change on INT pins
  *         (only if INT1_SLEEP_CHANGE or INT2_SLEEP_CHANGE bits
  *         are enabled).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sleep_status_on_int in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_act_pin_notification_get(const stmdev_ctx_t *ctx,
                                          lsm6dsrx_sleep_status_on_int_t *val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  switch (tap_cfg0. sleep_status_on_int)
  {
    case LSM6DSRX_DRIVE_SLEEP_CHG_EVENT:
      *val = LSM6DSRX_DRIVE_SLEEP_CHG_EVENT;
      break;

    case LSM6DSRX_DRIVE_SLEEP_STATUS:
      *val = LSM6DSRX_DRIVE_SLEEP_STATUS;
      break;

    default:
      *val = LSM6DSRX_DRIVE_SLEEP_CHG_EVENT;
      break;
  }

  return ret;
}

/**
  * @brief  Enable inactivity function.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of inact_en in reg TAP_CFG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_act_mode_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_inact_en_t val)
{
  lsm6dsrx_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG2,
                          (uint8_t *)&tap_cfg2, 1);

  if (ret == 0)
  {
    tap_cfg2.inact_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG2,
                             (uint8_t *)&tap_cfg2, 1);
  }

  return ret;
}

/**
  * @brief  Enable inactivity function.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of inact_en in reg TAP_CFG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_act_mode_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_inact_en_t *val)
{
  lsm6dsrx_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG2,
                          (uint8_t *)&tap_cfg2, 1);

  switch (tap_cfg2.inact_en)
  {
    case LSM6DSRX_XL_AND_GY_NOT_AFFECTED:
      *val = LSM6DSRX_XL_AND_GY_NOT_AFFECTED;
      break;

    case LSM6DSRX_XL_12Hz5_GY_NOT_AFFECTED:
      *val = LSM6DSRX_XL_12Hz5_GY_NOT_AFFECTED;
      break;

    case LSM6DSRX_XL_12Hz5_GY_SLEEP:
      *val = LSM6DSRX_XL_12Hz5_GY_SLEEP;
      break;

    case LSM6DSRX_XL_12Hz5_GY_PD:
      *val = LSM6DSRX_XL_12Hz5_GY_PD;
      break;

    default:
      *val = LSM6DSRX_XL_AND_GY_NOT_AFFECTED;
      break;
  }

  return ret;
}

/**
  * @brief  Duration to go in sleep mode (1 LSb = 512 / ODR).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_act_sleep_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.sleep_dur = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                             (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Duration to go in sleep mode.(1 LSb = 512 / ODR).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_act_sleep_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);
  *val = wake_up_dur.sleep_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_tap_generator
  * @brief      This section groups all the functions that manage the
  *             tap and double tap event generation.
  * @{
  *
  */

/**
  * @brief  Enable Z direction in tap recognition.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_z_en in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_detection_on_z_set(const stmdev_ctx_t *ctx,
                                        uint8_t val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.tap_z_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG0,
                             (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  Enable Z direction in tap recognition.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_z_en in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_detection_on_z_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);
  *val = tap_cfg0.tap_z_en;

  return ret;
}

/**
  * @brief  Enable Y direction in tap recognition.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_y_en in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_detection_on_y_set(const stmdev_ctx_t *ctx,
                                        uint8_t val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.tap_y_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG0,
                             (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  Enable Y direction in tap recognition.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_y_en in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_detection_on_y_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);
  *val = tap_cfg0.tap_y_en;

  return ret;
}

/**
  * @brief  Enable X direction in tap recognition.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_x_en in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_detection_on_x_set(const stmdev_ctx_t *ctx,
                                        uint8_t val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.tap_x_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG0,
                             (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  Enable X direction in tap recognition.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_x_en in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_detection_on_x_get(const stmdev_ctx_t *ctx,
                                        uint8_t *val)
{
  lsm6dsrx_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG0,
                          (uint8_t *)&tap_cfg0, 1);
  *val = tap_cfg0.tap_x_en;

  return ret;
}

/**
  * @brief  X-axis tap recognition threshold.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_ths_x in reg TAP_CFG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_threshold_x_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG1,
                          (uint8_t *)&tap_cfg1, 1);

  if (ret == 0)
  {
    tap_cfg1.tap_ths_x = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG1,
                             (uint8_t *)&tap_cfg1, 1);
  }

  return ret;
}

/**
  * @brief  X-axis tap recognition threshold.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_ths_x in reg TAP_CFG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_threshold_x_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG1,
                          (uint8_t *)&tap_cfg1, 1);
  *val = tap_cfg1.tap_ths_x;

  return ret;
}

/**
  * @brief  Selection of axis priority for TAP detection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_priority in reg TAP_CFG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_axis_priority_set(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_tap_priority_t val)
{
  lsm6dsrx_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG1,
                          (uint8_t *)&tap_cfg1, 1);

  if (ret == 0)
  {
    tap_cfg1.tap_priority = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG1,
                             (uint8_t *)&tap_cfg1, 1);
  }

  return ret;
}

/**
  * @brief  Selection of axis priority for TAP detection[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of tap_priority in reg TAP_CFG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_axis_priority_get(const stmdev_ctx_t *ctx,
                                       lsm6dsrx_tap_priority_t *val)
{
  lsm6dsrx_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG1,
                          (uint8_t *)&tap_cfg1, 1);

  switch (tap_cfg1.tap_priority)
  {
    case LSM6DSRX_XYZ:
      *val = LSM6DSRX_XYZ;
      break;

    case LSM6DSRX_YXZ:
      *val = LSM6DSRX_YXZ;
      break;

    case LSM6DSRX_XZY:
      *val = LSM6DSRX_XZY;
      break;

    case LSM6DSRX_ZYX:
      *val = LSM6DSRX_ZYX;
      break;

    case LSM6DSRX_YZX:
      *val = LSM6DSRX_YZX;
      break;

    case LSM6DSRX_ZXY:
      *val = LSM6DSRX_ZXY;
      break;

    default:
      *val = LSM6DSRX_XYZ;
      break;
  }

  return ret;
}

/**
  * @brief  Y-axis tap recognition threshold.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_ths_y in reg TAP_CFG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_threshold_y_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG2,
                          (uint8_t *)&tap_cfg2, 1);

  if (ret == 0)
  {
    tap_cfg2.tap_ths_y = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_CFG2,
                             (uint8_t *)&tap_cfg2, 1);
  }

  return ret;
}

/**
  * @brief  Y-axis tap recognition threshold.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_ths_y in reg TAP_CFG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_threshold_y_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_tap_cfg2_t tap_cfg2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_CFG2,
                          (uint8_t *)&tap_cfg2, 1);
  *val = tap_cfg2.tap_ths_y;

  return ret;
}

/**
  * @brief  Z-axis recognition threshold.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_ths_z in reg TAP_THS_6D
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_threshold_z_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_THS_6D,
                          (uint8_t *)&tap_ths_6d, 1);

  if (ret == 0)
  {
    tap_ths_6d.tap_ths_z = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_THS_6D,
                             (uint8_t *)&tap_ths_6d, 1);
  }

  return ret;
}

/**
  * @brief  Z-axis recognition threshold.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tap_ths_z in reg TAP_THS_6D
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_threshold_z_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_THS_6D,
                          (uint8_t *)&tap_ths_6d, 1);
  *val = tap_ths_6d.tap_ths_z;

  return ret;
}

/**
  * @brief  Maximum duration is the maximum time of an overthreshold signal
  *         detection to be recognized as a tap event. The default value of
  *         these bits is 00b which corresponds to 4*ODR_XL time.
  *         If the SHOCK[1:0] bits are set to a different value, 1LSB
  *         corresponds to 8*ODR_XL time.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of shock in reg INT_DUR2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_shock_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_int_dur2_t int_dur2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_DUR2,
                          (uint8_t *)&int_dur2, 1);

  if (ret == 0)
  {
    int_dur2.shock = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_DUR2,
                             (uint8_t *)&int_dur2, 1);
  }

  return ret;
}

/**
  * @brief  Maximum duration is the maximum time of an overthreshold signal
  *         detection to be recognized as a tap event. The default value of
  *         these bits is 00b which corresponds to 4*ODR_XL time.
  *         If the SHOCK[1:0] bits are set to a different value, 1LSB
  *         corresponds to 8*ODR_XL time.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of shock in reg INT_DUR2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_shock_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_int_dur2_t int_dur2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_DUR2,
                          (uint8_t *)&int_dur2, 1);
  *val = int_dur2.shock;

  return ret;
}

/**
  * @brief  Quiet time is the time after the first detected tap in which
  *         there must not be any overthreshold event.
  *         The default value of these bits is 00b which corresponds to
  *         2*ODR_XL time. If the QUIET[1:0] bits are set to a different
  *         value, 1LSB corresponds to 4*ODR_XL time.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of quiet in reg INT_DUR2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_quiet_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_int_dur2_t int_dur2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_DUR2,
                          (uint8_t *)&int_dur2, 1);

  if (ret == 0)
  {
    int_dur2.quiet = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_DUR2,
                             (uint8_t *)&int_dur2, 1);
  }

  return ret;
}

/**
  * @brief  Quiet time is the time after the first detected tap in which
  *         there must not be any overthreshold event.
  *         The default value of these bits is 00b which corresponds to
  *         2*ODR_XL time. If the QUIET[1:0] bits are set to a different
  *         value, 1LSB corresponds to 4*ODR_XL time.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of quiet in reg INT_DUR2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_quiet_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_int_dur2_t int_dur2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_DUR2,
                          (uint8_t *)&int_dur2, 1);
  *val = int_dur2.quiet;

  return ret;
}

/**
  * @brief  When double tap recognition is enabled, this register expresses
  *         the maximum time between two consecutive detected taps to
  *         determine a double tap event.
  *         The default value of these bits is 0000b which corresponds to
  *         16*ODR_XL time.
  *         If the DUR[3:0] bits are set to a different value, 1LSB
  *         corresponds to 32*ODR_XL time.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of dur in reg INT_DUR2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_int_dur2_t int_dur2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_DUR2,
                          (uint8_t *)&int_dur2, 1);

  if (ret == 0)
  {
    int_dur2.dur = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_INT_DUR2,
                             (uint8_t *)&int_dur2, 1);
  }

  return ret;
}

/**
  * @brief  When double tap recognition is enabled, this register expresses the
  *         maximum time between two consecutive detected taps to determine
  *         a double tap event. The default value of these bits is 0000b which
  *         corresponds to 16*ODR_XL time. If the DUR[3:0] bits are set to
  *         a different value, 1LSB corresponds to 32*ODR_XL time.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of dur in reg INT_DUR2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_int_dur2_t int_dur2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_INT_DUR2,
                          (uint8_t *)&int_dur2, 1);
  *val = int_dur2.dur;

  return ret;
}

/**
  * @brief  Single/double-tap event enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of single_double_tap in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_mode_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_single_double_tap_t val)
{
  lsm6dsrx_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                          (uint8_t *)&wake_up_ths, 1);

  if (ret == 0)
  {
    wake_up_ths.single_double_tap = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                             (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  Single/double-tap event enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of single_double_tap in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tap_mode_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_single_double_tap_t *val)
{
  lsm6dsrx_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_THS,
                          (uint8_t *)&wake_up_ths, 1);

  switch (wake_up_ths.single_double_tap)
  {
    case LSM6DSRX_ONLY_SINGLE:
      *val = LSM6DSRX_ONLY_SINGLE;
      break;

    case LSM6DSRX_BOTH_SINGLE_DOUBLE:
      *val = LSM6DSRX_BOTH_SINGLE_DOUBLE;
      break;

    default:
      *val = LSM6DSRX_ONLY_SINGLE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_ Six_position_detection(6D/4D)
  * @brief      This section groups all the functions concerning six
  *             position detection (6D).
  * @{
  *
  */

/**
  * @brief  Threshold for 4D/6D function.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sixd_ths in reg TAP_THS_6D
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_6d_threshold_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sixd_ths_t val)
{
  lsm6dsrx_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_THS_6D,
                          (uint8_t *)&tap_ths_6d, 1);

  if (ret == 0)
  {
    tap_ths_6d.sixd_ths = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_THS_6D,
                             (uint8_t *)&tap_ths_6d, 1);
  }

  return ret;
}

/**
  * @brief  Threshold for 4D/6D function.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sixd_ths in reg TAP_THS_6D
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_6d_threshold_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sixd_ths_t *val)
{
  lsm6dsrx_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_THS_6D,
                          (uint8_t *)&tap_ths_6d, 1);

  switch (tap_ths_6d.sixd_ths)
  {
    case LSM6DSRX_DEG_80:
      *val = LSM6DSRX_DEG_80;
      break;

    case LSM6DSRX_DEG_70:
      *val = LSM6DSRX_DEG_70;
      break;

    case LSM6DSRX_DEG_60:
      *val = LSM6DSRX_DEG_60;
      break;

    case LSM6DSRX_DEG_50:
      *val = LSM6DSRX_DEG_50;
      break;

    default:
      *val = LSM6DSRX_DEG_80;
      break;
  }

  return ret;
}

/**
  * @brief  4D orientation detection enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of d4d_en in reg TAP_THS_6D
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_4d_mode_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_THS_6D,
                          (uint8_t *)&tap_ths_6d, 1);

  if (ret == 0)
  {
    tap_ths_6d.d4d_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_TAP_THS_6D,
                             (uint8_t *)&tap_ths_6d, 1);
  }

  return ret;
}

/**
  * @brief  4D orientation detection enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of d4d_en in reg TAP_THS_6D
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_4d_mode_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_TAP_THS_6D,
                          (uint8_t *)&tap_ths_6d, 1);
  *val = tap_ths_6d.d4d_en;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_free_fall
  * @brief      This section group all the functions concerning the free
  *             fall detection.
  * @{
  *
  */

/**
  * @brief  Free fall threshold setting.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ff_ths in reg FREE_FALL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ff_threshold_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_ff_ths_t val)
{
  lsm6dsrx_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FREE_FALL,
                          (uint8_t *)&free_fall, 1);

  if (ret == 0)
  {
    free_fall.ff_ths = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FREE_FALL,
                             (uint8_t *)&free_fall, 1);
  }

  return ret;
}

/**
  * @brief  Free fall threshold setting.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of ff_ths in reg FREE_FALL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ff_threshold_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_ff_ths_t *val)
{
  lsm6dsrx_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FREE_FALL,
                          (uint8_t *)&free_fall, 1);

  switch (free_fall.ff_ths)
  {
    case LSM6DSRX_FF_TSH_156mg:
      *val = LSM6DSRX_FF_TSH_156mg;
      break;

    case LSM6DSRX_FF_TSH_219mg:
      *val = LSM6DSRX_FF_TSH_219mg;
      break;

    case LSM6DSRX_FF_TSH_250mg:
      *val = LSM6DSRX_FF_TSH_250mg;
      break;

    case LSM6DSRX_FF_TSH_312mg:
      *val = LSM6DSRX_FF_TSH_312mg;
      break;

    case LSM6DSRX_FF_TSH_344mg:
      *val = LSM6DSRX_FF_TSH_344mg;
      break;

    case LSM6DSRX_FF_TSH_406mg:
      *val = LSM6DSRX_FF_TSH_406mg;
      break;

    case LSM6DSRX_FF_TSH_469mg:
      *val = LSM6DSRX_FF_TSH_469mg;
      break;

    case LSM6DSRX_FF_TSH_500mg:
      *val = LSM6DSRX_FF_TSH_500mg;
      break;

    default:
      *val = LSM6DSRX_FF_TSH_156mg;
      break;
  }

  return ret;
}

/**
  * @brief  Free-fall duration event(1LSb = 1 / ODR).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ff_dur in reg FREE_FALL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ff_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  lsm6dsrx_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.ff_dur = (val & 0x20U) >> 5;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                             (uint8_t *)&wake_up_dur, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FREE_FALL,
                            (uint8_t *)&free_fall, 1);
  }

  if (ret == 0)
  {
    free_fall.ff_dur = val & 0x1FU;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FREE_FALL,
                             (uint8_t *)&free_fall, 1);
  }

  return ret;
}

/**
  * @brief  Free-fall duration event(1LSb = 1 / ODR).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of ff_dur in reg FREE_FALL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_ff_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_wake_up_dur_t wake_up_dur;
  lsm6dsrx_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_WAKE_UP_DUR,
                          (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FREE_FALL,
                            (uint8_t *)&free_fall, 1);
  }

  *val = (wake_up_dur.ff_dur << 5) + free_fall.ff_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_fifo
  * @brief      This section group all the functions concerning
  *             the fifo usage
  * @{
  *
  */

/**
  * @brief  FIFO watermark level selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wtm in reg FIFO_CTRL1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_watermark_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  lsm6dsrx_fifo_ctrl1_t fifo_ctrl1;
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL1, (uint8_t *)&fifo_ctrl1, 1);
  ret += lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl1.wtm = (uint8_t)(val  & 0xFFU);
    fifo_ctrl2.wtm = (uint8_t)(val / 256U) & 0x01U;

    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL1, (uint8_t *)&fifo_ctrl1, 1);
    ret += lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wtm in reg FIFO_CTRL1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_watermark_get(const stmdev_ctx_t *ctx,
                                    uint16_t *val)
{
  lsm6dsrx_fifo_ctrl1_t fifo_ctrl1;
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL1, (uint8_t *)&fifo_ctrl1, 1);
  ret += lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);

  *val = fifo_ctrl2.wtm;
  *val = (*val * 256U) +  fifo_ctrl1.wtm;;

  return ret;
}

/**
  * @brief  FIFO compression feature initialization request.[set].
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of FIFO_COMPR_INIT in reg EMB_FUNC_INIT_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_compression_algo_init_set(const stmdev_ctx_t *ctx,
                                           uint8_t val)
{
  lsm6dsrx_emb_func_init_b_t emb_func_init_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                            (uint8_t *)&emb_func_init_b, 1);
  }

  if (ret == 0)
  {
    emb_func_init_b.fifo_compr_init = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                             (uint8_t *)&emb_func_init_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FIFO compression feature initialization request.[get].
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    change the values of FIFO_COMPR_INIT in
  *                reg EMB_FUNC_INIT_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_compression_algo_init_get(const stmdev_ctx_t *ctx,
                                           uint8_t *val)
{
  lsm6dsrx_emb_func_init_b_t emb_func_init_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                            (uint8_t *)&emb_func_init_b, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_init_b.fifo_compr_init;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable and configure compression algo.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of uncoptr_rate in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_compression_algo_set(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_uncoptr_rate_t val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  lsm6dsrx_emb_func_en_b_t emb_func_en_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                            (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    emb_func_en_b.fifo_compr_en = ((uint8_t)val & 0x04U) >> 2;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                            (uint8_t *)&fifo_ctrl2, 1);
  }

  if (ret == 0)
  {
    fifo_ctrl2.fifo_compr_rt_en = ((uint8_t)val & 0x04U) >> 2;
    fifo_ctrl2.uncoptr_rate = (uint8_t)val & 0x03U;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                             (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Enable and configure compression algo.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of uncoptr_rate in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_compression_algo_get(const stmdev_ctx_t *ctx,
                                      lsm6dsrx_uncoptr_rate_t *val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);

  switch ((fifo_ctrl2.fifo_compr_rt_en << 2) +
          fifo_ctrl2.uncoptr_rate)
  {
    case LSM6DSRX_CMP_DISABLE:
      *val = LSM6DSRX_CMP_DISABLE;
      break;

    case LSM6DSRX_CMP_ALWAYS:
      *val = LSM6DSRX_CMP_ALWAYS;
      break;

    case LSM6DSRX_CMP_8_TO_1:
      *val = LSM6DSRX_CMP_8_TO_1;
      break;

    case LSM6DSRX_CMP_16_TO_1:
      *val = LSM6DSRX_CMP_16_TO_1;
      break;

    case LSM6DSRX_CMP_32_TO_1:
      *val = LSM6DSRX_CMP_32_TO_1;
      break;

    default:
      *val = LSM6DSRX_CMP_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Enables ODR CHANGE virtual sensor to be batched in FIFO.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odrchg_en in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_virtual_sens_odr_chg_set(const stmdev_ctx_t *ctx,
                                               uint8_t val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl2.odrchg_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                             (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Enables ODR CHANGE virtual sensor to be batched in FIFO.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odrchg_en in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_virtual_sens_odr_chg_get(const stmdev_ctx_t *ctx,
                                               uint8_t *val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.odrchg_en;

  return ret;
}

/**
  * @brief  Enables/Disables compression algorithm runtime[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fifo_compr_rt_en in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_compression_algo_real_time_set(const stmdev_ctx_t *ctx,
                                                uint8_t val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl2.fifo_compr_rt_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                             (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Enables/Disables compression algorithm runtime.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fifo_compr_rt_en in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_compression_algo_real_time_get(const stmdev_ctx_t *ctx,
                                                uint8_t *val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.fifo_compr_rt_en;

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at threshold
  *         level.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of stop_on_wtm in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_stop_on_wtm_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl2.stop_on_wtm = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                             (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at threshold
  *         level.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of stop_on_wtm in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_stop_on_wtm_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL2,
                          (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.stop_on_wtm;

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for accelerometer data.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdr_xl in reg FIFO_CTRL3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_xl_batch_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_bdr_xl_t val)
{
  lsm6dsrx_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL3,
                          (uint8_t *)&fifo_ctrl3, 1);

  if (ret == 0)
  {
    fifo_ctrl3.bdr_xl = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL3,
                             (uint8_t *)&fifo_ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for accelerometer data.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of bdr_xl in reg FIFO_CTRL3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_xl_batch_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_bdr_xl_t *val)
{
  lsm6dsrx_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL3,
                          (uint8_t *)&fifo_ctrl3, 1);

  switch (fifo_ctrl3.bdr_xl)
  {
    case LSM6DSRX_XL_NOT_BATCHED:
      *val = LSM6DSRX_XL_NOT_BATCHED;
      break;

    case LSM6DSRX_XL_BATCHED_AT_12Hz5:
      *val = LSM6DSRX_XL_BATCHED_AT_12Hz5;
      break;

    case LSM6DSRX_XL_BATCHED_AT_26Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_26Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_52Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_52Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_104Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_104Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_208Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_208Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_417Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_417Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_833Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_833Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_1667Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_1667Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_3333Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_3333Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_6667Hz:
      *val = LSM6DSRX_XL_BATCHED_AT_6667Hz;
      break;

    case LSM6DSRX_XL_BATCHED_AT_6Hz5:
      *val = LSM6DSRX_XL_BATCHED_AT_6Hz5;
      break;

    default:
      *val = LSM6DSRX_XL_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for gyroscope data.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdr_gy in reg FIFO_CTRL3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_gy_batch_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_bdr_gy_t val)
{
  lsm6dsrx_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL3,
                          (uint8_t *)&fifo_ctrl3, 1);

  if (ret == 0)
  {
    fifo_ctrl3.bdr_gy = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL3,
                             (uint8_t *)&fifo_ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for gyroscope data.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of bdr_gy in reg FIFO_CTRL3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_gy_batch_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_bdr_gy_t *val)
{
  lsm6dsrx_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL3,
                          (uint8_t *)&fifo_ctrl3, 1);

  switch (fifo_ctrl3.bdr_gy)
  {
    case LSM6DSRX_GY_NOT_BATCHED:
      *val = LSM6DSRX_GY_NOT_BATCHED;
      break;

    case LSM6DSRX_GY_BATCHED_AT_12Hz5:
      *val = LSM6DSRX_GY_BATCHED_AT_12Hz5;
      break;

    case LSM6DSRX_GY_BATCHED_AT_26Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_26Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_52Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_52Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_104Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_104Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_208Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_208Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_417Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_417Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_833Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_833Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_1667Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_1667Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_3333Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_3333Hz;
      break;

    case LSM6DSRX_GY_BATCHED_AT_6667Hz:
      *val = LSM6DSRX_GY_BATCHED_AT_6667Hz;
      break;

    case LSM6DSRX_GY_BATCHED_6Hz5:
      *val = LSM6DSRX_GY_BATCHED_6Hz5;
      break;

    default:
      *val = LSM6DSRX_GY_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fifo_mode in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_mode_set(const stmdev_ctx_t *ctx,
                               lsm6dsrx_fifo_mode_t val)
{
  lsm6dsrx_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                          (uint8_t *)&fifo_ctrl4, 1);

  if (ret == 0)
  {
    fifo_ctrl4.fifo_mode = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                             (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fifo_mode in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_mode_get(const stmdev_ctx_t *ctx,
                               lsm6dsrx_fifo_mode_t *val)
{
  lsm6dsrx_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                          (uint8_t *)&fifo_ctrl4, 1);

  switch (fifo_ctrl4.fifo_mode)
  {
    case LSM6DSRX_BYPASS_MODE:
      *val = LSM6DSRX_BYPASS_MODE;
      break;

    case LSM6DSRX_FIFO_MODE:
      *val = LSM6DSRX_FIFO_MODE;
      break;

    case LSM6DSRX_STREAM_TO_FIFO_MODE:
      *val = LSM6DSRX_STREAM_TO_FIFO_MODE;
      break;

    case LSM6DSRX_BYPASS_TO_STREAM_MODE:
      *val = LSM6DSRX_BYPASS_TO_STREAM_MODE;
      break;

    case LSM6DSRX_STREAM_MODE:
      *val = LSM6DSRX_STREAM_MODE;
      break;

    case LSM6DSRX_BYPASS_TO_FIFO_MODE:
      *val = LSM6DSRX_BYPASS_TO_FIFO_MODE;
      break;

    default:
      *val = LSM6DSRX_BYPASS_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for temperature data.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odr_t_batch in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_temp_batch_set(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_odr_t_batch_t val)
{
  lsm6dsrx_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                          (uint8_t *)&fifo_ctrl4, 1);

  if (ret == 0)
  {
    fifo_ctrl4.odr_t_batch = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                             (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for temperature data.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_t_batch in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_temp_batch_get(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_odr_t_batch_t *val)
{
  lsm6dsrx_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                          (uint8_t *)&fifo_ctrl4, 1);

  switch (fifo_ctrl4.odr_t_batch)
  {
    case LSM6DSRX_TEMP_NOT_BATCHED:
      *val = LSM6DSRX_TEMP_NOT_BATCHED;
      break;

    case LSM6DSRX_TEMP_BATCHED_AT_52Hz:
      *val = LSM6DSRX_TEMP_BATCHED_AT_52Hz;
      break;

    case LSM6DSRX_TEMP_BATCHED_AT_12Hz5:
      *val = LSM6DSRX_TEMP_BATCHED_AT_12Hz5;
      break;

    case LSM6DSRX_TEMP_BATCHED_AT_1Hz6:
      *val = LSM6DSRX_TEMP_BATCHED_AT_1Hz6;
      break;

    default:
      *val = LSM6DSRX_TEMP_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO.
  *         Writing rate will be the maximum rate between XL and
  *         GYRO BDR divided by decimation decoder.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odr_ts_batch in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_timestamp_decimation_set(const stmdev_ctx_t *ctx,
                                               lsm6dsrx_odr_ts_batch_t val)
{
  lsm6dsrx_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                          (uint8_t *)&fifo_ctrl4, 1);

  if (ret == 0)
  {
    fifo_ctrl4.odr_ts_batch = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                             (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO.
  *         Writing rate will be the maximum rate between XL and
  *         GYRO BDR divided by decimation decoder.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_ts_batch in reg
  *                                 FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_timestamp_decimation_get(const stmdev_ctx_t *ctx,
                                               lsm6dsrx_odr_ts_batch_t *val)
{
  lsm6dsrx_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_CTRL4,
                          (uint8_t *)&fifo_ctrl4, 1);

  switch (fifo_ctrl4.odr_ts_batch)
  {
    case LSM6DSRX_NO_DECIMATION:
      *val = LSM6DSRX_NO_DECIMATION;
      break;

    case LSM6DSRX_DEC_1:
      *val = LSM6DSRX_DEC_1;
      break;

    case LSM6DSRX_DEC_8:
      *val = LSM6DSRX_DEC_8;
      break;

    case LSM6DSRX_DEC_32:
      *val = LSM6DSRX_DEC_32;
      break;

    default:
      *val = LSM6DSRX_NO_DECIMATION;
      break;
  }

  return ret;
}

/**
  * @brief  Selects the trigger for the internal counter of batching events
  *         between XL and gyro.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of trig_counter_bdr in
  *                reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_cnt_event_batch_set(const stmdev_ctx_t *ctx,
                                          lsm6dsrx_trig_counter_bdr_t val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.trig_counter_bdr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                             (uint8_t *)&counter_bdr_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Selects the trigger for the internal counter of batching events
  *          between XL and gyro.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of trig_counter_bdr
  *                in reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_cnt_event_batch_get(const stmdev_ctx_t *ctx,
                                          lsm6dsrx_trig_counter_bdr_t *val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  switch (counter_bdr_reg1.trig_counter_bdr)
  {
    case LSM6DSRX_XL_BATCH_EVENT:
      *val = LSM6DSRX_XL_BATCH_EVENT;
      break;

    case LSM6DSRX_GYRO_BATCH_EVENT:
      *val = LSM6DSRX_GYRO_BATCH_EVENT;
      break;

    default:
      *val = LSM6DSRX_XL_BATCH_EVENT;
      break;
  }

  return ret;
}

/**
  * @brief  Resets the internal counter of batching events for a single sensor.
  *         This bit is automatically reset to zero if it was set to '1'.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rst_counter_bdr in reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_rst_batch_counter_set(const stmdev_ctx_t *ctx,
                                       uint8_t val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.rst_counter_bdr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                             (uint8_t *)&counter_bdr_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Resets the internal counter of batching events for a single sensor.
  *         This bit is automatically reset to zero if it was set to '1'.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rst_counter_bdr in reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_rst_batch_counter_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);
  *val = counter_bdr_reg1.rst_counter_bdr;

  return ret;
}

/**
  * @brief  Batch data rate counter.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of cnt_bdr_th in reg COUNTER_BDR_REG2
  *                and COUNTER_BDR_REG1.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_batch_counter_threshold_set(const stmdev_ctx_t *ctx,
                                             uint16_t val)
{
  lsm6dsrx_counter_bdr_reg2_t counter_bdr_reg1;
  lsm6dsrx_counter_bdr_reg2_t counter_bdr_reg2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.cnt_bdr_th = (uint8_t)((val / 256U) & 0x07U);
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                             (uint8_t *)&counter_bdr_reg1, 1);
  }

  if (ret == 0)
  {
    counter_bdr_reg2.cnt_bdr_th = (uint8_t)(val -
                                            (counter_bdr_reg1.cnt_bdr_th * 256U));
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_COUNTER_BDR_REG2,
                             (uint8_t *)&counter_bdr_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Batch data rate counter.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of cnt_bdr_th in reg COUNTER_BDR_REG2
  *                and COUNTER_BDR_REG1.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_batch_counter_threshold_get(const stmdev_ctx_t *ctx,
                                             uint16_t *val)
{
  lsm6dsrx_counter_bdr_reg1_t counter_bdr_reg1;
  lsm6dsrx_counter_bdr_reg2_t counter_bdr_reg2;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG1,
                          (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_COUNTER_BDR_REG2,
                            (uint8_t *)&counter_bdr_reg2, 1);
  }

  *val = counter_bdr_reg1.cnt_bdr_th;
  *val = (*val * 256U) +  counter_bdr_reg2.cnt_bdr_th;

  return ret;
}

/**
  * @brief  Number of unread sensor data (TAG + 6 bytes) stored in FIFO.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the value of diff_fifo in reg FIFO_STATUS1 and FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_data_level_get(const stmdev_ctx_t *ctx,
                                     uint16_t *val)
{
  uint8_t reg[2];
  lsm6dsrx_fifo_status1_t *fifo_status1 = (lsm6dsrx_fifo_status1_t *)&reg[0];
  lsm6dsrx_fifo_status2_t *fifo_status2 = (lsm6dsrx_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->diff_fifo;
    *val = (*val * 256U) + fifo_status1->diff_fifo;
  }

  return ret;
}

/**
  * @brief  Smart FIFO status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read registers FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_status_get(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_fifo_status2_t *val)
{
  uint8_t reg[2];
  lsm6dsrx_fifo_status2_t *fifo_status2 = (lsm6dsrx_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = *fifo_status2;
  }

  return ret;
}

/**
  * @brief  Smart FIFO full status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the values of fifo_full_ia in reg FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_full_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  uint8_t reg[2];
  lsm6dsrx_fifo_status2_t *fifo_status2 = (lsm6dsrx_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->fifo_full_ia;
  }

  return ret;
}

/**
  * @brief  FIFO overrun status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the values of  fifo_over_run_latched in
  *                reg FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_ovr_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  uint8_t reg[2];
  lsm6dsrx_fifo_status2_t *fifo_status2 = (lsm6dsrx_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->fifo_ovr_ia;
  }

  return ret;
}

/**
  * @brief  FIFO watermark status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Read the values of fifo_wtm_ia in reg FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_wtm_flag_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  uint8_t reg[2];
  lsm6dsrx_fifo_status2_t *fifo_status2 = (lsm6dsrx_fifo_status2_t *)&reg[1];
  int32_t ret;

  /* read both FIFO_STATUS1 + FIFO_STATUS2 regs */
  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_STATUS1, (uint8_t *)reg, 2);
  if (ret == 0)
  {
    *val = fifo_status2->fifo_wtm_ia;
  }

  return ret;
}

/**
  * @brief  Identifies the sensor in FIFO_DATA_OUT.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tag_sensor in reg FIFO_DATA_OUT_TAG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_sensor_tag_get(const stmdev_ctx_t *ctx,
                                     lsm6dsrx_fifo_tag_t *val)
{
  lsm6dsrx_fifo_data_out_tag_t fifo_data_out_tag;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FIFO_DATA_OUT_TAG,
                          (uint8_t *)&fifo_data_out_tag, 1);

  switch (fifo_data_out_tag.tag_sensor)
  {
    case LSM6DSRX_GYRO_NC_TAG:
      *val = LSM6DSRX_GYRO_NC_TAG;
      break;

    case LSM6DSRX_XL_NC_TAG:
      *val = LSM6DSRX_XL_NC_TAG;
      break;

    case LSM6DSRX_TEMPERATURE_TAG:
      *val = LSM6DSRX_TEMPERATURE_TAG;
      break;

    case LSM6DSRX_TIMESTAMP_TAG:
      *val = LSM6DSRX_TIMESTAMP_TAG;
      break;

    case LSM6DSRX_CFG_CHANGE_TAG:
      *val = LSM6DSRX_CFG_CHANGE_TAG;
      break;

    case LSM6DSRX_XL_NC_T_2_TAG:
      *val = LSM6DSRX_XL_NC_T_2_TAG;
      break;

    case LSM6DSRX_XL_NC_T_1_TAG:
      *val = LSM6DSRX_XL_NC_T_1_TAG;
      break;

    case LSM6DSRX_XL_2XC_TAG:
      *val = LSM6DSRX_XL_2XC_TAG;
      break;

    case LSM6DSRX_XL_3XC_TAG:
      *val = LSM6DSRX_XL_3XC_TAG;
      break;

    case LSM6DSRX_GYRO_NC_T_2_TAG:
      *val = LSM6DSRX_GYRO_NC_T_2_TAG;
      break;

    case LSM6DSRX_GYRO_NC_T_1_TAG:
      *val = LSM6DSRX_GYRO_NC_T_1_TAG;
      break;

    case LSM6DSRX_GYRO_2XC_TAG:
      *val = LSM6DSRX_GYRO_2XC_TAG;
      break;

    case LSM6DSRX_GYRO_3XC_TAG:
      *val = LSM6DSRX_GYRO_3XC_TAG;
      break;

    case LSM6DSRX_SENSORHUB_SLAVE0_TAG:
      *val = LSM6DSRX_SENSORHUB_SLAVE0_TAG;
      break;

    case LSM6DSRX_SENSORHUB_SLAVE1_TAG:
      *val = LSM6DSRX_SENSORHUB_SLAVE1_TAG;
      break;

    case LSM6DSRX_SENSORHUB_SLAVE2_TAG:
      *val = LSM6DSRX_SENSORHUB_SLAVE2_TAG;
      break;

    case LSM6DSRX_SENSORHUB_SLAVE3_TAG:
      *val = LSM6DSRX_SENSORHUB_SLAVE3_TAG;
      break;

    case LSM6DSRX_STEP_CPUNTER_TAG:
      *val = LSM6DSRX_STEP_CPUNTER_TAG;
      break;

    case LSM6DSRX_SENSORHUB_NACK_TAG:
      *val = LSM6DSRX_SENSORHUB_NACK_TAG;
      break;

    default:
      *val = LSM6DSRX_SENSORHUB_NACK_TAG;
      break;
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching of pedometer embedded function values.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of gbias_fifo_en in
  *                reg LSM6DSRX_EMB_FUNC_FIFO_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_pedo_batch_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_emb_func_fifo_cfg_t emb_func_fifo_cfg;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_FIFO_CFG,
                            (uint8_t *)&emb_func_fifo_cfg, 1);
  }

  if (ret == 0)
  {
    emb_func_fifo_cfg.pedo_fifo_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_FIFO_CFG,
                             (uint8_t *)&emb_func_fifo_cfg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching of pedometer embedded function values.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pedo_fifo_en in reg
  *                LSM6DSRX_EMB_FUNC_FIFO_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fifo_pedo_batch_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_emb_func_fifo_cfg_t emb_func_fifo_cfg;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_FIFO_CFG,
                            (uint8_t *)&emb_func_fifo_cfg, 1);
    *val = emb_func_fifo_cfg.pedo_fifo_en;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of first slave.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_0_en in reg SLV0_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_0_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                            (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config. batch_ext_sens_0_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                             (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of first slave.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_0_en in
  *                reg SLV0_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_0_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                            (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    *val = slv0_config. batch_ext_sens_0_en;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of second slave.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_1_en in
  *                reg SLV1_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_1_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_slv1_config_t slv1_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV1_CONFIG,
                            (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    slv1_config. batch_ext_sens_1_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV1_CONFIG,
                             (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of second slave.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_1_en in
  *                reg SLV1_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_1_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_slv1_config_t slv1_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV1_CONFIG,
                            (uint8_t *)&slv1_config, 1);
    *val = slv1_config. batch_ext_sens_1_en;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of third slave.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_2_en in
  *                reg SLV2_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_2_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_slv2_config_t slv2_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV2_CONFIG,
                            (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    slv2_config. batch_ext_sens_2_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV2_CONFIG,
                             (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of third slave.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_2_en in
  *                reg SLV2_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_2_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_slv2_config_t slv2_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV2_CONFIG,
                            (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    *val = slv2_config. batch_ext_sens_2_en;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of fourth slave.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_3_en in
  *                reg SLV3_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_3_set(const stmdev_ctx_t *ctx,
                                      uint8_t val)
{
  lsm6dsrx_slv3_config_t slv3_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV3_CONFIG,
                            (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    slv3_config. batch_ext_sens_3_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV3_CONFIG,
                             (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO batching data of fourth slave.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of  batch_ext_sens_3_en in
  *                reg SLV3_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_batch_slave_3_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_slv3_config_t slv3_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV3_CONFIG,
                            (uint8_t *)&slv3_config, 1);
    *val = slv3_config. batch_ext_sens_3_en;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_DEN_functionality
  * @brief      This section groups all the functions concerning
  *             DEN functionality.
  * @{
  *
  */

/**
  * @brief  DEN functionality marking mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_mode in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mode_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_den_mode_t val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  if (ret == 0)
  {
    ctrl6_c.den_mode = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL6_C,
                             (uint8_t *)&ctrl6_c, 1);
  }

  return ret;
}

/**
  * @brief  DEN functionality marking mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of den_mode in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mode_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_den_mode_t *val)
{
  lsm6dsrx_ctrl6_c_t ctrl6_c;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL6_C,
                          (uint8_t *)&ctrl6_c, 1);

  switch (ctrl6_c.den_mode)
  {
    case LSM6DSRX_DEN_DISABLE:
      *val = LSM6DSRX_DEN_DISABLE;
      break;

    case LSM6DSRX_LEVEL_FIFO:
      *val = LSM6DSRX_LEVEL_FIFO;
      break;

    case LSM6DSRX_LEVEL_LETCHED:
      *val = LSM6DSRX_LEVEL_LETCHED;
      break;

    case LSM6DSRX_LEVEL_TRIGGER:
      *val = LSM6DSRX_LEVEL_TRIGGER;
      break;

    case LSM6DSRX_EDGE_TRIGGER:
      *val = LSM6DSRX_EDGE_TRIGGER;
      break;

    default:
      *val = LSM6DSRX_DEN_DISABLE;
      break;
  }

  return ret;
}

/**
  * @brief  DEN active level configuration.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_lh in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_polarity_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_den_lh_t val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.den_lh = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL9_XL,
                             (uint8_t *)&ctrl9_xl, 1);
  }

  return ret;
}

/**
  * @brief  DEN active level configuration.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of den_lh in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_polarity_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_den_lh_t *val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  switch (ctrl9_xl.den_lh)
  {
    case LSM6DSRX_DEN_ACT_LOW:
      *val = LSM6DSRX_DEN_ACT_LOW;
      break;

    case LSM6DSRX_DEN_ACT_HIGH:
      *val = LSM6DSRX_DEN_ACT_HIGH;
      break;

    default:
      *val = LSM6DSRX_DEN_ACT_LOW;
      break;
  }

  return ret;
}

/**
  * @brief  DEN configuration.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_xl_g in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_enable_set(const stmdev_ctx_t *ctx,
                                lsm6dsrx_den_xl_g_t val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.den_xl_g = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL9_XL,
                             (uint8_t *)&ctrl9_xl, 1);
  }

  return ret;
}

/**
  * @brief  DEN configuration.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of den_xl_g in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_enable_get(const stmdev_ctx_t *ctx,
                                lsm6dsrx_den_xl_g_t *val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  switch (ctrl9_xl.den_xl_g)
  {
    case LSM6DSRX_STAMP_IN_GY_DATA:
      *val = LSM6DSRX_STAMP_IN_GY_DATA;
      break;

    case LSM6DSRX_STAMP_IN_XL_DATA:
      *val = LSM6DSRX_STAMP_IN_XL_DATA;
      break;

    case LSM6DSRX_STAMP_IN_GY_XL_DATA:
      *val = LSM6DSRX_STAMP_IN_GY_XL_DATA;
      break;

    default:
      *val = LSM6DSRX_STAMP_IN_GY_DATA;
      break;
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of X-axis.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_z in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mark_axis_x_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.den_z = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL9_XL,
                             (uint8_t *)&ctrl9_xl, 1);
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of X-axis.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_z in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mark_axis_x_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);
  *val = ctrl9_xl.den_z;

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Y-axis.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_y in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mark_axis_y_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.den_y = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL9_XL,
                             (uint8_t *)&ctrl9_xl, 1);
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Y-axis.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_y in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mark_axis_y_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);
  *val = ctrl9_xl.den_y;

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Z-axis.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_x in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mark_axis_z_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);

  if (ret == 0)
  {
    ctrl9_xl.den_z = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_CTRL9_XL,
                             (uint8_t *)&ctrl9_xl, 1);
  }

  return ret;
}

/**
  * @brief  DEN value stored in LSB of Z-axis.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of den_x in reg CTRL9_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_den_mark_axis_z_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_CTRL9_XL,
                          (uint8_t *)&ctrl9_xl, 1);
  *val = ctrl9_xl.den_z;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_Pedometer
  * @brief      This section groups all the functions that manage pedometer.
  * @{
  *
  */

/**
  * @brief  Enable pedometer algorithm.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pedo_en in reg EMB_FUNC_EN_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_sens_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                            (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    emb_func_en_a.pedo_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                             (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable pedometer algorithm.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pedo_en in reg EMB_FUNC_EN_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_sens_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                            (uint8_t *)&emb_func_en_a, 1);
    *val = emb_func_en_a.pedo_en;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Interrupt status bit for step detection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of is_step_det in reg EMB_FUNC_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_step_detect_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val)
{
  lsm6dsrx_emb_func_status_t emb_func_status;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_STATUS,
                            (uint8_t *)&emb_func_status, 1);
    *val = emb_func_status.is_step_det;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Pedometer debounce configuration register (r/w).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_debounce_steps_set(const stmdev_ctx_t *ctx,
                                         uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_PEDO_DEB_STEPS_CONF,
                                  buff);

  return ret;
}

/**
  * @brief  Pedometer debounce configuration register (r/w).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_debounce_steps_get(const stmdev_ctx_t *ctx,
                                         uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_PEDO_DEB_STEPS_CONF,
                                 buff);

  return ret;
}

/**
  * @brief  Time period register for step detection on delta time (r/w).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_steps_period_set(const stmdev_ctx_t *ctx,
                                       uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_PEDO_SC_DELTAT_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_PEDO_SC_DELTAT_H,
                                    &buff[1]);
  }

  return ret;
}

/**
  * @brief  Time period register for step detection on delta time (r/w).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_steps_period_get(const stmdev_ctx_t *ctx,
                                       uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_PEDO_SC_DELTAT_L,
                                 &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_PEDO_SC_DELTAT_H,
                                   &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @brief  Set when user wants to generate interrupt on count overflow
  *         event/every step.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of carry_count_en in reg PEDO_CMD_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_int_mode_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_carry_count_en_t val)
{
  lsm6dsrx_pedo_cmd_reg_t pedo_cmd_reg;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_PEDO_CMD_REG,
                                 (uint8_t *)&pedo_cmd_reg);

  if (ret == 0)
  {
    pedo_cmd_reg.carry_count_en = (uint8_t)val;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_PEDO_CMD_REG,
                                    (uint8_t *)&pedo_cmd_reg);
  }

  return ret;
}

/**
  * @brief  Set when user wants to generate interrupt on count overflow
  *         event/every step.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of carry_count_en in reg PEDO_CMD_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_pedo_int_mode_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_carry_count_en_t *val)
{
  lsm6dsrx_pedo_cmd_reg_t pedo_cmd_reg;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_PEDO_CMD_REG,
                                 (uint8_t *)&pedo_cmd_reg);

  switch (pedo_cmd_reg.carry_count_en)
  {
    case LSM6DSRX_EVERY_STEP:
      *val = LSM6DSRX_EVERY_STEP;
      break;

    case LSM6DSRX_COUNT_OVERFLOW:
      *val = LSM6DSRX_COUNT_OVERFLOW;
      break;

    default:
      *val = LSM6DSRX_EVERY_STEP;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_significant_motion
  * @brief      This section groups all the functions that manage the
  *             significant motion detection.
  * @{
  *
  */

/**
  * @brief  Enable significant motion detection function.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sign_motion_en in reg EMB_FUNC_EN_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_motion_sens_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                            (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    emb_func_en_a.sign_motion_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                             (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable significant motion detection function.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sign_motion_en in reg EMB_FUNC_EN_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_motion_sens_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                            (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_en_a.sign_motion_en;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Interrupt status bit for significant motion detection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of is_sigmot in reg EMB_FUNC_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_motion_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                            uint8_t *val)
{
  lsm6dsrx_emb_func_status_t emb_func_status;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_STATUS,
                            (uint8_t *)&emb_func_status, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_status.is_sigmot;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_tilt_detection
  * @brief      This section groups all the functions that manage the tilt
  *             event detection.
  * @{
  *
  */

/**
  * @brief  Enable tilt calculation.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tilt_en in reg EMB_FUNC_EN_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tilt_sens_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                            (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    emb_func_en_a.tilt_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                             (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable tilt calculation.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tilt_en in reg EMB_FUNC_EN_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tilt_sens_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_A,
                            (uint8_t *)&emb_func_en_a, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_en_a.tilt_en;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Interrupt status bit for tilt detection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of is_tilt in reg EMB_FUNC_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_tilt_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                          uint8_t *val)
{
  lsm6dsrx_emb_func_status_t emb_func_status;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_STATUS,
                            (uint8_t *)&emb_func_status, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_status.is_tilt;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_ magnetometer_sensor
  * @brief      This section groups all the functions that manage additional
  *             magnetometer sensor.
  * @{
  *
  */

/**
  * @brief  External magnetometer sensitivity value register.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_sensitivity_set(const stmdev_ctx_t *ctx,
                                     uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SENSITIVITY_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SENSITIVITY_H,
                                    &buff[1]);
  }

  return ret;
}

/**
  * @brief  External magnetometer sensitivity value register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_sensitivity_get(const stmdev_ctx_t *ctx,
                                     uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SENSITIVITY_L,
                                 &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SENSITIVITY_H,
                                   &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) + buff[0];
  }

  return ret;
}

/**
  * @brief  Offset for hard-iron compensation register (r/w).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_offset_set(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;
  uint8_t i;

  buff[1] = (uint8_t)((uint16_t)val[0] / 256U);
  buff[0] = (uint8_t)((uint16_t)val[0] - (buff[1] * 256U));
  buff[3] = (uint8_t)((uint16_t)val[1] / 256U);
  buff[2] = (uint8_t)((uint16_t)val[1] - (buff[3] * 256U));
  buff[5] = (uint8_t)((uint16_t)val[2] / 256U);
  buff[4] = (uint8_t)((uint16_t)val[2] - (buff[5] * 256U));
  i = 0x00U;
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_OFFX_L, &buff[i]);

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_OFFX_H, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_OFFY_L, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_OFFY_H, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_OFFZ_L, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_OFFZ_H, &buff[i]);
  }

  return ret;
}

/**
  * @brief  Offset for hard-iron compensation register (r/w).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_offset_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;
  uint8_t i;

  i = 0x00U;
  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_OFFX_L, &buff[i]);

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_OFFX_H, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_OFFY_L, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_OFFY_H, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_OFFZ_L, &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_OFFZ_H, &buff[i]);

    val[0] = (int16_t)buff[1];
    val[0] = (val[0] * 256) + (int16_t)buff[0];
    val[1] = (int16_t)buff[3];
    val[1] = (val[1] * 256) + (int16_t)buff[2];
    val[2] = (int16_t)buff[5];
    val[2] = (val[2] * 256) + (int16_t)buff[4];
  }

  return ret;
}

/**
  * @brief  Soft-iron (3x3 symmetric) matrix correction register (r/w).
  *         The value is expressed as half-precision floating-point format:
  *         SEEEEEFFFFFFFFFF
  *         S: 1 sign bit;
  *         E: 5 exponent bits;
  *         F: 10 fraction bits).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_soft_iron_set(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[12];
  int32_t ret;
  uint8_t i;

  buff[1] = (uint8_t)(val[0] / 256U);
  buff[0] = (uint8_t)(val[0] - (buff[1] * 256U));
  buff[3] = (uint8_t)(val[1] / 256U);
  buff[2] = (uint8_t)(val[1] - (buff[3] * 256U));
  buff[5] = (uint8_t)(val[2] / 256U);
  buff[4] = (uint8_t)(val[2] - (buff[5] * 256U));
  buff[7] = (uint8_t)(val[3] / 256U);
  buff[6] = (uint8_t)(val[3] - (buff[1] * 256U));
  buff[9] = (uint8_t)(val[4] / 256U);
  buff[8] = (uint8_t)(val[4] - (buff[3] * 256U));
  buff[11] = (uint8_t)(val[5] / 256U);
  buff[10] = (uint8_t)(val[5] - (buff[5] * 256U));
  i = 0x00U;
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_XX_L,
                                  &buff[i]);

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_XX_H,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_XY_L,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_XY_H,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_XZ_L,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_XZ_H,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_YY_L,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_YY_H,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_YZ_L,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_YZ_H,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_ZZ_L,
                                    &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_SI_ZZ_H,
                                    &buff[i]);
  }

  return ret;
}

/**
  * @brief  Soft-iron (3x3 symmetric) matrix correction register (r/w).
  *         The value is expressed as half-precision floating-point format:
  *         SEEEEEFFFFFFFFFF
  *         S: 1 sign bit;
  *         E: 5 exponent bits;
  *         F: 10 fraction bits).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_soft_iron_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[12];
  int32_t ret;
  uint8_t i;

  i = 0x00U;
  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_XX_L,
                                 &buff[i]);

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_XX_H,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_XY_L,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_XY_H,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_XZ_L,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_XZ_H,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_YY_L,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_YY_H,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_YZ_L,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_YZ_H,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_ZZ_L,
                                   &buff[i]);
  }

  if (ret == 0)
  {
    i++;
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_SI_ZZ_H,
                                   &buff[i]);
  }

  val[0] = buff[1];
  val[0] = (val[0] * 256U) +  buff[0];
  val[1] = buff[3];
  val[1] = (val[1] * 256U) +  buff[2];
  val[2] = buff[5];
  val[2] = (val[2] * 256U) +  buff[4];
  val[3] = buff[7];
  val[3] = (val[3] * 256U) +  buff[6];
  val[4] = buff[9];
  val[4] = (val[4] * 256U) +  buff[8];
  val[5] = buff[11];
  val[6] = (val[5] * 256U) +  buff[10];

  return ret;
}

/**
  * @brief  Magnetometer Z-axis coordinates rotation (to be aligned to
  *         accelerometer/gyroscope axes orientation).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of mag_z_axis in reg MAG_CFG_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_z_orient_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_mag_z_axis_t val)
{
  lsm6dsrx_mag_cfg_a_t mag_cfg_a;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_CFG_A,
                                 (uint8_t *)&mag_cfg_a);

  if (ret == 0)
  {
    mag_cfg_a.mag_z_axis = (uint8_t)val;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_CFG_A,
                                    (uint8_t *)&mag_cfg_a);
  }

  return ret;
}

/**
  * @brief  Magnetometer Z-axis coordinates rotation (to be aligned to
  *         accelerometer/gyroscope axes orientation).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of mag_z_axis in reg MAG_CFG_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_z_orient_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_mag_z_axis_t *val)
{
  lsm6dsrx_mag_cfg_a_t mag_cfg_a;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_CFG_A,
                                 (uint8_t *)&mag_cfg_a);

  switch (mag_cfg_a.mag_z_axis)
  {
    case LSM6DSRX_Z_EQ_Y:
      *val = LSM6DSRX_Z_EQ_Y;
      break;

    case LSM6DSRX_Z_EQ_MIN_Y:
      *val = LSM6DSRX_Z_EQ_MIN_Y;
      break;

    case LSM6DSRX_Z_EQ_X:
      *val = LSM6DSRX_Z_EQ_X;
      break;

    case LSM6DSRX_Z_EQ_MIN_X:
      *val = LSM6DSRX_Z_EQ_MIN_X;
      break;

    case LSM6DSRX_Z_EQ_MIN_Z:
      *val = LSM6DSRX_Z_EQ_MIN_Z;
      break;

    case LSM6DSRX_Z_EQ_Z:
      *val = LSM6DSRX_Z_EQ_Z;
      break;

    default:
      *val = LSM6DSRX_Z_EQ_Y;
      break;
  }

  return ret;
}

/**
  * @brief  Magnetometer Y-axis coordinates rotation (to be aligned to
  *         accelerometer/gyroscope axes orientation).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of mag_y_axis in
  *                               reg MAG_CFG_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_y_orient_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_mag_y_axis_t val)
{
  lsm6dsrx_mag_cfg_a_t mag_cfg_a;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_CFG_A,
                                 (uint8_t *)&mag_cfg_a);

  if (ret == 0)
  {
    mag_cfg_a.mag_y_axis = (uint8_t)val;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_CFG_A,
                                    (uint8_t *)&mag_cfg_a);
  }

  return ret;
}

/**
  * @brief  Magnetometer Y-axis coordinates rotation (to be aligned to
  *         accelerometer/gyroscope axes orientation).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of mag_y_axis in reg MAG_CFG_A
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_y_orient_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_mag_y_axis_t *val)
{
  lsm6dsrx_mag_cfg_a_t mag_cfg_a;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_CFG_A,
                                 (uint8_t *)&mag_cfg_a);

  switch (mag_cfg_a.mag_y_axis)
  {
    case LSM6DSRX_Y_EQ_Y:
      *val = LSM6DSRX_Y_EQ_Y;
      break;

    case LSM6DSRX_Y_EQ_MIN_Y:
      *val = LSM6DSRX_Y_EQ_MIN_Y;
      break;

    case LSM6DSRX_Y_EQ_X:
      *val = LSM6DSRX_Y_EQ_X;
      break;

    case LSM6DSRX_Y_EQ_MIN_X:
      *val = LSM6DSRX_Y_EQ_MIN_X;
      break;

    case LSM6DSRX_Y_EQ_MIN_Z:
      *val = LSM6DSRX_Y_EQ_MIN_Z;
      break;

    case LSM6DSRX_Y_EQ_Z:
      *val = LSM6DSRX_Y_EQ_Z;
      break;

    default:
      *val = LSM6DSRX_Y_EQ_Y;
      break;
  }

  return ret;
}

/**
   * @brief  Magnetometer X-axis coordinates rotation (to be aligned to
  *         accelerometer/gyroscope axes orientation).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of mag_x_axis in reg MAG_CFG_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_x_orient_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_mag_x_axis_t val)
{
  lsm6dsrx_mag_cfg_b_t mag_cfg_b;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_CFG_B,
                                 (uint8_t *)&mag_cfg_b);

  if (ret == 0)
  {
    mag_cfg_b.mag_x_axis = (uint8_t)val;
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MAG_CFG_B,
                                    (uint8_t *)&mag_cfg_b);
  }

  return ret;
}

/**
  * @brief  Magnetometer X-axis coordinates rotation (to be aligned to
  *         accelerometer/gyroscope axes orientation).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of mag_x_axis in reg MAG_CFG_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_mag_x_orient_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_mag_x_axis_t *val)
{
  lsm6dsrx_mag_cfg_b_t mag_cfg_b;
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MAG_CFG_B,
                                 (uint8_t *)&mag_cfg_b);

  switch (mag_cfg_b.mag_x_axis)
  {
    case LSM6DSRX_X_EQ_Y:
      *val = LSM6DSRX_X_EQ_Y;
      break;

    case LSM6DSRX_X_EQ_MIN_Y:
      *val = LSM6DSRX_X_EQ_MIN_Y;
      break;

    case LSM6DSRX_X_EQ_X:
      *val = LSM6DSRX_X_EQ_X;
      break;

    case LSM6DSRX_X_EQ_MIN_X:
      *val = LSM6DSRX_X_EQ_MIN_X;
      break;

    case LSM6DSRX_X_EQ_MIN_Z:
      *val = LSM6DSRX_X_EQ_MIN_Z;
      break;

    case LSM6DSRX_X_EQ_Z:
      *val = LSM6DSRX_X_EQ_Z;
      break;

    default:
      *val = LSM6DSRX_X_EQ_Y;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_finite_state_machine
  * @brief      This section groups all the functions that manage the
  *             state_machine.
  * @{
  *
  */

/**
  * @brief  Interrupt status bit for FSM long counter timeout interrupt
  *         event.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of is_fsm_lc in reg EMB_FUNC_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_cnt_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                              uint8_t *val)
{
  lsm6dsrx_emb_func_status_t emb_func_status;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_STATUS,
                            (uint8_t *)&emb_func_status, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_status.is_fsm_lc;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Embedded final state machine functions mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fsm_en in reg EMB_FUNC_EN_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_emb_fsm_en_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  int32_t ret;

  lsm6dsrx_emb_func_en_b_t emb_func_en_b;
  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                            (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    emb_func_en_b.fsm_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Embedded final state machine functions mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fsm_en in reg EMB_FUNC_EN_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_emb_fsm_en_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;
  lsm6dsrx_emb_func_en_b_t emb_func_en_b;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                            (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_en_b.fsm_en;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Embedded final state machine functions mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers from FSM_ENABLE_A to FSM_ENABLE_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_enable_set(const stmdev_ctx_t *ctx,
                                lsm6dsrx_emb_fsm_enable_t *val)
{
  lsm6dsrx_emb_func_en_b_t emb_func_en_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_ENABLE_A,
                             (uint8_t *)&val->fsm_enable_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_ENABLE_B,
                             (uint8_t *)&val->fsm_enable_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                            (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    if ((val->fsm_enable_a.fsm1_en |
         val->fsm_enable_a.fsm2_en |
         val->fsm_enable_a.fsm3_en |
         val->fsm_enable_a.fsm4_en |
         val->fsm_enable_a.fsm5_en |
         val->fsm_enable_a.fsm6_en |
         val->fsm_enable_a.fsm7_en |
         val->fsm_enable_a.fsm8_en |
         val->fsm_enable_b.fsm9_en |
         val->fsm_enable_b.fsm10_en |
         val->fsm_enable_b.fsm11_en |
         val->fsm_enable_b.fsm12_en |
         val->fsm_enable_b.fsm13_en |
         val->fsm_enable_b.fsm14_en |
         val->fsm_enable_b.fsm15_en |
         val->fsm_enable_b.fsm16_en) != PROPERTY_DISABLE)
    {
      emb_func_en_b.fsm_en = PROPERTY_ENABLE;
    }

    else
    {
      emb_func_en_b.fsm_en = PROPERTY_DISABLE;
    }
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                             (uint8_t *)&emb_func_en_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Embedded final state machine functions mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers from FSM_ENABLE_A to FSM_ENABLE_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_enable_get(const stmdev_ctx_t *ctx,
                                lsm6dsrx_emb_fsm_enable_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_ENABLE_A,
                            (uint8_t *)&val->fsm_enable_a, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_ENABLE_B,
                            (uint8_t *)&val->fsm_enable_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter status register. Long counter value is an
  *         unsigned integer value (16-bit format).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_cnt_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_LONG_COUNTER_L, buff,
                             2);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter status register. Long counter value is an
  *         unsigned integer value (16-bit format).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_cnt_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_LONG_COUNTER_L, buff,
                            2);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Clear FSM long counter value.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fsm_lc_clr in reg
  *                FSM_LONG_COUNTER_CLEAR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_clr_set(const stmdev_ctx_t *ctx,
                              lsm6dsrx_fsm_lc_clr_t val)
{
  lsm6dsrx_fsm_long_counter_clear_t fsm_long_counter_clear;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_LONG_COUNTER_CLEAR,
                            (uint8_t *)&fsm_long_counter_clear, 1);
  }

  if (ret == 0)
  {
    fsm_long_counter_clear.fsm_lc_clr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_FSM_LONG_COUNTER_CLEAR,
                             (uint8_t *)&fsm_long_counter_clear, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Clear FSM long counter value.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fsm_lc_clr in reg  FSM_LONG_COUNTER_CLEAR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_clr_get(const stmdev_ctx_t *ctx,
                              lsm6dsrx_fsm_lc_clr_t *val)
{
  lsm6dsrx_fsm_long_counter_clear_t fsm_long_counter_clear;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_LONG_COUNTER_CLEAR,
                            (uint8_t *)&fsm_long_counter_clear, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (fsm_long_counter_clear.fsm_lc_clr)
  {
    case LSM6DSRX_LC_NORMAL:
      *val = LSM6DSRX_LC_NORMAL;
      break;

    case LSM6DSRX_LC_CLEAR:
      *val = LSM6DSRX_LC_CLEAR;
      break;

    case LSM6DSRX_LC_CLEAR_DONE:
      *val = LSM6DSRX_LC_CLEAR_DONE;
      break;

    default:
      *val = LSM6DSRX_LC_NORMAL;
      break;
  }

  return ret;
}

/**
  * @brief  FSM output registers.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers from FSM_OUTS1 to FSM_OUTS16
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_out_get(const stmdev_ctx_t *ctx,
                             lsm6dsrx_fsm_out_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_FSM_OUTS1,
                            (uint8_t *)&val->fsm_outs1, 16);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Finite State Machine ODR configuration.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fsm_odr in reg EMB_FUNC_ODR_CFG_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_data_rate_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_fsm_odr_t val)
{
  lsm6dsrx_emb_func_odr_cfg_b_t emb_func_odr_cfg_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_ODR_CFG_B,
                            (uint8_t *)&emb_func_odr_cfg_b, 1);
  }

  if (ret == 0)
  {
    emb_func_odr_cfg_b.not_used_01 = 3; /* set default values */
    emb_func_odr_cfg_b.not_used_02 = 1; /* set default values */
    emb_func_odr_cfg_b.fsm_odr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_ODR_CFG_B,
                             (uint8_t *)&emb_func_odr_cfg_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Finite State Machine ODR configuration.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fsm_odr in reg EMB_FUNC_ODR_CFG_B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_data_rate_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_fsm_odr_t *val)
{
  lsm6dsrx_emb_func_odr_cfg_b_t emb_func_odr_cfg_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_ODR_CFG_B,
                            (uint8_t *)&emb_func_odr_cfg_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (emb_func_odr_cfg_b.fsm_odr)
  {
    case LSM6DSRX_ODR_FSM_12Hz5:
      *val = LSM6DSRX_ODR_FSM_12Hz5;
      break;

    case LSM6DSRX_ODR_FSM_26Hz:
      *val = LSM6DSRX_ODR_FSM_26Hz;
      break;

    case LSM6DSRX_ODR_FSM_52Hz:
      *val = LSM6DSRX_ODR_FSM_52Hz;
      break;

    case LSM6DSRX_ODR_FSM_104Hz:
      *val = LSM6DSRX_ODR_FSM_104Hz;
      break;

    default:
      *val = LSM6DSRX_ODR_FSM_12Hz5;
      break;
  }

  return ret;
}

/**
  * @brief  FSM initialization request.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fsm_init in reg FSM_INIT
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_init_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_emb_func_init_b_t emb_func_init_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                            (uint8_t *)&emb_func_init_b, 1);
  }

  if (ret == 0)
  {
    emb_func_init_b.fsm_init = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                             (uint8_t *)&emb_func_init_b, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM initialization request.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fsm_init in reg FSM_INIT
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_init_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_emb_func_init_b_t emb_func_init_b;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                            (uint8_t *)&emb_func_init_b, 1);
  }

  if (ret == 0)
  {
    *val = emb_func_init_b.fsm_init;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter timeout register (r/w). The long counter
  *         timeout value is an unsigned integer value (16-bit format).
  *         When the long counter value reached this value, the FSM
  *         generates an interrupt.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_cnt_int_value_set(const stmdev_ctx_t *ctx,
                                        uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_FSM_LC_TIMEOUT_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_FSM_LC_TIMEOUT_H,
                                    &buff[1]);
  }

  return ret;
}

/**
  * @brief  FSM long counter timeout register (r/w). The long counter
  *         timeout value is an unsigned integer value (16-bit format).
  *         When the long counter value reached this value, the FSM generates
  *         an interrupt.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_long_cnt_int_value_get(const stmdev_ctx_t *ctx,
                                        uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_FSM_LC_TIMEOUT_L,
                                 &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_FSM_LC_TIMEOUT_H,
                                   &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @brief  FSM number of programs register.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_number_of_programs_set(const stmdev_ctx_t *ctx,
                                            uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_FSM_PROGRAMS, buff);

  return ret;
}

/**
  * @brief  FSM number of programs register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_number_of_programs_get(const stmdev_ctx_t *ctx,
                                            uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_FSM_PROGRAMS, buff);

  return ret;
}

/**
  * @brief  FSM start address register (r/w). First available address is
  *         0x033C.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_start_address_set(const stmdev_ctx_t *ctx,
                                       uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_FSM_START_ADD_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_FSM_START_ADD_H,
                                    &buff[1]);
  }

  return ret;
}

/**
  * @brief  FSM start address register (r/w). First available address
  *         is 0x033C.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_fsm_start_address_get(const stmdev_ctx_t *ctx,
                                       uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_FSM_START_ADD_L,
                                 &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_FSM_START_ADD_H,
                                   &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @addtogroup  Machine Learning Core
  * @brief   This section group all the functions concerning the
  *          usage of Machine Learning Core
  * @{
  *
  */

/**
  * @brief  Enable Machine Learning Core.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of mlc_en in
  *                  reg EMB_FUNC_EN_B and mlc_init
  *                  in EMB_FUNC_INIT_B
  *
  */
int32_t lsm6dsrx_mlc_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_emb_func_en_b_t reg;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                            (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.mlc_en = val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                             (uint8_t *)&reg, 1);
  }

  if ((val != PROPERTY_DISABLE) && (ret == 0))
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                            (uint8_t *)&reg, 1);

    if (ret == 0)
    {
      reg.mlc_en = val;
      ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_INIT_B,
                               (uint8_t *)&reg, 1);
    }
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Enable Machine Learning Core.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the values of mlc_en in
  *                  reg EMB_FUNC_EN_B
  *
  */
int32_t lsm6dsrx_mlc_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_emb_func_en_b_t reg;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_EN_B,
                            (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
    *val  = reg.mlc_en;
  }

  return ret;
}

/**
  * @brief  Machine Learning Core status register[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      register MLC_STATUS_MAINPAGE
  *
  */
int32_t lsm6dsrx_mlc_status_get(const stmdev_ctx_t *ctx,
                                lsm6dsrx_mlc_status_mainpage_t *val)
{
  return lsm6dsrx_read_reg(ctx, LSM6DSRX_MLC_STATUS_MAINPAGE,
                           (uint8_t *) val, 1);
}

/**
  * @brief  Machine Learning Core data rate selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      get the values of mlc_odr in
  *                  reg EMB_FUNC_ODR_CFG_C
  *
  */
int32_t lsm6dsrx_mlc_data_rate_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_mlc_odr_t val)
{
  lsm6dsrx_emb_func_odr_cfg_c_t reg;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_ODR_CFG_C,
                            (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    reg.mlc_odr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_EMB_FUNC_ODR_CFG_C,
                             (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Machine Learning Core data rate selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      change the values of mlc_odr in
  *                  reg EMB_FUNC_ODR_CFG_C
  *
  */
int32_t lsm6dsrx_mlc_data_rate_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_mlc_odr_t *val)
{
  lsm6dsrx_emb_func_odr_cfg_c_t reg;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_EMB_FUNC_ODR_CFG_C,
                            (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    switch (reg.mlc_odr)
    {
      case LSM6DSRX_ODR_PRGS_12Hz5:
        *val = LSM6DSRX_ODR_PRGS_12Hz5;
        break;

      case LSM6DSRX_ODR_PRGS_26Hz:
        *val = LSM6DSRX_ODR_PRGS_26Hz;
        break;

      case LSM6DSRX_ODR_PRGS_52Hz:
        *val = LSM6DSRX_ODR_PRGS_52Hz;
        break;

      case LSM6DSRX_ODR_PRGS_104Hz:
        *val = LSM6DSRX_ODR_PRGS_104Hz;
        break;

      default:
        *val = LSM6DSRX_ODR_PRGS_12Hz5;
        break;
    }

    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  prgsens_out: [get] Output value of all MLCx decision trees.
  *
  * @param  ctx_t *ctx: read / write interface definitions
  * @param  uint8_t * : buffer that stores data read
  *
  */
int32_t lsm6dsrx_mlc_out_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_EMBEDDED_FUNC_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MLC0_SRC, buff, 8);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  External magnetometer sensitivity value register for
  *         Machine Learning Core.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that contains data to write
  *
  */
int32_t lsm6dsrx_mlc_mag_sensitivity_set(const stmdev_ctx_t *ctx,
                                         uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MLC_MAG_SENSITIVITY_L,
                                  &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_write_byte(ctx, LSM6DSRX_MLC_MAG_SENSITIVITY_H,
                                    &buff[1]);
  }

  return ret;
}

/**
  * @brief  External magnetometer sensitivity value register for
  *         Machine Learning Core.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  buff     buffer that stores data read
  *
  */
int32_t lsm6dsrx_mlc_mag_sensitivity_get(const stmdev_ctx_t *ctx,
                                         uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MLC_MAG_SENSITIVITY_L,
                                 &buff[0]);

  if (ret == 0)
  {
    ret = lsm6dsrx_ln_pg_read_byte(ctx, LSM6DSRX_MLC_MAG_SENSITIVITY_H,
                                   &buff[1]);
    *val = buff[1];
    *val = (*val * 256U) +  buff[0];
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_Sensor_hub
  * @brief      This section groups all the functions that manage the
  *             sensor hub.
  * @{
  *
  */

/**
  * @brief  Sensor hub output registers.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure of registers from SENSOR_HUB_1 to SENSOR_HUB_18
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_read_data_raw_get(const stmdev_ctx_t *ctx, uint8_t *val,
                                      uint8_t len)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SENSOR_HUB_1,
                            (uint8_t *)val, len);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Number of external sensors to be read by the sensor hub.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of aux_sens_on in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_slave_connected_set(const stmdev_ctx_t *ctx,
                                        lsm6dsrx_aux_sens_on_t val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.aux_sens_on = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Number of external sensors to be read by the sensor hub.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of aux_sens_on in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_slave_connected_get(const stmdev_ctx_t *ctx,
                                        lsm6dsrx_aux_sens_on_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (master_config.aux_sens_on)
  {
    case LSM6DSRX_SLV_0:
      *val = LSM6DSRX_SLV_0;
      break;

    case LSM6DSRX_SLV_0_1:
      *val = LSM6DSRX_SLV_0_1;
      break;

    case LSM6DSRX_SLV_0_1_2:
      *val = LSM6DSRX_SLV_0_1_2;
      break;

    case LSM6DSRX_SLV_0_1_2_3:
      *val = LSM6DSRX_SLV_0_1_2_3;
      break;

    default:
      *val = LSM6DSRX_SLV_0;
      break;
  }

  return ret;
}

/**
  * @brief  Sensor hub I2C master enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of master_on in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_master_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.master_on = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub I2C master enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of master_on in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_master_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    *val = master_config.master_on;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Master I2C pull-up enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of shub_pu_en in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_pin_mode_set(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_shub_pu_en_t val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.shub_pu_en = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Master I2C pull-up enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of shub_pu_en in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_pin_mode_get(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_shub_pu_en_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (master_config.shub_pu_en)
  {
    case LSM6DSRX_EXT_PULL_UP:
      *val = LSM6DSRX_EXT_PULL_UP;
      break;

    case LSM6DSRX_INTERNAL_PULL_UP:
      *val = LSM6DSRX_INTERNAL_PULL_UP;
      break;

    default:
      *val = LSM6DSRX_EXT_PULL_UP;
      break;
  }

  return ret;
}

/**
  * @brief  I2C interface pass-through.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pass_through_mode in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_pass_through_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.pass_through_mode = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  I2C interface pass-through.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pass_through_mode in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_pass_through_get(const stmdev_ctx_t *ctx,
                                     uint8_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    *val = master_config.pass_through_mode;
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub trigger signal selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of start_config in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_syncro_mode_set(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_start_config_t val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.start_config = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub trigger signal selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of start_config in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_syncro_mode_get(const stmdev_ctx_t *ctx,
                                    lsm6dsrx_start_config_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (master_config.start_config)
  {
    case LSM6DSRX_EXT_ON_INT2_PIN:
      *val = LSM6DSRX_EXT_ON_INT2_PIN;
      break;

    case LSM6DSRX_XL_GY_DRDY:
      *val = LSM6DSRX_XL_GY_DRDY;
      break;

    default:
      *val = LSM6DSRX_EXT_ON_INT2_PIN;
      break;
  }

  return ret;
}

/**
  * @brief  Slave 0 write operation is performed only at the first sensor
  *         hub cycle.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of write_once in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_write_mode_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_write_once_t val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.write_once = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Slave 0 write operation is performed only at the first sensor
  *         hub cycle.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of write_once in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_write_mode_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_write_once_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (master_config.write_once)
  {
    case LSM6DSRX_EACH_SH_CYCLE:
      *val = LSM6DSRX_EACH_SH_CYCLE;
      break;

    case LSM6DSRX_ONLY_FIRST_CYCLE:
      *val = LSM6DSRX_ONLY_FIRST_CYCLE;
      break;

    default:
      *val = LSM6DSRX_EACH_SH_CYCLE;
      break;
  }

  return ret;
}

/**
  * @brief  Reset Master logic and output registers.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_reset_set(const stmdev_ctx_t *ctx)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.rst_master_regs = PROPERTY_ENABLE;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.rst_master_regs = PROPERTY_DISABLE;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                             (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Reset Master logic and output registers.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rst_master_regs in reg MASTER_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_reset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_MASTER_CONFIG,
                            (uint8_t *)&master_config, 1);
    *val = master_config.rst_master_regs;
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Rate at which the master communicates.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of shub_odr in reg SLV0_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_data_rate_set(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_shub_odr_t val)
{
  lsm6dsrx_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                            (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config.shub_odr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                             (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Rate at which the master communicates.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of shub_odr in reg slv1_CONFIG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_data_rate_get(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_shub_odr_t *val)
{
  lsm6dsrx_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                            (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  switch (slv0_config.shub_odr)
  {
    case LSM6DSRX_SH_ODR_104Hz:
      *val = LSM6DSRX_SH_ODR_104Hz;
      break;

    case LSM6DSRX_SH_ODR_52Hz:
      *val = LSM6DSRX_SH_ODR_52Hz;
      break;

    case LSM6DSRX_SH_ODR_26Hz:
      *val = LSM6DSRX_SH_ODR_26Hz;
      break;

    case LSM6DSRX_SH_ODR_13Hz:
      *val = LSM6DSRX_SH_ODR_13Hz;
      break;

    default:
      *val = LSM6DSRX_SH_ODR_104Hz;
      break;
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure that contain
  *                - uint8_t slv0_add;    8 bit i2c device address
  *                - uint8_t slv0_subadd; 8 bit register device address
  *                - uint8_t slv0_data;   8 bit data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_cfg_write(const stmdev_ctx_t *ctx,
                              lsm6dsrx_sh_cfg_write_t *val)
{
  lsm6dsrx_slv0_add_t slv0_add;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv0_add.slave0 = (uint8_t)(val->slv0_add >> 1);
    slv0_add.rw_0 = 0;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_ADD,
                             (uint8_t *) & (slv0_add), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_SUBADD,
                             (uint8_t *) & (val->slv0_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_DATAWRITE_SLV0,
                             (uint8_t *) & (val->slv0_data), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief Configure slave 0 for perform a write/read.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure that contain
  *                - uint8_t slv_add;    8 bit i2c device address
  *                - uint8_t slv_subadd; 8 bit register device address
  *                - uint8_t slv_len;    num of bit to read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_slv0_cfg_read(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sh_cfg_read_t *val)
{
  lsm6dsrx_slv0_config_t slv0_config;
  lsm6dsrx_slv0_add_t slv0_add;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv0_add.slave0 = (uint8_t) val->slv_add >> 1;
    slv0_add.rw_0 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_ADD,
                             (uint8_t *) & (slv0_add), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_SUBADD,
                             &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                            (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config.slave0_numop = val->slv_len;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV0_CONFIG,
                             (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write/read.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure that contain
  *                - uint8_t slv_add;    8 bit i2c device address
  *                - uint8_t slv_subadd; 8 bit register device address
  *                - uint8_t slv_len;    num of bit to read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_slv1_cfg_read(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sh_cfg_read_t *val)
{
  lsm6dsrx_slv1_config_t slv1_config;
  lsm6dsrx_slv1_add_t slv1_add;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv1_add.slave1_add = (uint8_t)(val->slv_add >> 1);
    slv1_add.r_1 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV1_ADD,
                             (uint8_t *)&slv1_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV1_SUBADD,
                             &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV1_CONFIG,
                            (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    slv1_config.slave1_numop = val->slv_len;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV1_CONFIG,
                             (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 2 for perform a write/read.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure that contain
  *                - uint8_t slv_add;    8 bit i2c device address
  *                - uint8_t slv_subadd; 8 bit register device address
  *                - uint8_t slv_len;    num of bit to read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_slv2_cfg_read(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sh_cfg_read_t *val)
{
  lsm6dsrx_slv2_config_t slv2_config;
  lsm6dsrx_slv2_add_t slv2_add;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv2_add.slave2_add = (uint8_t)(val->slv_add >> 1);
    slv2_add.r_2 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV2_ADD,
                             (uint8_t *)&slv2_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV2_SUBADD,
                             (uint8_t *) & (val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV2_CONFIG,
                            (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    slv2_config.slave2_numop = val->slv_len;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV2_CONFIG,
                             (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 3 for perform a write/read.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Structure that contain
  *                - uint8_t slv_add;    8 bit i2c device address
  *                - uint8_t slv_subadd; 8 bit register device address
  *                - uint8_t slv_len;    num of bit to read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_slv3_cfg_read(const stmdev_ctx_t *ctx,
                                  lsm6dsrx_sh_cfg_read_t *val)
{
  lsm6dsrx_slv3_config_t slv3_config;
  lsm6dsrx_slv3_add_t slv3_add;
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    slv3_add.slave3_add = (uint8_t)(val->slv_add >> 1);
    slv3_add.r_3 = 1;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV3_ADD,
                             (uint8_t *)&slv3_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV3_SUBADD,
                             &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_SLV3_CONFIG,
                            (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    slv3_config.slave3_numop = val->slv_len;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_SLV3_CONFIG,
                             (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub source register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Registers from STATUS_MASTER
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_sh_status_get(const stmdev_ctx_t *ctx,
                               lsm6dsrx_status_master_t *val)
{
  int32_t ret;

  ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_SENSOR_HUB_BANK);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_STATUS_MASTER,
                            (uint8_t *)val, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_mem_bank_set(ctx, LSM6DSRX_USER_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM6DSRX_Sensors for Smart Mobile Devices
  * @brief      This section groups all the functions that manage the
  *             Sensors for Smart Mobile Devices.
  * @{
  *
  */

/**
  * @brief  Sensor synchronization time frame resolution[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tph_h_sel in LSM6DSRX_S4S_TPH_L
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_tph_res_set(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_s4s_tph_res_t val)
{
  lsm6dsrx_s4s_tph_l_t s4s_tph_l;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_TPH_L, (uint8_t *)&s4s_tph_l, 1);

  if (ret == 0)
  {
    s4s_tph_l.tph_h_sel = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_S4S_TPH_L,
                             (uint8_t *)&s4s_tph_l, 1);
  }

  return ret;
}

/**
  * @brief  Sensor synchronization time frame resolution.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of tph_h_sel in LSM6DSRX_S4S_TPH_L
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_tph_res_get(const stmdev_ctx_t *ctx,
                                 lsm6dsrx_s4s_tph_res_t *val)
{
  lsm6dsrx_s4s_tph_l_t s4s_tph_l;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_TPH_L, (uint8_t *)&s4s_tph_l, 1);

  switch (s4s_tph_l.tph_h_sel)
  {
    case LSM6DSRX_S4S_TPH_7bit:
      *val = LSM6DSRX_S4S_TPH_7bit;
      break;

    case LSM6DSRX_S4S_TPH_15bit:
      *val = LSM6DSRX_S4S_TPH_15bit;
      break;

    default:
      *val = LSM6DSRX_S4S_TPH_7bit;
      break;
  }

  return ret;
}

/**
  * @brief  Sensor synchronization time frame.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tph_l in S4S_TPH_L and
  *                tph_h in S4S_TPH_H
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_tph_val_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  lsm6dsrx_s4s_tph_l_t s4s_tph_l;
  lsm6dsrx_s4s_tph_h_t s4s_tph_h;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_TPH_L, (uint8_t *)&s4s_tph_l, 1);

  if (ret == 0)
  {
    s4s_tph_l.tph_l = (uint8_t)(val & 0x007FU);
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_S4S_TPH_L,
                             (uint8_t *)&s4s_tph_l, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_TPH_H,
                            (uint8_t *)&s4s_tph_h, 1);
  }

  if (ret == 0)
  {
    s4s_tph_h.tph_h = (uint8_t)((val & 0x7F80U) >> 7);
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_S4S_TPH_H,
                             (uint8_t *)&s4s_tph_h, 1);
  }

  return ret;
}

/**
  * @brief  Sensor synchronization time frame.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of tph_l in S4S_TPH_L and tph_h in S4S_TPH_H
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_tph_val_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  lsm6dsrx_s4s_tph_l_t s4s_tph_l;
  lsm6dsrx_s4s_tph_h_t s4s_tph_h;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_TPH_L, (uint8_t *)&s4s_tph_l, 1);

  if (ret == 0)
  {
    ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_TPH_H,
                            (uint8_t *)&s4s_tph_h, 1);
  }

  *val = s4s_tph_h.tph_h;
  *val = *val << 7;
  *val += s4s_tph_l.tph_l;

  return ret;
}

/**
  * @brief  Sensor synchronization resolution ratio register.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rr in S4S_RR.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_res_ratio_set(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_s4s_res_ratio_t val)
{
  lsm6dsrx_s4s_rr_t s4s_rr;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_RR, (uint8_t *)&s4s_rr, 1);

  if (ret == 0)
  {
    s4s_rr.rr = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_S4S_RR, (uint8_t *)&s4s_rr, 1);
  }

  return ret;
}

/**
  * @brief   Sensor synchronization resolution ratio register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    get the values of rr in S4S_RR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_res_ratio_get(const stmdev_ctx_t *ctx,
                                   lsm6dsrx_s4s_res_ratio_t *val)
{
  lsm6dsrx_s4s_rr_t s4s_rr;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_RR, (uint8_t *)&s4s_rr, 1);

  switch (s4s_rr.rr)
  {
    case LSM6DSRX_S4S_DT_RES_11:
      *val = LSM6DSRX_S4S_DT_RES_11;
      break;

    case LSM6DSRX_S4S_DT_RES_12:
      *val = LSM6DSRX_S4S_DT_RES_12;
      break;

    case LSM6DSRX_S4S_DT_RES_13:
      *val = LSM6DSRX_S4S_DT_RES_13;
      break;

    case LSM6DSRX_S4S_DT_RES_14:
      *val = LSM6DSRX_S4S_DT_RES_14;
      break;

    default:
      *val = LSM6DSRX_S4S_DT_RES_11;
      break;
  }

  return ret;
}

/**
  * @brief  s4s master command.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of S4S_ST_CMD_CODE.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_command_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_s4s_st_cmd_code_t s4s_st_cmd_code;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_ST_CMD_CODE,
                          (uint8_t *)&s4s_st_cmd_code, 1);

  if (ret == 0)
  {
    s4s_st_cmd_code.s4s_st_cmd_code = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_S4S_ST_CMD_CODE,
                             (uint8_t *)&s4s_st_cmd_code, 1);
  }

  return ret;
}

/**
  * @brief  s4s master command.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    get the values of S4S_ST_CMD_CODE.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_command_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_s4s_st_cmd_code_t s4s_st_cmd_code;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_ST_CMD_CODE,
                          (uint8_t *)&s4s_st_cmd_code, 1);
  *val = s4s_st_cmd_code.s4s_st_cmd_code;

  return ret;
}

/**
  * @brief S4S DT register.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of S4S_DT_REG.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_dt_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsrx_s4s_dt_reg_t s4s_dt_reg;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_DT_REG,
                          (uint8_t *)&s4s_dt_reg, 1);

  if (ret == 0)
  {
    s4s_dt_reg.dt = (uint8_t)val;
    ret = lsm6dsrx_write_reg(ctx, LSM6DSRX_S4S_DT_REG,
                             (uint8_t *)&s4s_dt_reg, 1);
  }

  return ret;
}

/**
  * @brief  S4S DT register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    get the values of S4S_DT_REG.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsrx_s4s_dt_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsrx_s4s_dt_reg_t s4s_dt_reg;
  int32_t ret;

  ret = lsm6dsrx_read_reg(ctx, LSM6DSRX_S4S_DT_REG,
                          (uint8_t *)&s4s_dt_reg, 1);
  *val = s4s_dt_reg.dt;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @}
  *
  */

