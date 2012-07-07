#!/bin/sh

cd /home/neptune/Desktop/facebook/

echo -n "All Profile              : "; ls -1 know-of/ tried-downloading/ tried-expanding/ | wc -l
echo -n "Know of Profile          : "; ls -1 know-of/ | wc -l
echo -n "Tried Downloading Profile: "; ls -1 tried-downloading/ | wc -l
echo -n "Tried Expanding Profile  : "; ls -1 tried-expanding/ | wc -l
echo -n "Downloaded Public Page   : "; ls -1 */*/public_webpage.html | wc -l
echo -n "Downloaded Login Page    : "; ls -1 */*/login_webpage.html | wc -l
echo -n "Downloaded Friends Page  : "; ls -1 */*/all_friends_webpage.html | wc -l
echo -n "Megabytes of HD Space    : "; du -sm .

