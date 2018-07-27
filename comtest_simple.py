import serial
import serial.tools.list_ports
import time

print ('hello')
ports = list(serial.tools.list_ports.comports())
print (ports)


for p in ports:
    print (p[1])
    if "USB-SERIAL" in p[1]:
	    ser=serial.Serial(port=p[0],baudrate=9600)
    else :
	    print ("No Arduino Device was found connected to the computer")
	    
time.sleep(2)


ser.write("A 30 90 0 0 0".encode())
time.sleep(2)

ser.write("A 120 90 0 0 0".encode())
time.sleep(2)

ser.write("A 120 90 0 0 0".encode())
time.sleep(2)

ser.write("A 30 90 110 0 0".encode())
time.sleep(8)

ser.write("A 120 90 110 0 0".encode())
time.sleep(8)

ser.write("A 120 90 110 0 0".encode())
time.sleep(8)
