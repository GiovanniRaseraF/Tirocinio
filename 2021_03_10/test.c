#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/rpmsg.h>
#include <sys/ioctl.h>
#include <unistd.h>
 
int main(void)
{
	char data_buf [] = {'a', 'b', 'c', 'd', 'e', '\0'};
	struct rpmsg_endpoint_info ept_info = {"rpmsg-openamp-demo-channel", 0x2, 0x1};
	int fd = open("/dev/rpmsg_ctrl0", O_RDWR);
	/* create endpoint interface */
	ioctl(fd, RPMSG_CREATE_EPT_IOCTL, &ept_info);  // /dev/rpmsg0 is created
	/* create endpoint */
	int fd_ept = open("/dev/rpmsg0", O_RDWR); // backend creates endpoint
	/* receive data from remote device */
	read(fd_ept, &data_buf, sizeof(data_buf));
	/* send data to remote device */
	write(fd_ept, &data_buf, sizeof(data_buf));
	/* destroy endpoint */
	ioctl(fd_ept, RPMSG_DESTROY_EPT_IOCTL);
	close(fd_ept);
	close(fd);
}