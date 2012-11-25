import serial, scrapelib, json, time

def sendCheerlightsColor():
        try:
                cheerlights = json.loads(s.urlopen('http://api.thingspeak.com/channels/1417/field/1/last.json'))
                print 'The Cheerlights color was {0} at {1}.'.format(cheerlights['field1'],time.strftime("%H:%M:%S", time.localtime()))
                #ser = serial.Serial("/dev/tty.usbserial-A900frks", 9600, timeout=1)
                ser.write(cheerlights['field1'])
                ser.write(",")
                #time.sleep(1)
                #response = ser.readline()
                #responseColor = response[:len(response)-2]
                #print 'The tree acknowledges {0}.'.format(responseColor)
                #ser.close()
        except:
                print 'Error in sendCheerlightsColor'

if __name__ == '__main__':
        s = scrapelib.Scraper(requests_per_minute=5, follow_robots=True)
        ser = serial.Serial("/dev/tty.usbserial-A900frks", 9600, timeout=1)
                
        while True:
                try:
						if ser.isOpen() == 0:
								print 'Re-opening a serial connection'
								ser = serial.Serial("/dev/tty.usbserial-A900frks", 9600, timeout=1)
						incoming = ser.readline()
						#print '|{0}|'.format(incoming,)
						if incoming[:len(incoming)-2] == '<CheerlightsColor>':
								print 'Send Color Command Received'
								sendCheerlightsColor()
						elif len(incoming) > 0:
								incoming = incoming[:len(incoming)-2]
								print 'The tree acknowledges {0}.'.format(incoming)
						incoming = ''
                except:
                        print 'Error in main'
