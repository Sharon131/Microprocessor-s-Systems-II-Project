import serial
import matplotlib
matplotlib.use("TkAgg")
from matplotlib import pyplot as plt

x_axis_range = 25
bit_no = 256
accelerometer_range = 4
accelerometer_offset = 2
gyroscope_range = 500
gyroscope_offset = 250

ser = serial.Serial('COM9', 9600)
plt.close('all')

plt.figure(1)
fig, ax = plt.subplots(3, 2, constrained_layout=True)
line0 = ax[0, 0].plot(0, 0, 'g.')
ax[0, 0].set_title('Accelerometer X - axis')
ax[0, 0].set_xlabel('Measuring point')
ax[0, 0].set_ylabel('Value[g]')
ax[0, 0].set_xlim([0, x_axis_range])
ax[0, 0].set_ylim([-2, 2])

line1 = ax[0, 1].plot(0, 0, 'g.')
ax[0, 1].set_title('Gyroscope X - axis')
ax[0, 1].set_xlabel('Measuring point')
ax[0, 1].set_ylabel('Value[st. C/s]')
ax[0, 1].set_xlim([0, x_axis_range])
ax[0, 1].set_ylim([-2, 2])

line2 = ax[1, 0].plot(0, 0, 'b.')
ax[1, 0].set_title('Accelerometer Y - axis')
ax[1, 0].set_xlabel('Measuring point')
ax[1, 0].set_ylabel('Value[g]')
ax[1, 0].set_xlim([0, x_axis_range])
ax[1, 0].set_ylim([-2, 2])

line3 = ax[1, 1].plot(0, 0, 'b.')
ax[1, 1].set_title('Gyroscope Y - axis')
ax[1, 1].set_xlabel('Measuring point')
ax[1, 1].set_ylabel('Value[st. C/s]')
ax[1, 1].set_xlim([0, x_axis_range])
ax[1, 1].set_ylim([-2, 2])

line4 = ax[2, 0].plot(0, 0, 'r.')
ax[2, 0].set_title('Accelerometer Z - axis')
ax[2, 0].set_xlabel('Measuring point')
ax[2, 0].set_ylabel('Value[g]')
ax[2, 0].set_xlim([0, x_axis_range])
ax[2, 0].set_ylim([-2, 2])

line5 = ax[2, 1].plot(0, 0, 'r.')
ax[2, 1].set_title('Gyroscope Z - axis')
ax[2, 1].set_xlabel('Measuring point')
ax[2, 1].set_ylabel('Value[st. C/s]')
ax[2, 1].set_xlim([0, x_axis_range])
ax[2, 1].set_ylim([-2, 2])
fig.canvas.manager.show()


def add_point_to_plot(value, index_no):
#    line = get_line_from_number(index_no)
#    line[0].set_ydata(value)
    ax[0, 0].plot(value)
    fig.canvas.draw()
    fig.canvas.flush_events()
    plt.draw()
    plt.show()


def get_line_from_number(number):
    return {0: line0,
            1: line1,
            2: line2,
            3: line3,
            4: line4,
            5: line5}[number]


def get_data_from_port():
    byte_read = ser.read(1)
    if index < 3:
        data_read = ord(byte_read) * accelerometer_range / bit_no - accelerometer_offset
    else:
        data_read = ord(byte_read) * gyroscope_range / bit_no - gyroscope_offset
    return data_read


print('Hi, there!')
print(ser.is_open)

plt.show()

while 1:
    for index in range(0, 6):
        to_print = get_data_from_port()
        print(to_print)
        add_point_to_plot(to_print, index)
        plt.draw()

ser.close()

print('Mr Bean has finished.')
