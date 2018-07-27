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

cmdL="A 30 20 20 "
cmdM="A 90 20 20 "
cmdR="A 150 20 20 "
cmdLF="A 30 20 120 "
cmdMF="A 90 20 120 "
cmdRF="A 150 20 120 "


cmds=[cmdL,cmdM,cmdR,cmdLF,cmdM,cmdRF]
count=0

for cmd in cmds:    
    ser.write(cmd.encode())
    print(cmd)
    time.sleep(5)


