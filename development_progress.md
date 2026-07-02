successful upload+good gds connection+fileuplink OK as of commit ee886b83da52ec5ff6e899db9bc8df2b413300f9
successful build for both mcuboot (app1) and f'-zephyr(app2) separately. both outputs GOOD hex, with f'-zephyr outputting a correct hex file for a mcuboot image (allegedly, i cant read hex well) as of commit 222d9afadfdb5903ca87d00dd4cd62deaf09a809

currently debuggingg:
why WONT CUBEPROGRAMMER flash CORRECTLY??? mcuboot's hex OK but f'-zzephyr refuses to be flashed at 0x8100 and when force-flash, wrong magic header bytes.


todo:
why wont it flash correctly??
then
implement a component that uses svc::fileuplink and writes to slot1 partition and then mark it as pending upgrade and then reboot and see if it DOES reboot
