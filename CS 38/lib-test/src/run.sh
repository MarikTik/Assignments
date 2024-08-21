#!/bin/bash

# important to execute this script from src/ directory
javac -Xlint:deprecation -cp ../../lib/Draw.jar:. main.java
java -cp ../../lib/Draw.jar:. Main


