#import argparse
import asyncio
from sys import flags
#import websockets
import serial
from serial.tools import list_ports
from serial.tools import *


scheduled = []
#flag=1

def find_arduino_port():
    arduino_ports = [
        p.device
        for p in list_ports.comports()
        if 'CH340' in p.description  # Modify this if necessary to match your Arduino's description
    ]
    if arduino_ports:
        print(f"Arduino found at {arduino_ports[0]}")
        return arduino_ports[0]
    else:
        raise RuntimeError("Arduino port not found.")
# Connect to Arduino over serial
# Replace 'COM3' with the appropriate serial port for your Arduino
arduino_serial = serial.Serial(find_arduino_port(), 115200)

#msg = []

async def process_message(msg):
    if msg.startswith('/start_sheduler'):
       print("Start shedule in process message")
       await asyncio.create_task(scheduler_task())
    else:
        # Send message to Arduino over serial
        # Replace '/play_note' with the appropriate command for your Arduino code
        print(f"Sending to Arduino: {msg}")
        arduino_serial.write((msg + "\n").encode())
        await asyncio.sleep(0.02)

async def scheduler_task():
    global scheduled
    print("Starting scheduler")

    start_time = asyncio.get_event_loop().time()
    while scheduled:
        for index in range(len(scheduled)):
            item = scheduled[index]
            if item[0].isdigit():
               if (float(item.split(';')[0]) / 1000.0) <= (asyncio.get_event_loop().time() - start_time):
                  # Process rest of the message as if received from the server
                  print(asyncio.get_event_loop().time() - start_time)
                  print("Processing scheduled msg:", item)
                  #msg = item[item.index(';') + 1:]
                  await process_message(item[item.index(';') + 1:])
                  scheduled[index] = None
            else:
               print("Processing msg:", item)
               #msg = item[item.index(';') + 1:]
               await process_message(item)
               scheduled[index] = None
        scheduled = [x for x in scheduled if x is not None]
    print("Sheduler finish.")
    
#file=open("info.txt","w")#with open ("info.txt","w") as file
#file.write("0")
#file.closed

async def playing():
        flag = 0
        while True:
          if flag==0:
             a_answer = []
             while True:
               if arduino_serial.in_waiting > 0:
                 a_answer = arduino_serial.readline().decode(errors='ignore').strip()
                 print (f'Received message: {a_answer}')
               if a_answer == "start":
                 print ('Start sheduler!')
                 break
               await asyncio.sleep(0.000001)
             flag = 1
             print (f'Flag: {flag}')

          if flag==1:
             with open ("e:\T-lab-E\CyberTheater\RobbyBrown\scenario.txt") as file: #если что прописать полный путь
                lines = file.readlines()
                for line in lines:
                  message = line
                  print (f'Received message: {message}')
                  scheduled.append(message)
                  #this will store the line
             flag = 2    

          if flag==2:
             print ('send /start sheduler')
             await process_message('/start_sheduler')
             flag=0
          await asyncio.sleep(0.0001)
                 
# If arduino sent a message over serial, print it to the console
async def arduino_listener():
    while True:
        if arduino_serial.in_waiting > 0:
            print(f"{arduino_serial.readline().decode(errors='ignore').strip()}")
        await asyncio.sleep(0.000001)

if __name__ == '__main__':
    # Parse command line arguments

    # Start the WebSocket client
    # asyncio.gather()
    loop = asyncio.new_event_loop()
    # Start the Arduino listener
    # asyncio.new_event_loop().create_task(arduino_listener())
    #loop.create_task(arduino_listener())
    loop.create_task(playing())
    # loop.create_task(scheduler_task())
    loop.run_forever()
    # asyncio.get_event_loop().run_forever()

