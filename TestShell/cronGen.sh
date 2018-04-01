# m h  dom mon dow   command
#crontab -e
*/1 * * * *  /home/david/Documents/MyGitHub/TestShell/dateTime.sh >>/home/david/Documents/MyGitHub/TestShell/crontab_test.txt
* * * * * sleep 3; /home/david/Documents/MyGitHub/TestShell/dateTime.sh >>/home/david/Documents/MyGitHub/TestShell/crontab_test_1s.txt
* * * * * sleep 10; /home/david/Documents/MyGitHub/TestShell/dateTime.sh >>/home/david/Documents/MyGitHub/TestShell/crontab_test_10s.txt
* * * * * sleep 8; /home/david/Documents/MyGitHub/TestShell/dateTime.sh >>/home/david/Documents/MyGitHub/TestShell/crontab_test_0_1s.txt
