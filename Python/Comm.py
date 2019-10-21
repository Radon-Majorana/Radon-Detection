# coding: utf-8
import serial
import time
import sys
import alarm
import datetime as dt
import os
import httplib

def Connection():
	try:
		ser = serial.Serial('/dev/ttyACM0', 115200)
		print("Port found and connected")  # Connessione alla porta seriale
		return ser
	except:
		print("Error. Check port")
		return -1


def Send(ser, cmd):
	print("Got command: " + str(cmd) + "  Now writing")
	line = ser.write(cmd)  # Scrittura comando
	print(str(cmd) + " Sent to serial")

	print("\n")

	print("Waiting reply")
	maxWaitingTime=2
	try:
		with alarm.Timeout(id_='a', seconds=4):
			response = int(ser.readline())  # Attesa conferma
	except alarm.TimeoutError as e:  # No impulses for 5 minutes
			print('raised', e.id_)
			response=-1
	print("Got reply: " + str(response))
	print'ok'
	if response == 121:
		return 0
	elif response == 1:
		return 1
	else:
		return -1


def Listening(ser):
	bip = int(ser.readline())
	return bip


def getStringTime():
	ts = time.time()
	st = dt.datetime.fromtimestamp(ts).strftime('%d-%m-%Y_%H:%M:%S')
	return st


def saveFile(fileToSave, N_file):
	# Salva il file passato
	fileToSave.close()
	# Prende l'ora corrente
	fileName = 'File' + str(N_file) + '.txt'
	# Genera il nuovo file con la data come nome
	newFile = open(str(fileName), "w")
	currentTimeString = getStringTime()
	newFile.write(currentTimeString + "\n")
	return newFile



def calculateDelta(startTimeInS, finishTimeInS):
	deltaInSeconds = finishTimeInS - startTimeInS

	return deltaInSeconds


def Numero_ricevuto(numero):
	if numero == 33:
		#If 33 is received, Arduino blocked all comunications (Decidere cosa fare!!!)
		#os.system('reboot')
		print("Arduino blocked all the activities!")
	if numero == 107:
		serial.write('121')
        
  
def have_internet():
	conn = httplib.HTTPConnection("www.google.com", timeout=1.5)
	try:
		conn.request("HEAD", "/")
		conn.close()
		return True
	except:
		conn.close()
	return False

ser = Connection()

# If there's an error while connecting, connection() returns -1
if(ser == -1):

	# Connection failed: exiting the script
	sys.exit()

else:

	# Connection established, turn on the status LED and make a check (code for checking: 107)
	check = Send(ser, '107')
	time.sleep(1.5)

if(check == -1):

	# Check failed: Arduino isn't working
	sys.exit("Arduino doesn't reply")
elif(check == 1):
		print "1"

Send(ser, str(12))
def main(ser):
	# Declaring the variable which counts how many detection we made at the start in order to get detection even during
	# startup checks
	bip_tot = 0

	#Initiate connection with Arduino


    # Code for file saving
	fileNumber = 1

    # Creates the first logging file, named "File1.txt". Following files will be named "File2.txt", "File3.txt"...
	currentLog = open('File' + str(fileNumber) + '.txt',"w")

    # Gets the current time and writes it on the log file
	currentTimeString = getStringTime()
	currentLog.write(currentTimeString + "\n")

    # Gets the detection starting time in seconds
	startTimeInS = time.time()
	startTimeWrite = time.time()
	repeat=True
    # At this point Arduino's working and python can start listening for signals (bip)
	
	while 1:
		if dt.datetime.fromtimestamp(time.time()).strftime('%H')=='19' and repeat==True:
			ser.write('10')
			repeat=False
		connection=have_internet()
		if connection==True:
			ser.write('8')
			ser.write('11')
			repeat=True
			saveFile(currentLog, fileNumber)
			os.system('python SendMail.py &')
			time.sleep(15)
			ser.write('9')
			print "STACCAH STACCAH"
			time.sleep(10)
			return
        # Every fourth of an hour it prints the time along with how many detection it made and checks if Arduino's
        # working
		finishTimeWrite = time.time()
		if calculateDelta(startTimeWrite, finishTimeWrite) >= 900:
			currentLog.write(getStringTime() + ',' + str(bip_tot) + "\n")  # fa il timestamp dell'ultimo  quarto d'ora''
			startTimeWrite = time.time()
			bip_tot = 0


        # Every hour it saves the log and it creates a new one
		finishTimeInS = time.time()
		if calculateDelta(startTimeInS, finishTimeInS) >= 3600:
			fileNumber += 1
			currentLog = saveFile(currentLog, fileNumber)
			startTimeInS = time.time()

        # Following code puts a maximun waiting time for a detection to arrive, if nothing arrives in 300 s, it breaks
        # the listening and checks if Arduino's working

		maxWaitingTime = 300  # Seconds
		bip = 0

		try:
			with alarm.Timeout(id_='a', seconds=maxWaitingTime):
				bip = Listening(ser)

		except alarm.TimeoutError as e:  # No impulses for 5 minutes
			print('raised', e.id_)

			Check = Send(ser, "107")  # controlla se arduino funge
			if Check == -1:
				saveFile(currentLog, fileNumber)
				print("\n ERROR. Port dicsconnected at ")	#
				sys.exit("Arduino doesn't reply")	
			elif Check== 1:
				bip_tot+=1

        # If a detection happened, increase the detection count variable
		if bip == 1:
			bip_tot += 1
			print "TIC"
		else:
			Numero_ricevuto(bip)


if __name__ == "__main__":
	while 1:
		main(ser)
