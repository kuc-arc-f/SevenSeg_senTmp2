import threading
import serial
import datetime
import time

mDevice = "/dev/ttyAMA0"

mOK_CODE=1
mNG_CODE=0


if __name__ == "__main__":
#    ret_base= "000000000000000000000000"
    ser=serial.Serial(mDevice ,9600)
    from datetime import datetime

    while True:
        sTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        time.sleep(1.0)
        val=ser.readline()
        print("IN :"  + val)
        print("TM="  + sTime)
