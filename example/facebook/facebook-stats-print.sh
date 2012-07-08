#!/bin/sh

cd /home/neptune/Desktop/facebook/

echo -n "All Profile              : "; find -maxdepth 1 know-of/ tried-downloading/ tried-expanding/ | wc -l
echo -n "Know of Profile          : "; find -maxdepth 1 know-of/ | wc -l
echo -n "Tried Downloading Profile: "; find -maxdepth 1 tried-downloading/ | wc -l
echo -n "Tried Expanding Profile  : "; find -maxdepth 1 tried-expanding/ | wc -l
echo -n "Downloaded Public Page   : "; find . | grep /public_webpage.html | wc -l
echo -n "Downloaded Login Page    : "; find . | grep /login_webpage.html | wc -l
echo -n "Downloaded Friends Page  : "; find . | grep /all_friends_webpage.html | wc -l
echo -n "Megabytes of HD Space    : "; du -sm .

