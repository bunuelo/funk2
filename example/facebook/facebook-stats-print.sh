#!/bin/sh

echo -n "Know of Profile        : "; ls -1 /home/neptune/Desktop/facebook/profile/ | wc -l
echo -n "Downloaded Public Page : "; ls -1 /home/neptune/Desktop/facebook/profile/*/public_webpage.html | wc -l
echo -n "Downloaded Login Page  : "; ls -1 /home/neptune/Desktop/facebook/profile/*/login_webpage.html | wc -l
echo -n "Downloaded Friends Page: "; ls -1 /home/neptune/Desktop/facebook/profile/*/all_friends_webpage.html | wc -l
echo -n "Megabytes of HD Space  : "; du -sm /home/neptune/Desktop/facebook/profile/

