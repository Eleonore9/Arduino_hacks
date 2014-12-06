# this is a very simple sample script for logging data from an Arduino
import serial 
from datetime import datetime

# set this to your serial port
SERIAL_PORT = "/dev/ttyACM0"


# log data from serial port into a csv file
def logSensors():
    
    # open the serial port
    serialConnection = serial.Serial( SERIAL_PORT, timeout=2.0 )
    
    # open the output file (for appending)
    outputFile = open( "test_tempsensor.csv", "a" )
    
    # write the date and time to keep track of things
    outputFile.write(str(datetime.now()) + '\n')
    outputFile.write('Temperature (degrees C)')

    # loop until user breaks
    while True:

        data = serialConnection.readline().strip()
        if data:
            print data
            outputFile.write( data + "\n" )
        
    
# if run as top-level script
if __name__ == "__main__":
    try:
        logSensors()
    except KeyboardInterrupt:
        pass
