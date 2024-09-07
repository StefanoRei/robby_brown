import argparse
import asyncio
from sys import flags
#import websockets
import serial
from serial.tools import list_ports
from serial.tools import *


port = "/dev/ttyUSB0" # COM port name
scheduled = []


def find_arduino_port():
    arduino_ports = [
        p.device
        for p in list_ports.comports()
        if 'USB Serial' in p.description  # Modify this if necessary to match your Arduino's description
    ]
    if arduino_ports:
        s = serial.Serial('/dev/ttyUSB0')
        print(f"Arduino found at {arduino_ports[0]}")
        return arduino_ports[0]
   
    else:
        raise RuntimeError("Arduino port not found.")
# Connect to Arduino over serial
# Replace 'COM3' with the appropriate serial port for your Arduino
arduino_serial = serial.Serial(find_arduino_port(), 115200)

async def process_message(message):
    if message.startswith('/start_sheduler'):
        asyncio.create_task(scheduler_task())
    else:
        # Send message to Arduino over serial
        # Replace '/play_note' with the appropriate command for your Arduino code
        print(f"Sending to Arduino: {message}")
        arduino_serial.write((message + "\n").encode())
        await asyncio.sleep(0.02)

async def scheduler_task():
    global scheduled
    print("Starting scheduler")
    start_time = asyncio.get_event_loop().time()
    while scheduled:
        for index in range(len(scheduled)):
            item = scheduled[index]
            if (float(item.split(';')[0]) / 1000.0) <= (asyncio.get_event_loop().time() - start_time):
                # Process rest of the message as if received from the server
                print(asyncio.get_event_loop().time() - start_time)
                print("Processing scheduled msg:", item)
                await process_message(item[item.index(';') + 1:])
                scheduled[index] = None
        scheduled = [x for x in scheduled if x is not None]



file=open("info.txt","w")#with open ("info.txt","w") as file
file.write("0")
file.closed


flags=1
with open ("szenari.txt") as file: #если что прописать полный путь
    lines = file.readlines()

for line in lines:
            message = line
            print (f'Received message: {message}')
            if message[0].isdigit():
                        scheduled.append(message)
            else:
                 process_message(message)
while True:
    if flags==1:
        response = ser.readline()# Читаем ответ от Arduino#decoded_response= response.decode('utf-8')# Декодируем ответ из байтов в строку с использованием UTF-8
        asyncio.sleep(0.03)
        if response :#==команда от ардуино
                flags=2
    if flags==2:
        process_message('/start_sheduler')
        with open ("info.txt","r+") as file:
         fline=file.readlines()
        del fline[0]
        file.write("1")
        flags=3
    if flags==3:
        with open ("info.txt","r+") as file:
         n=file.readlines()#n[0].isdigit():
        if n==1:
            del fline[0]
            file.write("0")
            flags=1
                 



#if __name__ == '__main__':
    #try:
        # Parse command line arguments
        ##parser = argparse.ArgumentParser(description='WebSocket client script')
       ##parser.add_argument('--host', type=str, default='192.168.88.254', help='WebSocket server host')
       ## args = parser.parse_args()

    
        # Start the WebSocket client
        #asyncio.get_event_loop().run_forever()
    #except:
        #pass