#!/bin/sh

cd /home/neptune/Desktop/facebook/

echo -n "All Profile              : "; ls -1 know_of/ tried_downloading/ tried_expanding/ | wc -l
echo -n "Know of Profile          : "; ls -1 know_of/ | wc -l
echo -n "Tried Downloading Profile: "; ls -1 tried_downloading/ | wc -l
echo -n "Tried Expanding Profile  : "; ls -1 tried_expanding/ | wc -l
echo -n "Downloaded Public Page   : "; ls -1 */*/public_webpage.html | wc -l
echo -n "Downloaded Login Page    : "; ls -1 */*/login_webpage.html | wc -l
echo -n "Downloaded Friends Page  : "; ls -1 */*/all_friends_webpage.html | wc -l
echo -n "Megabytes of HD Space    : "; du -sm .

