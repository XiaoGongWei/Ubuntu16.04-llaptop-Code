#nvida
lsmod | grep nouveau
sudo gedit /etc/modprobe.d/blacklist.config

#grub
sudo update-grub
sudo gedit /etc/default/grub
＃　GRUB_DEFAULT=0　(0:Ubuntu, 4:Windows)
