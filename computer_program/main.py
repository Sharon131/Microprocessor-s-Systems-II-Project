import numpy as np
import serial
import matplotlib
matplotlib.use("TkAgg")
from matplotlib import pyplot as plt
from matplotlib import animation

fig, axs = plt.subplots(3, 2, constrained_layout=True)
line = []

for row in axs:
    for ax in row:
        ax.set_xlim(0, 2)
        ax.set_xlabel('Time[s]')
        tmp_line, = ax.plot([], [])
        line.append(tmp_line)
    row[0].set_ylabel('Value[g]')
    row[1].set_ylabel('Value[st./s]')
    row[0].set_ylim(-2.5, 2.5)
    row[1].set_ylim(-300, 300)

axs[0, 0].set_title('Accelerometer x-axis')
axs[1, 0].set_title('Accelerometer y-axis')
axs[2, 0].set_title('Accelerometer z-axis')
axs[0, 1].set_title('Gyroscope x-axis')
axs[1, 1].set_title('Gyroscope y-axis')
axs[2, 1].set_title('Gyroscope z-axis')

ser = serial.Serial('COM9', 9600)
t_time = 0
bit_no = float(2**15 - 1)
accelerometer_range = 2.0
gyroscope_range = 250.0


def get_data_from_port(index):
    byte_read1 = ord(ser.read(1))
    byte_read2 = ord(ser.read(1))
    data_read = byte_read1*256+byte_read2

    if is_negative(data_read):
        data_read = data_read - 2**16

    if index < 3:
        conversed_data = data_read * accelerometer_range / bit_no
    else:
        conversed_data = data_read * gyroscope_range / bit_no
    return conversed_data


def is_negative(data_from_port):
    return data_from_port & (1 << 15) == (1 << 15)


def data_gen():
    global t_time
    cnt = 0
    while cnt < 10000:
        cnt += 1
        t_time += 0.7
        accelerometer = []
        gyroscope = []
        accelerometer.append(get_data_from_port(0))
        accelerometer.append(get_data_from_port(1))
        accelerometer.append(get_data_from_port(2))
        gyroscope.append(get_data_from_port(3))
        gyroscope.append(get_data_from_port(4))
        gyroscope.append(get_data_from_port(5))
        yield t_time, accelerometer, gyroscope


xdata = []
accel = [[], [], []]
gyros = [[], [], []]


def init():
    for line_no in line:
        line_no.set_data([], [])
    return line


def animate(data):
    t, accel0, gyros0 = data

    for g in range(0, 3):
        accel[g].append(accel0[g])
        gyros[g].append(gyros0[g])

    xdata.append(t)

    for row1 in axs:
        for axi in row1:
            xmin, xmax = axi.get_xlim()
            if t >= xmax:
                axi.set_xlim(xmin, 2 * xmax)
                axi.figure.canvas.draw()

    line[0].set_data(xdata, accel[0])
    line[2].set_data(xdata, accel[1])
    line[4].set_data(xdata, accel[2])
    line[1].set_data(xdata, gyros[0])
    line[3].set_data(xdata, gyros[1])
    line[5].set_data(xdata, gyros[2])
    return line


anim = animation.FuncAnimation(fig, animate, data_gen,
                               interval=20, blit=True, repeat=False, init_func=init)

my_writer = animation.FFMpegWriter()
anim.save('basic_animation.mp4', writer=my_writer)

plt.show()
