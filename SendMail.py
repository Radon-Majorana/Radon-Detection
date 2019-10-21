#coding: utf-8
import os
import smtplib
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email import encoders
import time


class mail:
	def __init__(self, fromaddress, password, toaddress, subject, body, filename, dirpath):
		self.fromaddr = fromaddress
		self.passwd = password
		self.toaddr = str(toaddress)
		self.subj = subject
		self.body = str(body)
		self.filename = filename
		self.dirpath = dirpath

	def Create(self):					#
		self.msg = MIMEMultipart()			#
		# FORMT #					#
		self.msg['From'] = self.fromaddr		#	INDIRIZZO MITTENTE (deve coincidere con il login)
		self.msg['To'] = self.toaddr			#	INDIRIZZO DESTINATARIO
		self.msg['Subject'] = self.subj			#	OGGETTO
		body = self.body				#	CORPO
		# FORMT #					#
		self.msg.attach(MIMEText(self.body, 'plain'))	#	CREAZIONE MAIL
		return self.msg					#

	def attachThis(self):
		path=self.dirpath + self.filename						#	IMPOSTAZIONE DEL PATH AL FILE
		attachment = open(path, "rb")							#	LETTURA FILE
												#
		part = MIMEBase('application', 'octet-stream')					#	PREPARAZIONE ALLA CODIFICA DELL'ALLEGATO
		part.set_payload((attachment).read())						#	PREPARAZIONE ALLA CODIFICA IN BASE64
		encoders.encode_base64(part)							#	CODIFICA IN BASE64
		part.add_header('Content-Disposition', "attachment; filename= %s" % self.filename)	#	CREAZIONE DELL'ALLEGATO
		self.msg.attach(part)								#	INSERIMENTO DELL'ALLEGATO
		print "File attached: " + self.filename						#	RIEPILOGO
		return 0									#
		
	def getPass(self):
		return self.passwd
	
	def getUser(self):
		return self.fromaddr
	
	def getmessage(self):
		return self.msg
	
	def Send(self):
		
		# COMM #
		print "Contacting server..."
		server = smtplib.SMTP('smtp.gmail.com', 587)				#	SELEZIONE SERVER SMTP
		server.starttls()							#	INIZIO COMUNICAZIONE CON SERVER
		print "Logging..."							#	
		server.login(self.fromaddr, self.passwd)				#	PROCEDURA DI LOGIN (indirizzo mail, password)
		text = self.msg.as_string()						#	SELEZIONE MAIL E CONVERSIONE
		print "Sending..."							#
		server.sendmail(self.fromaddr, self.toaddr, text)			#	INVIO MAIL (INDIRIZZO MITTENTE, INDIRIZZO DESTINATARIO,MAIL CONVERTITA)
		server.quit()								#	CHIUSURA COMUNICAZIONI CON SERVER 
		print "Mail sent. Closing communication with smtp server. \n \n DONE"
		
		# COMM #


def file_union():
	Union=open('Union.txt','w')
	N_file=1
	while 1:
		try:
			toopen=open('File'+str(N_file)+'.txt','r')
			towrite=toopen.readlines()
			towrite=''.join(towrite)
			Union.write(towrite)
			toopen.close()
			os.system('rm File'+str(N_file)+'.txt')
		except:
			print'File uniti\n'
			break
		N_file+=1
	Union.close()
	Union=open('Union.txt','r')
	first_and_last=Union.readlines()

	first=first_and_last[0]
	first=list(first)
	first.remove('\n')
	first=''.join(first)

	last=first_and_last[len(first_and_last)-1]
	last=list(last)
	last.remove('\n')
	last=''.join(last)
	Union.close()
	os.system('cp Union.txt '+str(first)+str('_')+str(last)+'.txt')
	os.system('rm Union.txt')
	return (str(first)+str('_')+str(last)+'.txt')


File_txt=file_union()
Mail=mail(					#	CREAZIONE MAIL (fromaddress, password, toaddress, subject, body, filename, dirpath)
"radon@majoranaorvieto.org",			#	INDIRIZZO MITTENTE
"210radon86",					#	PASSWORD MITTENTE
"os19_radon@majoranaorvieto.org", 	#	INDIRIZZO DESTINATARIO
"RADON - RILEVAZIONE",						#	OGGETTO
						#	CORPO
"Nuova rilevazione",
				#
File_txt,			#	NOME FILE
""				#	PATH FILE
)

Mail.Create()

Mail.attachThis()	#	INSERIMENTO DELL'ALLEGATO (Nome file CON ESTENSIONE,Directory del file CON / ALLA FINE)
Mail.Send()
os.system('rm '+str(File_txt))
