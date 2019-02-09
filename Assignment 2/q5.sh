#!/bin/bash
# We capture the text from the pipe1.txt, and pipe the result to stream editor (sed)
# in the format 'substitute/old pattern/new pattern/all occurrences' and save the output
# in pipenew.txt

cat pipe1.txt | sed 's/peeps/pipes/g' > pipenew.txt