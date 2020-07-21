#!/bin/bash
# Archiving script for DEncryptor

echo "Archiving files in $1"

for i in ls -al $1
do
	if [file i -eq "ASCII text"]
	then
		i >> catalogue
	fi
done

ls -al $1

echo Done
