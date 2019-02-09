#!/bin/bash

ls -lSrh *.txt | tr -s ' ' | cut -f9- -d' ' | xargs head -n1 -q  > output4.txt
