/*
 *  Scheme.cpp
 *  
 *
 *  Created by todd ingalls on 9/1/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scheme.h"


SchemeThread::SchemeThread(String name) : Thread(name)
{
}

SchemeThread::~SchemeThread()
{
}

void SchemeThread::run()
{
	int res;
	C_word k;
	C_word r;
	char buffer[8192];
	
    res = CHICKEN_initialize(0, 0, 0, CHICKEN_default_toplevel);
    if(res == 1)
        printf("chicken initialized\n");	
	
    k = CHICKEN_run(CHICKEN_default_toplevel);
	
    k = CHICKEN_continue(k);
	
	
	while(!threadShouldExit()	) {
		
		wait(-1);
		
		CHICKEN_eval_string( (char*)EvalString, &r);
		
		CHICKEN_eval_to_string(r, buffer, 8192);
		printf("result = %s\n", buffer);
		bzero(buffer, 8192);
	}	
	
}

