successful upload+good gds connection+fileuplink OK as of commit ee886b83da52ec5ff6e899db9bc8df2b413300f9


todo:
flash mcuboot + f'-zephyr app and test 
then
implement a component that uses svc::fileuplink and writes to slot1 partition and then mark it as pending upgrade and then reboot and see if it DOES reboot
