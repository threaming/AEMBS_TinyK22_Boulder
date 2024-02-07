/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "portmacro.h"

/*!
 * \brief Sensor module initialization
 */
void Sensor_Deinit(void);

/*!
 * \brief Get temperature which is updated every second
 */
void GetTemp(float *temp);

/*!
 * \brief Get humidity which is updated every second
 */
void GetHum(float *hum);

/*!
 * \brief Sensor module de-initialization
 */
void Sensor_Init(void);

/*!
 * \brief Take i2c-Mutex
 */
BaseType_t sLock(void);

/*!
 * \brief Give i2c-Mutex
 */
BaseType_t sUnlock(void);

#endif /* SENSOR_H_ */
