/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */



// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  This file contains implmentations for functions prototyped
 *  in pic24_util.h.
 */

#include "pic24_util.h"
#include "pic24_serial.h"
#include "pic24_clockfreq.h"
#include "pic24_ports.h"
#include "pic24_delay.h"
#include "pic24_unittest.h"
#include <stdio.h>        // To define NULL


#if !USE_HEARTBEAT && !defined(__DOXYGEN__)
// No heartbeat; instead, just define empty functions.
void configHeartbeat(void) {
}

void doHeartbeat(void) {
}

void toggleHeartbeat(void) {
}
#else

/** \name Heartbeat
 *  @{
 *  These routines provide heartbeat support by blinking a LED
 *  on a regular basis. See doHeartbeat() for more information.
 *
 */
/** The current heartbeat count. When this value reaches
 *  \ref u32_heartbeatMax, the heatbeat LED is toggled by
 *   doHeartbeat().
 * \see doHeartbeat
 */
uint32_t u32_heartbeatCount;
/** When u32_heartbeatCount reaches this maximum, the
 *  heatbeat LED is toggled by doHeartbeat().
 */
static uint32_t u32_heartbeatMax;


/** Configures a GPIO pin for use with the heartbeat and sets
 *  up the heartbeat counter.
 *  \see doHeartbeat
 */
void configHeartbeat(void) {
  CONFIG_HB_LED();
  /* long enough to see LED toggle. Incrementing the heartbeat
  takes several cycles - CYCLES_PER_MS used as the multiplier so that
  we are tied to FCY
  */
  u32_heartbeatMax = CYCLES_PER_MS * 10;
  u32_heartbeatCount = 0;
  HB_LED = 0; // Turn LED off to show we started running
  doHeartbeat();    // do Heartbeat   at least once
}

/** This heartbeat function should be called
 *  repeatedly in any sort of blocking wait loop. It will
 *  periodically toggle an LED after \ref u32_heartbeatMax increments.
 */
void doHeartbeat(void) {
  u32_heartbeatCount++;
  if (u32_heartbeatCount > u32_heartbeatMax) {
    toggleHeartbeat();
    u32_heartbeatCount = 0;
  }
}


/** A function which toggles the hearbeat LED.
    \see doHeartbeat
  */
void toggleHeartbeat(void) {
  HB_LED = !HB_LED;
}
/// @}
#endif

/** Persistent storage for an error message, typically
 *  set by \ref reportError and reported at reset by
 *  \ref printResetCause.
 */
static _PERSISTENT const char* sz_lastError;
/** Persistent storage for a timeout error, to be reported
 *  if a watchdog reset occurs.
 */
_PERSISTENT const char* sz_lastTimeoutError;

#ifndef __PIC24F__
/** Store a copy of the INTTREG register as a bitfield.
 *  This is not defined for the PIC24F, so work around
 *  with an \#ifdef. This is _PERSISTENT so that it
 *  survives the resets which occurs immeidately after
 *  the default interrupt handler \ref _DefaultInterrupt
 *  copies INTTREG to this variable.
 */
static _PERSISTENT INTTREGBITS INTTREGBITS_last;
/** Make the \ref INTTREGBITS_last also accessible as
 *  a word. This is like <code>uint16_t u16_INTTREGlast</code>
 *  except that INTTREGBITS_last and u16_INTTREGlast
 *  refer to the same data.
 */
#define u16_INTTREGlast BITS2WORD(INTTREGBITS_last)
#else
static uint16_t u16_INTTREGlast;
#endif

/** Provide a default interrupt handler which records what
 *  interrupt was not handled then resets the chip. Typically,
 *  a call to \ref printResetCause during chip startup will then
 *  print the error.
 */
void _ISR _DefaultInterrupt(void) {
#ifndef __PIC24F__
  // Record the interrupt vector and priority of the
  // unhandled interrupt.
  u16_INTTREGlast = INTTREG;
#else
  // Any non-zero value causes reportError to report
  // this. This register doesn't exist on the PIC24F.
  u16_INTTREGlast = 1;
#endif
  reportError("Unhandled interrupt, ");
}


/** Report a critical error by recording a message
 *  in \ref sz_lastError then resetting the chip,
 *  assuming hat \ref printResetCause will be called
 *  during chip initialization.
 *  \param sz_errorMessage Error message to report.
 *  \see REPORT_ERROR
 */
void reportError(const char* sz_errorMessage) {
  //ignore if a previous error has already been triggerred
  if (sz_lastError == NULL) {
    sz_lastError = sz_errorMessage;
    asm("reset");
  }
}

/** Reads a 24-bit program memory word at the given address.
 *  \param u32_address Address of program memory to read.
 *  \return The 24-bit program memory word at u32_address.
 *          The upper 8 bits are 0.
 */


/** Determines the device and revision of the PIC this program
 *  is executing on. This information is then output via the default
 *  UART. A warning message is issued if this program was not compiled
 *  for the chip it is running on.
 */


/** Reports the oscillator currently in use to the default
 *  serial port.
 */


/** Determines and prints the cause of a CPU reset. This should
 *  be called when the chip first starts up. For an example, see
 *  the \ref configBasic function.
 */


/** Perform basic chip configuration:
 *  - Configure the heartbeat
 *  - Configure the clock
 *  - Configure UART1
 *  - Determine and print the cause of reset
 *  - Print a hello message.
 *
 *  \param sz_helloMsg Hello message to print.
 */
void configBasic(const char* sz_helloMsg) {
  //configHeartbeat();
  configClock();
  //configDefaultUART(DEFAULT_BAUDRATE);
  //printResetCause();
  //outString(sz_helloMsg);
}


#ifndef _NOFLOAT
/** Round a floating-point number to the nearest integer.
 *  \param f_x Floating-point value to round
 *  \return The nearest uint32_t to f_x.
 */
uint32_t roundFloatToUint32(float f_x) {
  uint32_t u32_y;

  u32_y = f_x;
  if ((f_x - u32_y) < 0.5) return u32_y;
  else return u32_y+1;
}

/** Round a floating-point number to the nearest integer.
 *  \param f_x Floating-point value to round
 *  \return The nearest uint16_t to f_x.
 */
uint16_t roundFloatToUint16(float f_x) {
  uint16_t u16_y;

  u16_y = f_x;
  if ((f_x - u16_y) < 0.5) return u16_y;
  else return u16_y+1;
}

/**  Choose UART baud rate, based on u32_fct.
  *  NOTE: Be careful about using BRGH=1 - this uses only four clock
  *  periods to sample each bit and can be very intolerant of
  *  baud rate % error - you may see framing errors. BRGH is selected
  *  via the DEFAULT_BRGH1 define above.
  */
uint16_t compute_brg(uint32_t u32_fcy, uint16_t u16_brgh, uint32_t u32_baudrate) {
  float f_brg;

  // Make sure u16_brgh is valid (1 or 0)
  ASSERT(u16_brgh <= 1);
  if (u16_brgh == 0) {
    f_brg = (((float) u32_fcy)/((float) u32_baudrate)/16.0) - 1.0;
  } else {
    f_brg = (((float) u32_fcy)/((float) u32_baudrate)/4.0) - 1.0;
  }
  ASSERT(f_brg < 65535.5);
  return roundFloatToUint16(f_brg);
}

#else // #ifndef _NOFLOAT, so _NOFLOAT is defined.

uint16_t compute_brg(uint32_t u32_fcy, uint16_t u16_brgh, uint32_t u32_baudrate) {
  uint32_t u32_brg;

  // Make sure u16_brgh is valid (1 or 0)
  ASSERT(u16_brgh <= 1);
  u32_brg = u32_fcy/u32_baudrate;
  if (u16_brgh == 0) {
    if ((u32_brg & 0x0FL) >= 8) {
      u32_brg = u32_brg/16;
    } else {
      u32_brg = u32_brg/16 - 1;
    }
  } else {
    if ((u32_brg & 0x03L) >= 2) {
      u32_brg = u32_brg/4;
    } else {
      u32_brg = u32_brg/4 - 1;
    }
  }
  ASSERT(u32_brg < 65536);
  return u32_brg;
}

#endif
