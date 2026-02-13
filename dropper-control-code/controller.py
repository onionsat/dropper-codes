import serial
import serial.tools.list_ports
from time import sleep

print()

# getting available ports
ports = serial.tools.list_ports.comports()

print("Available devices:\n")

portDevices = []

for port in ports:
    print(f"Device: {port.device}")
    print(f"Description: {port.description}\n")

    portDevices.append(port.device)

# promting user to select from one of the avaliable ports
userPortOK = False

while userPortOK == False:
    userPort = input("Please select port: ")

    # check if the port provided is available
    if userPort in portDevices:
        userPortOK = True
    else:
        print("Port selected isn't an option! Try again!")

loraSerial = serial.Serial(userPort, 115200, timeout=1)


#sending init to Lora
initList = [b"sys reset", b"radio set mod lora", b"radio set pa on", b"radio set freq 862750000", b"radio set pwr 20", b"radio set sf sf10", b"radio set sync 12", b"radio set bw 125"]

for command in initList:
    loraSerial.write(command + b"\r\n")
    sleep(0.1)
    data = loraSerial.read(loraSerial.in_waiting)

    data = data[:-1]
    print(data.decode())

while True:
    userCommand = input("Command: ")

    if userCommand == "toggle":
        loraSerial.write(b"radio tx 12345678 1" + b"\r\n")
        sleep(0.1)

        data = loraSerial.read(loraSerial.in_waiting)
        data = data[:-2].decode()

        print(data)
    elif userCommand == "help":
        print("Toggle -> toggle dropper arm")
    else:
        print("Invaild command! Try help")