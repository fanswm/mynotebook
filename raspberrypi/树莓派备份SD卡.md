sudo dd if=/dev/sdc | gzip>/home/fanwm/Rpi_centos_backup.img.gz
$sudo fdisk /dev/sdc
$p
删除分区;
格式化;
恢复:
$sudo gzip -dc /home/fanswm/Rpi_centos_backup.img.gz |sudo dd of=/dev/sdc
