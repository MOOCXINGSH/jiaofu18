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

song=['A','1','0','0',' ','1','0','0']
cmd1="A 30 20 20 0 0"
cmd2="A 90 20 20 0 0"
cmd3="A 150 20 20 0 0"
cmds=[cmd1,cmd2,cmd3]
count=0

while True:
    cmd=cmds[count]
    ser.write(cmd.encode())
    print(cmd)
    time.sleep(5)
    count=count+1
    if count >2:
        count=0


