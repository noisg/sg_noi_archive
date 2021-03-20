#!/bin/bash

problem=mushrooms
grader_name=stub
stack_size=960M
heap_size=1024M

java -Xmx1024M -Xss960M -cp Archaeologist.jar stub
