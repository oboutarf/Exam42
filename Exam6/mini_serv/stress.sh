#!/bin/bash

send=10
port=9000
for ((i = 0; i < send; i++)); do
  echo "spam out server" | nc -q 0 localhost $port &
done; wait
