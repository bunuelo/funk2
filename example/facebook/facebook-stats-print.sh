#!/bin/sh

cd /home/neptune/Desktop/facebook/profile/
echo -n "Know of Profile        : "; ls -1 | wc -l
echo -n "Downloaded Public Page : "; ls -1 */public_webpage.html | wc -l
echo -n "Downloaded Login Page  : "; ls -1 */login_webpage.html | wc -l
echo -n "Downloaded Friends Page: "; ls -1 */all_friends_webpage.html | wc -l
echo -n "Megabytes of HD Space  : "; du -sm .

