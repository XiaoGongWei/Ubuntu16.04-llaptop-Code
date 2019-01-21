*/1 * * * * /home/david/Documents/MyShell/notify_items.sh >>/home/david/Documents/notify_minutes.txt

*/1 * * * * date >>/home/david/Documents/notify_minutes.txt
*/1 * * * * notify-send ["该休息一下啦"] "喝水！伸懒腰！动一动！"

