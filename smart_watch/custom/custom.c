/*
 * Copyright 2026 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void analog_clock_count(int *hour, int *min, int *sec);
static void analog_clock_timer(lv_timer_t *timer);

/**********************
 *  STATIC VARIABLES
 **********************/

bool AclockisValid = false;
int AClock_Hour_Value = 3;
int AClock_Min_Value = 32;
int AClock_Sec_Value = 460;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a demo application
 */
void custom_init(gg_ui_t *ui)
{
    /* Add your codes here */
    lv_timer_create(analog_clock_timer, 100, NULL);
}

static void analog_clock_timer(lv_timer_t *timer)
{
    analog_clock_count(&AClock_Hour_Value, &AClock_Min_Value, &AClock_Sec_Value);
    if (AclockisValid)
    {
        lv_image_set_rotation(guider_ui.home_analog.img_Sec, AClock_Sec_Value * 6);
        lv_image_set_rotation(guider_ui.home_analog.img_Min, AClock_Min_Value * 60);
        lv_image_set_rotation(guider_ui.home_analog.img_Hour, AClock_Hour_Value * 300);
    }
}

void analog_clock_ready_cb(struct _lv_anim_t *a)
{
    AclockisValid = true;
}

static void analog_clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if (*sec == 600)
    {
        *sec = 0;
        (*min)++;
    }
    if (*min == 60)
    {
        *min = 0;
        if (*hour < 12)
        {
            (*hour)++;
        }
        else
        {
            (*hour)++;
            *hour = *hour % 12;
        }
    }
}
