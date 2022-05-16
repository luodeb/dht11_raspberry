from ctypes import *
import time

library = cdll.LoadLibrary('my_dht11.so')

def inti_dht11(pinNum):
    library.init_dht11.argtype = c_int
    library.init_dht11.restype = c_ulong
    a = c_int(pinNum)
    return library.init_dht11(a)

def preRead(pinNum):
    library.preRead.argtype = c_int
    a = c_int(pinNum)
    library.preRead(a)

def readSensorData(pinNum):
    library.readSensorData.argtype = c_int
    library.readSensorData.restype = c_ulong
    a = c_int(pinNum)
    return library.readSensorData(a)

if __name__ == "__main__":
    pinNum = 1
    print("start")
    inti_dht11(pinNum)

    while True:
        preRead(pinNum)
        time.sleep(5)
        data_tmp = readSensorData(pinNum)
        if data_tmp:
            print(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())))
            tmp = "{}.{}".format(int((data_tmp/256)%256),int(data_tmp%256))
            rh = "{}.{}".format(int((data_tmp/16777216)%256),int((data_tmp/65536)%256))
            print(f"The TMP:{tmp} °C")
            print(f"The RH :{rh} %")
            # print(hex(int(data_tmp/256)))