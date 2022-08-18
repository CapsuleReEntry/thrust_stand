import asyncio
import time
import psutil
import matplotlib.pyplot as plt
import datetime

import serial

fig = plt.figure()
ax = fig.add_subplot(111)
fig.show()
ser = serial.Serial('COM10', 9800, timeout=1)
time.sleep(2)

i = 0
x, y = [], []

with open('data.txt', 'w') as f:
	f.write('')



async def draw_graph(i):

	line = ser.readline()   # read a byte string
	print(line)
	line = str(line).split(' ')

	gram = float(line[1])


	x.append(i)
	y.append(gram)
    
	ax.plot(x, y, color='b')
    
	fig.canvas.draw()
    
	ax.set_xlim(left=max(0, i-50), right=i+50)
    
	time.sleep(0.1)
	#i += 1

	return gram

async def write_data():

	line = ser.readline()   # read a byte string

	line = str(line).split(' ')
	gram = float(line[1])

	date = datetime.datetime.now()


	with open('data.txt', 'a') as f:
		f.write('\n')
		f.write(f'{date} : ')
		f.write(str(gram))

async def main(i):
	task1 = asyncio.create_task(draw_graph(i))
	task2 = asyncio.create_task(write_data())

	await task1
	await task2

print(time.strftime('%X'))


while True:
	asyncio.run(main(i))
	i += 1


plt.close()

ser.close()
