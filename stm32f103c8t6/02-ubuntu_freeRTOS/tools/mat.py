#!/usr/bin/python3
import re
import sys
import time
import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

class Serial:
    def __init__(self, com='/dev/ttyUSB0', boardrate=115200):
        self.serial = serial.Serial(com, boardrate, timeout=1)
        self.dataMaxLen = 1000
        time.sleep(0.5)
        print("Ok open the serial", self.serial.portstr)
        self.draw_frame()

    def __del__(self):
        print("Ok close the serial", self.serial.portstr)
        self.serial.close()

    def read(self):
        return self.serial.readline()

    def parse(self, data):
        #log = "subtask2_motors[195]:[83216] r36 k40 (p9.50 i0.80 d0.0) O:-829 P:-380 I:-449 D:0"
        row = int(re.search(' r([-\d]+)', data, re.M).group(1))
        kal = int(re.search(' k([-\d]+)', data, re.M).group(1))
        tar = int(re.search(' t([-\d]+)', data, re.M).group(1))
        out = int(re.search(' O([-\d]+)', data, re.M).group(1))
        p = float(re.search('p([-\.\d]+)', data, re.M).group(1))
        i = float(re.search(' i([-\.\d]+)', data, re.M).group(1))
        d = float(re.search(' d([-\.\d]+)', data, re.M).group(1))
        pout = int(re.search(' P([-\d]+)', data, re.M).group(1))
        iout = int(re.search(' I([-\d]+)', data, re.M).group(1))
        dout = int(re.search(' D([-\d]+)', data, re.M).group(1))
        pdata = {'row': row, 'kal': kal, 'tar': tar, 'out': out, 'p': p, \
                'i': i, 'd': d, 'pout': pout, 'iout': iout, 'dout': dout}
        return pdata

    def draw_frame(self):
        # 创建图形和轴
        plt.ion()  # 打开交互模式
        self.fig, self.ax = plt.subplots()
        # 初始化两条线
        self.line = {}
        self.line['tar'], = self.ax.plot([], [], label='Tar')
        self.line['row'], = self.ax.plot([], [], label='Row')
        self.line['kal'], = self.ax.plot([], [], label='Kal')
        self.line['out'], = self.ax.plot([], [], label='Out')
        self.ax.set_xlim(0, self.dataMaxLen)
        self.ax.set_ylim(-100, 100)  # 根据你的数据范围调整
        self.ax.legend()
        self.data = {k: [] for k in self.line}

    def show(self, pdata):
        print(pdata)
        self.ax.set_title('PID control(Kp: {}, Ki: {}, Kd: {})'.format(pdata['p'], pdata['i'], pdata['d']))
        for dk in self.data:
            if dk == 'tar':
                self.data[dk] = [pdata[dk]] * self.dataMaxLen
            else:
                self.data[dk].append(pdata[dk])
            # 保持固定长度
            if (len(self.data[dk]) > self.dataMaxLen):
                self.data[dk].pop(0)
            # 更新图表数据
        for lk in self.line:
            self.line[lk].set_xdata(range(len(self.data[lk])))
            self.line[lk].set_ydata(self.data[lk])
        self.ax.set_ylim(min(min(v) for v in self.data.values()) - 1, max(max(v) for v in self.data.values()) + 1)
        plt.pause(0.1)

    def handle(self):
        try:
            while(True):
                data = self.read()
                if data[0:len('subtask2_motors')] == b'subtask2_motors':
                    pdata = self.parse(data.decode('utf-8'))
                    self.show(pdata)
        except KeyboardInterrupt as e:
            print("exit from ctrl+c")


if __name__ == '__main__':
    ser = Serial()
    ser.handle()
