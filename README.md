# Microprocessor's Systems II Project
Final project to Microprocessor's System II course at Electronics faculty. Winter semester, year 2018/2019.    
Project gets data from acceleremeter and gyroscope, sends it to computer and plots current state of them.   

## Used modules
Project uses FRDM-KL46Z board and MPU-6500 module. 

## Setting up
### Hardware
1. Connect MPU-6500 module to KL46Z board.
Pins of FRDM-KL46Z board and MPU-6500 module should be connected in the following way:    
    * VCC -> 3P3   
    * GND -> GND   
    * SDA -> D7   
    * SCL -> D6
2. Connect KL46Z board to your computer with USB-micro USB cabel.
Plug USB ending to computer and micro USB ending to OpenSDA socket in KL46Z board.

### Software
First of all, we need to program FRDM-KL46Z board. For that, you can use Keil software.
Next, run program from folder computer_program on your computer to see plots. You may want to press RESET on KL46Z board to make sure that data from accelerometer and gyroscope are sent to computer.

## Status
Currently not developed. Works on this project has finished.

## License
Feel free to use, but take under consideration, that it is made by students.



