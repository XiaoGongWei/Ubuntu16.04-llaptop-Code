softnames='cuda'
sudo dpkg -l | grep $softnames | awk '{print $2}' | sudo xargs dpkg -P
