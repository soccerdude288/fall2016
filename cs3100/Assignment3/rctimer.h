/* By Rolando Collantes
 * 
 * This timer is dedicated to CS3100 in Fall 2016.
 * Use it for whatever.  I place this in the public domain (if that matters)
 * 
 * How to use (works on Linux and Mac (at least macOS Sierra)):
 * 
 * Save this source to rctimer.h
 * Include it where/before you want to time code. #include "rctimer.h"
 * Call start_timer() before the code you want to time
 * Call end_timer() after the code ends
 * Call get_elapsed_time(). It returns a (static) const char* containing
 *     only the readable time, which can be printed like so:
 *     printf("Elapsed time: %s\n", get_elapsed_time());
 * Example output:  
 * 
 * Timer started. Sleeping for 5s
 * Elapsed time: 05.000141458s
 * 
 * Timer started. Sleeping for 62s
 * Elapsed time: 01m01.999477815s
 * 
 * As you can see, the granularity is down to the nanosecond.
 * 
 */

#ifndef RCTIMER_H //ifdef guards so that it's not included more than once
#define RCTIMER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h> // perror(), snprintf()
#include <stdlib.h> // exit(), EXIT_FAILURE
#include <time.h> // struct timespec, clock_gettime, CLOCK_MONOTINIC_RAW

typedef struct {
	struct timespec start;
	struct timespec end;
} __Timer;

__Timer _t;

void start_timer(){
	if(clock_gettime(CLOCK_MONOTONIC_RAW, &_t.start) != 0){
		perror("start_timer -> clock_gettime");
		exit(EXIT_FAILURE);
	}
}

void end_timer(){
	if(clock_gettime(CLOCK_MONOTONIC_RAW, &_t.end) != 0){
		perror("end_timer -> clock_gettime");
		exit(EXIT_FAILURE);
	}
}

// Returns a const char* string.  Don't call free() on it.
const char* get_elapsed_time(){
	static char str[64]; // Will hold string of timer.
	struct timespec diff;
	
	diff.tv_sec = (_t.end.tv_sec - 1) - _t.start.tv_sec; // Borrow 1 second
	diff.tv_nsec = (1000000000 + _t.end.tv_nsec) - _t.start.tv_nsec; // 1s = 1Bns
	diff.tv_sec += diff.tv_nsec / 1000000000; // Give back if it wasn't used
	diff.tv_nsec %= 1000000000;
	
	// Example: 01m05.003003003s
	if(diff.tv_sec > (60*60)){ // >= 1 hour
		snprintf(str, sizeof(str), "%.2ldh%.2ldm%.2ld.%.9lds", 
			(long)(diff.tv_sec/(60*60))/*h*/,
			(long)(diff.tv_sec / 60) /*m*/,
			(long)(diff.tv_sec % 60), diff.tv_nsec);
	} else if(diff.tv_sec > 60) { // >= 1 minute
		snprintf(str, sizeof(str), "%.2ldm%.2ld.%.9lds",
			(long)(diff.tv_sec / 60) /*m*/,
			(long)(diff.tv_sec % 60), diff.tv_nsec);
	} else {
		snprintf(str, sizeof(str), "%.2ld.%.9lds",
			(long)(diff.tv_sec % 60), diff.tv_nsec);
	}
	return str;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // RCTIMER_H