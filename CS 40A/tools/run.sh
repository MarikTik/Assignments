if [ -z "$1" ]; then
    echo "Usage: ./run.sh <file>"
    exit 1
fi

java -jar ~/Desktop/mars/mars.jar nc "$1"