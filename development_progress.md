successful upload+good gds connection+fileuplink OK as of commit ee886b83da52ec5ff6e899db9bc8df2b413300f9
successful build for both mcuboot (app1) and f'-zephyr(app2) separately. both outputs GOOD hex, with f'-zephyr outputting a correct hex file for a mcuboot image (allegedly, i cant read hex well) as of commit 222d9afadfdb5903ca87d00dd4cd62deaf09a809

successful upload of mcuboot's hex file and a mcuboot-compatible image of f'-zephyr. mcuboot successfully boots into img0 and successful fprime-gds connection
NOTE: MAKE SURE TO CHECK "Skip Flash Erase Before Programming" OPTION IN IN CUBEPROGRAMMER!!


currently debugging:
littlefs does not mount properly. 

todo:
implement a component that uses svc::fileuplink and writes to slot1 partition and then mark it as pending upgrade and then reboot and see if it DOES reboot
