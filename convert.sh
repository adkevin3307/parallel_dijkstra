#!/bin/bash

if [[ $# != 1 ]]; then
    echo "Usage: ./convert.sh {gr file}"
    exit 1
fi

if [[ -f $1 ]]; then
    OUTPUT_FILE=${1/%gr/in}

    echo Convert $1 to $OUTPUT_FILE

    cat $1 | grep -P "^p" | awk '{print $3}' > $OUTPUT_FILE
    cat $1 | grep -P "^a" | awk '{printf("%d %d %d\n", $2 - 1, $3 - 1, $4)}' >> $OUTPUT_FILE

    echo Convert Success
else
    echo Error: $1 does not exist
fi
