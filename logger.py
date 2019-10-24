#############################################################
#                                                           #                                                                     
#	VOCABOLARIO                                               #                                                                  
#                                                           #
#	PartialC = somma tic che verra azzerata ogni 15m          #
#                                                           #                                                                    
#	TIC = segnale in arrivo dal contatore                     #                                                                                                                                                                                                                                         
#                                                           #                                                                     
#	NextTime = ora attuale + 15m                              #
#	                                                          #
#	Time = ora attuale                                        #                                                                                                                                                                                                                 
#                                                           #                                                                                                                                                
#############################################################

######################################################
#IMPORT                                              #
                                                     #
import time, httplib                                 #
																									   #
import os,sys																				 #
																										 #
import serial, commands                              #
                                                     #
from shutil import copyfile                          #
                                                     #
from datetime import datetime, timedelta						 #
                                                     #
######################################################

#######################################################################################
def Connection():                                                                     #
	try:                                                                                #
		ser = serial.Serial('/dev/ttyACM0', 115200)		#/dev/tty/ACM0 POTREBBE CAMBIARE    #
		print("Port found and connected")                                                 #
		return ser                                                                        #
	except:                                                                             #
		print("Error. Check port")                                                        #
		sys.exit()                                                                        #
 
                                                                                      #
def CheckInternet():                                                                  #
	conn = httplib.HTTPConnection("www.google.com", timeout=1.5)                        #
	try:                                                                                #
		conn.request("HEAD", "/")                                                         #
		conn.close()                                                                      #
		return True                                                                       #
	except:                                                                             #
		conn.close()                                                                      #
	return False                                                                        #
                                                                                      #
#######################################################################################

ser = Connection()

#tutto sto coso serve pe aggiunge 15m senza srecchia il formato dell'ora#
NextTime = str (datetime.now () + timedelta (minutes = 1))
NextTime = NextTime.split ()
NextTime = NextTime [1]
NextTime = NextTime.split (".")
NextTime = NextTime [0]
print NextTime

TIC = 0

os.system("touch /home/pi/radon/rilevazione.txt")

while (True): 
	print(TIC)
	Time = datetime.now ().strftime ("%H:%M:%S") 
	if (NextTime <= Time): 
		print "TIME!"
		#qui crea il file finale, all'inizio lo chiamo solo rilevazione cosi la data la aggiungiamo all'ultimo prima di inviarla cosi non sbricchia la data# 
		FinalRilevation = open ("/home/pi/radon/rilevazione.txt", "a") 
		FinalRilevation.write (str(TIC) + "\n")
		FinalRilevation.close () 
		copyfile ("/home/pi/radon/rilevazione.txt", ("/home/pi/radon/backup/rilevazione" + str(Time) + ".txt")) 
		TIC = 0

		NextTime = str (datetime.now () + timedelta (minutes = 1)) 
		NextTime = NextTime.split () 
		NextTime = NextTime [1] 
		NextTime = NextTime.split (".") 
		NextTime = NextTime [0] 

	received = int(ser.readline()) 
	if received == 1:
		TIC = TIC + 1
	elif received == 2:
		if CheckInternet() == True:
			Date = datetime.datetime.now().strftime ("%d_%m_%Y")
			os.rename ("/home/pi/radon/rilevazione.txt", ("/home/pi/radon/rilevazione" + "_" + str(Date) + ".txt"))
			os.system("python SendMail.py")
	 
		else: print("nun ge sta l'indernet")
