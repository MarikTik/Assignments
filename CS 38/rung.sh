#!/bin/bash

base_directory=$1  # The base directory where to start looking for packages, e.g., "week2"
file=$2            # The .java file to compile, e.g., "week2/src/lecture1.java"
target=$3          # The main class name in that .java file, e.g., "Program"

# Compile the Java program
javac -Xlint:deprecation -cp "lib/Draw.jar:." "$base_directory"/src/"$file"

# Run the Java program
# Assuming 'src' is the package and 'Program' is the main class
java -cp "lib/Draw.jar:$base_directory/src" "$target"