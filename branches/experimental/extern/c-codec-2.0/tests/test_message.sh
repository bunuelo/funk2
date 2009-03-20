#!/bin/bash

# *  $Revision: 322 $
# *  $Date: 2008-10-08 10:56:23 -0600 (Wed, 08 Oct 2008) $
# *  $Author: brian@tannerpages.com $
# *  $HeadURL: http://rl-glue-ext.googlecode.com/svn/trunk/projects/codecs/C/tests/test_message.sh $

killall rl_glue 2>/dev/null
killall test_message_agent 2>/dev/null
killall test_message_environment 2>/dev/null
killall test_message_experiment 2>/dev/null
sleep 1
rl_glue &
sleep 1
./test_message_agent &
sleep 1
./test_message_environment &
sleep 1
./test_message_experiment

test_outcome=$?
exit $test_outcome