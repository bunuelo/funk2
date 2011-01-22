#!/bin/zsh -f

(   (   (cat README.template) &&
	(echo "")                                                                                 &&
	(echo "Code Mass")                                                                        &&
	(echo "")                                                                                 &&
	(echo "--------------------------------------------------------------------------------") &&
	(echo "")                                                                                 &&
	(./generate_statistics.sh)                                                                &&
	(echo "")                                                                                 &&
	(echo "--------------------------------------------------------------------------------") &&
	(echo "")                                                                                 &&
	(echo -n "Last Generated: " && date)                                                         ) | tee README) | less

