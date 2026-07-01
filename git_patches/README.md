besides applying the git patches in this repo, make sure to activate these projects 

run: west config manifest.project-filter "+cmsis, +cmsis_6, +hal_stm32, +mcuboot"
then run: west update 
