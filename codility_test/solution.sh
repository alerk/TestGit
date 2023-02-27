#!/usr/bin/env bash
LOG_FILE="$1"

# Read the newly append line in the log file
tail -n 1 -f $LOG_FILE | while read line
do
  # Check if the line contains the 2 words HTTP and 500
  # i.e
  # 172.19.0.100 - - [20/Feb/2020:12:00:00 +0000] "GET /file/one HTTP/1.1" 500 1024 "-" "Mozilla/5.0 (compatible)" "172.19.0.1"
  # extract HTTP 500 on /file/one
  if [[ "$new_line" == *"HTTP"* ]] && [[ "$new_line" == *"500"* ]]; then
    path=$(echo $tmp | sed -n 's/.*[GET|POST|PUT] \(.*\) HTTP.*/\1/p')
    mail "alert@project.com" "HTTP 500 on $path"
  fi
done