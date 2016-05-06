/**
 Copyright (c) 2015 MidAir Technology, LLC.  All rights reserved.
 Copyright (c) 2016 Bryan J. Rentoul (aka Gruvin).  All rights reserved.
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

/* Includes -----------------------------------------------------------------*/
#include "rtc_timer.h"

/* Private typedef ----------------------------------------------------------*/

/* Private define -----------------------------------------------------------*/
#define MAX_RTC_TIMERS (APP_TIMER_MAX_TIMERS-1)

/* Private macro ------------------------------------------------------------*/

/* Private variables --------------------------------------------------------*/

/* Extern variables ---------------------------------------------------------*/

/* Private function prototypes ----------------------------------------------*/

RTCTimer::RTCTimer(uint32_t interval, app_timer_timeout_handler_t handler_fn)
{
  this->_init();
  this->handlerFunc = handler_fn;
  this->timerInterval = interval;
  this->timerMode = APP_TIMER_MODE_SINGLE_SHOT;
};

RTCTimer::RTCTimer(uint32_t interval, app_timer_timeout_handler_t handler_fn, bool one_shot = true)
{
  this->_init();
  this->handlerFunc = handler_fn;
  this->timerInterval = interval;
  this->timerMode = (one_shot) ? APP_TIMER_MODE_SINGLE_SHOT : APP_TIMER_MODE_REPEATED;
};

RTCTimer::~RTCTimer()
{
  if (this->timerID) app_timer_stop(this->timerID);
}

void RTCTimer::_init() 
{ 
  this->handlerFunc = (app_timer_timeout_handler_t)0x00; 
  this->handlerContext = (void *)0x00;
  this->timerMode = APP_TIMER_MODE_REPEATED;
  this->timerID = 0;
};

void RTCTimer::start()
{
  uint32_t err_code;
  if (!this->timerID)  // don't repeat this call if we already have a valid timerID
  {
    err_code = app_timer_create( &this->timerID, this->timerMode, this->handlerFunc);
    APP_ERROR_CHECK(err_code);    
  }

  if (this->timerID) 
  {
    err_code = app_timer_start(this->timerID, this->timerInterval, this->handlerContext);
    APP_ERROR_CHECK(err_code);    
  }
};

void RTCTimer::stop()
{
  app_timer_stop(this->timerID);
};

void RTCTimer::changePeriod()
{
};

void RTCTimer::dispose()
{
};

bool RTCTimer::isActive()
{
  return false;
};

