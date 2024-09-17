#!/bin/bash

base_directory=$1  # The base directory where to start looking for packages, e.g., "week2"
target=$2          # The main class name in that .java file, e.g., "Program"

# Compile the Java program
javac -Xlint:-deprecation -d ./build/ -cp "lib/draw.jar:." ""$base_directory""/src/*".java"
# Run the Java program
java -cp "./build:./lib/draw.jar" "$target"
 