# CS5250_task2

Introduction
============
This code is for the completion of Task 2 of Assignment of module CS5250 Advanced Operating Systems from NUS School of Computing Academic Year 2017/2017 Semester 2.

Functionality
-------------
The task is to write a simple one character device driver.
The driver is initialised with the 'X' character.
Only single characters can be written to the driver.
If more than one character is written, it will only write the first character and return -ENOSPC error.

Instructions
------------
Make  
	Makefile is provided. Call $ make.

Install  
	$ sudo insmod onebyte.ko

Uninstall  
	$ sudo rmmod onebyte.ko

Running  
	$ mknod /dev/onebyte 61 0  
	$ cat /dev/onebyte  
	$ printf a>/dev/onebyte  
	$ printf abc>/dev/onebyte  


~~ joshsiao 2018 ~~

