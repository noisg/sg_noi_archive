#!/bin/sh
# echo "Creating named pipe" $$
rm -f $$
mkfifo $$
# echo "Executing programs"
$1 < $$ | $2 $3 > $$
rm -f $$
