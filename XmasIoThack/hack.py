import serial 

SERIAL_PORT = "/dev/ttyACM*"

# open the serial port
serialConnection = serial.Serial( SERIAL_PORT, timeout=2.0 )

data = serialConnection.readline().strip()

if data:
    print data
