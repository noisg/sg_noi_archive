#!/bin/bash

rm -f Archaeologist.jar *.class
javac stub.java Archaeologist.java -Xlint:all
jar cfe Archaeologist.jar stub *.class