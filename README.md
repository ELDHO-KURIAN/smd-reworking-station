# smd-reworking-station
this project aims to create an open source hot air station(smd reworking station),this project is not perfect and anyone is free to use this amd make it better this machine works based on pid to maintain the temperature accurately

<image src="images/IMG_20200725_164713.jpg" width="500">
  
  # FEATURES
 ```
1. heats up within 5 seconds
2. automatically reach to set temperature when you pick up the handle
3. when you put back the handle in the holder machine goes to cooling mode and fan spins until the temperature goes below 50 degree celsius
4. if the fan speed is too low at very high temperature the heating element shuts dowm and gives warning on lcd
5. machine works based on pid hence it han hold the heating element at the set temperature
6. RGB led which change color according to mode
``` 
  # LIBRARYS REQUIRED
   ```
   you can download the librarys fron electronoobs
  https://www.electronoobs.com/eng_arduino_liq_crystal.php
  https://www.electronoobs.com/eng_arduino_max6675.php
   ```
  
# WIRING
```
this is the schematic :
```
 <image src="images/Schematic.png" width="500"> 

```
this is how you wire up the max6675 and i2clcd module :
```
 <image src="images/images (22)-01.jpeg" width="500"> 
  
  ```
this is how you should solder the components on the pcb :
```
<image src="images/img.png" width="500"> 
  
```
pcb looks something like this :
```  
<image src="images/IMG_20200724_165809.jpg" width="500"> 
  
  ```
after soldering it should look something like this :
```  

<image src="images/IMG_20200725_205303.jpg" width="500"> 
