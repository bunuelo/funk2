#!/bin/sh

cd /home/neptune/Desktop/facebook/

echo -n "All Profile              : "; find know-of/ tried-downloading/ tried-expanding/ -maxdepth 1 | wc -l
echo -n "Know of Profile          : "; find know-of/ -maxdepth 1 | wc -l
echo -n "Tried Downloading Profile: "; find tried-downloading/ -maxdepth 1 | wc -l
echo -n "Tried Expanding Profile  : "; find tried-expanding/ -maxdepth 1 | wc -l
echo -n "Downloaded Public Page   : "; find . | grep /public_webpage.html | wc -l
echo -n "Downloaded Login Page    : "; find . | grep /login_webpage.html | wc -l
echo -n "Downloaded Friends Page  : "; find . | grep /all_friends_webpage.html | wc -l
echo -n "Megabytes of HD Space    : "; du -sm .

