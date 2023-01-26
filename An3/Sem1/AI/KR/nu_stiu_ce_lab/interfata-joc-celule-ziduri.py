"""
Faceti click intre celule pentru a crea un zid.
Incercati sa inconjurati o celula cu toate cele 4 ziduri.
Daca apasati tasta i puteti activa/dezactiva imaginile.
"""

import pygame
import sys

class Celula:
	#coordonatele nodurilor ()
	grosimeZid=11 #numar impar
	fundalCelula=(255,255,255)
	culoareLinii=(0,0,0)
	afisImagini=True

	def __init__ (self, left, top, w, h, display, lin, col,interfata, cod=0):
		self.dreptunghi=pygame.Rect(left, top, w, h)
		self.display=display
		self.zid=[None,None,None,None]
		#zidurile vor fi pe pozitiile 0-sus, 1-dreapta, 2-jos, 3-stanga
		self.cod=0
		if lin>0:
			self.zid[0]=pygame.Rect(left,top-1-self.__class__.grosimeZid//2, w,self.__class__.grosimeZid)
		else:
			self.cod+=2**0
		if col<interfata.nrColoane-1:
			self.zid[1]=pygame.Rect(left+w-self.__class__.grosimeZid//2,top, self.__class__.grosimeZid, h)
		else:
			self.cod+=2**1
		if lin<interfata.nrLinii-1:
			self.zid[2]=pygame.Rect(left,top+h-self.__class__.grosimeZid//2, w,self.__class__.grosimeZid)
		else:
			self.cod+=2**2
		if col>0:
			self.zid[3]=pygame.Rect(left-1-self.__class__.grosimeZid//2,top, self.__class__.grosimeZid,h)
		else:
			self.cod+=2**3

		#print(self.zid)
		#0001 zid doar sus
		#0011 zid sus si dreapta etc
	def deseneaza(self):
		pygame.draw.rect(self.display, self.__class__.fundalCelula, self.dreptunghi)
		#masti=[1,2,4,8]
		masca=1
		for i in range(4):
			if self.cod & masca:
				if self.zid[i]:
					pygame.draw.rect(self.display, self.__class__.culoareLinii, self.zid[i])		
			masca*=2
		

class Interfata:
	culoareEcran=(0,0,0)
	
	
	dimCelula=50
	paddingCelula=5
	dimImagine=dimCelula-2*paddingCelula

	def __init__(self, nrLinii=7, nrColoane=10, ecran=None):
		self.nrLinii=nrLinii
		self.nrColoane=nrColoane
		self.ecran=ecran
		self.matrCelule=[[Celula(display=ecran, left=col*(self.__class__.dimCelula+1), top=lin*(self.__class__.dimCelula+1), w=self.__class__.dimCelula, h=self.__class__.dimCelula, lin=lin, col=col, interfata=self) for col in range(nrColoane)] for lin in range(nrLinii) ]

		
		furios = pygame.image.load('foarte_furioasa_m.png')

		self.furios = pygame.transform.scale(furios, (self.__class__.dimImagine,self.__class__.dimImagine))
		vesel = pygame.image.load('smiley_galben_vesel.png')

		self.vesel = pygame.transform.scale(vesel, (self.__class__.dimImagine,self.__class__.dimImagine))

	def deseneazaImag(self, imag, cel):
		self.ecran.blit(imag,(cel.dreptunghi.left+self.__class__.paddingCelula,  cel.dreptunghi.top+self.__class__.paddingCelula))

	def deseneazaEcranJoc(self):
		self.ecran.fill(self.__class__.culoareEcran)
		for linie in self.matrCelule:
			for cel in linie:
				cel.deseneaza()  
				if Celula.afisImagini:
					imag=self.vesel if cel.cod!=15 else self.furios
					self.deseneazaImag(imag, cel)
		pygame.display.update()
pygame.init()


ecr=pygame.display.set_mode(size=(700,400))
interf= Interfata(nrLinii=7, nrColoane=10, ecran=ecr)

interf.deseneazaEcranJoc()
#bucla jocului care imi permite sa tot fac mutari
while True:		
	for ev in pygame.event.get(): 
		#daca utilizatorul face click pe x-ul de inchidere a ferestrei
		if ev.type == pygame.QUIT:
			pygame.quit()
			sys.exit()
		if ev.type == pygame.KEYDOWN:
			if ev.key == pygame.K_i:
				Celula.afisImagini=not Celula.afisImagini
				interf.deseneazaEcranJoc()
		#daca utilizatorul a facut click
		elif ev.type == pygame.MOUSEBUTTONDOWN: 
			pos = pygame.mouse.get_pos()
			zidGasit=[]
			for il, linie in enumerate(interf.matrCelule):
				for ic, cel in enumerate(linie):					
					for iz,zid in enumerate(cel.zid):
						if zid and zid.collidepoint(pos):
							zidGasit.append((cel,iz,zid))
			celuleAfectate=[]
			if 0<len(zidGasit)<=2:
				for (cel,iz,zid) in zidGasit:
					pygame.draw.rect(interf.ecran, Celula.culoareLinii,zid)
					cel.cod|=2**iz
					celuleAfectate.append(cel)		
				#doar de debug
				print("\nMatrice interfata: ")
				for l in interf.matrCelule:
					for  c in l:
						print(c.cod,end=" ")
					print()
			for celA in celuleAfectate:
				if celA.cod==15 and Celula.afisImagini:
					interf.deseneazaImag(interf.furios, celA)
			pygame.display.update()
					
							