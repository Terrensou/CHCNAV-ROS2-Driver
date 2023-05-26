# CHCNAV-ROS2-Driver
基于ROS2 Humble的华测导航简单读取驱动

发布话题“？chcnav_imugnss/GPCHC”

### Install
```shell
sudo apt-get install ros-humble-serial-driver
```


读取设备失败，可能原因为未给当前用户授权设备访问权限。
```shell
sudo usermod -aG dialout username
```
重启即可

可能是计算机串口BIOS设置波特率

### RUN
```shell
source install/setup.bash
ros2 run chcnav_driver cgi610_node
```

#### 已知问题
msg中数据类型为float32存在不精确