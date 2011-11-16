//  iphone_detect
//  Created by Aidan Steele on 16/11/11.

#include <stdio.h>
#include <string.h>
#include "libusb.h"

static char *device_names[] = {"iPhone", "iPad", "iPod"};
static int apple_vendor_id = 0x05AC;

int main (int argc, const char * argv[])
{
  if (libusb_init(NULL)) goto error;
  
  libusb_device **devs = NULL, *dev = NULL;
  int i = 0;
  int j = 0;

  if (libusb_get_device_list(NULL, &devs) == LIBUSB_ERROR_NO_MEM) goto error;
  while ((dev = devs[i++]))
  {
    struct libusb_device_descriptor descriptor;
    libusb_get_device_descriptor(dev, &descriptor);
    
    if (descriptor.idVendor == apple_vendor_id)
    {
      libusb_device_handle *handle = NULL;
      if (libusb_open(dev, &handle)) goto error;
      
      char device[40];
      libusb_get_string_descriptor_ascii(handle, descriptor.iProduct, (unsigned char *)device, sizeof(device));
      for (j = 0; j < sizeof(device_names)/sizeof(*device_names); j++)
      {
        if (strcmp(device, device_names[j]) == 0)
        {
          char serial[40];
          libusb_get_string_descriptor_ascii(handle, descriptor.iSerialNumber, (unsigned char *)serial, sizeof(serial));
          printf("%s\n", serial);
        }
      }
      
      libusb_close(handle);
    }
  }
  
  libusb_free_device_list(devs, 1);
  libusb_exit(NULL);
  return 0;
  
error:
  return -1;
}
