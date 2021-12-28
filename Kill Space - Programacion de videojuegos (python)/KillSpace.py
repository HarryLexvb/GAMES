import pygame, random
# defino el tamaño y color de mi ventana 
WIDTH = 800
HEIGHT = 600
BLACK = (0, 0, 0)
WHITE = ( 255, 255, 255)
GREEN = (0, 255, 0)

#EDITA 

pygame.init() #incializamos pygame 
pygame.mixer.init() #sirve para reproducir el sonido 
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("METALHEAD")
clock = pygame.time.Clock() #controlamos el tiempo 

def draw_text(surface, text, size, x, y): #definimos una funcion para dibujar texto 
										#surface es para donde queremos dibujar el texto 
	font = pygame.font.SysFont("serif", size) #fuente  
	text_surface = font.render(text, True, WHITE) #ubicacion donde pintamos el texto
	text_rect = text_surface.get_rect() #recta de una imagen 
	text_rect.midtop = (x, y) #posicionar 
	surface.blit(text_surface, text_rect) #pintarlo en pantalla 

def draw_shield_bar(surface, x, y, percentage): #creamo la funcion para dibujar la barra de salud
	BAR_LENGHT = 100 #largo de mi barra
	BAR_HEIGHT = 10 #que tan alto sera la barra 
	fill = (percentage / 100) * BAR_LENGHT #que tanto se va a llenar la barra 
	border = pygame.Rect(x, y, BAR_LENGHT, BAR_HEIGHT) #bordes que es lo que cubre la barra 
	fill = pygame.Rect(x, y, fill, BAR_HEIGHT) #llenamos la barra 
	pygame.draw.rect(surface, GREEN, fill) #le damos un color 
	pygame.draw.rect(surface, WHITE, border, 2)

class Player(pygame.sprite.Sprite): #cremos la clase jugador 
	def __init__(self): #inicializamos la clase con el constructor 
		super().__init__() #definimos una superclase
		self.image = pygame.image.load("assets/player.png") #cargamos la imagen 
		self.image.set_colorkey(BLACK) #removemos los borde negros de la imagen 
		self.rect = self.image.get_rect() #obtenemos el cuadro de mi sprite
		#lo ponemos en pantalla 
		self.rect.centerx = WIDTH // 2
		self.rect.bottom = HEIGHT - 10
		self.speed_x = 0 #velocidad con el cual se mueve 
		self.shield = 100 

	def update(self): #funcion actualizar 
		self.speed_x = 0 #inicia la veolicidad 
		keystate = pygame.key.get_pressed() #verificamos si alguna tecla ha sido presionada 
		if keystate[pygame.K_LEFT]: #tecla pulsada a la izquierda
			self.speed_x = -5 #la velocidad disminuye en 5 para moverse a la izquierda
		if keystate[pygame.K_RIGHT]: #tecla pulsada a la derecha 
			self.speed_x = 5 #l velocidad aumenta en 5 a la derecha 
		self.rect.x += self.speed_x #sumamos la velocidad 
		if self.rect.right > WIDTH:
			self.rect.right = WIDTH
		if self.rect.left < 0:
			self.rect.left = 0 

	def shoot(self): #creamos el metodo shoot
		bullet = Bullet(self.rect.centerx, self.rect.top) #creamos la bala 
		all_sprites.add(bullet) #agregamos a todos los sprites 
		bullets.add(bullet) #agregamos a la lista de las balas 
		laser_sound.play()

class Meteor(pygame.sprite.Sprite): #creamos los meteoros
	def __init__(self): #iniciamos la clase 
		super().__init__() #iniciamos la superclase 
		self.image = random.choice(meteor_images) #cargar lista meteor_images 
		self.image.set_colorkey(BLACK) #quitamos borde negro a la imagen
		self.rect = self.image.get_rect() #obtenemos la trecta 
		self.rect.x = random.randrange(WIDTH - self.rect.width) 
		self.rect.y = random.randrange(-140, -100) #random para que aparezca en cualquier lado
		self.speedy = random.randrange(1, 16)
		self.speedx = random.randrange(-5, 5)

	def update(self): #actualizamos
		self.rect.y += self.speedy #aumentamos la velociad
		self.rect.x += self.speedx 
		if self.rect.top > HEIGHT + 10 or self.rect.left < -40 or self.rect.right > WIDTH + 40:   
			self.rect.x = random.randrange(WIDTH - self.rect.width)
			self.rect.y = random.randrange(-140, - 100)
			self.speedy = random.randrange(1, 16)

class Bullet(pygame.sprite.Sprite): #creamos una clase para las balas 
	def __init__(self, x, y): #iniciamos la clase con dos parametros que es la posicion
		super().__init__() #iniciamos la superclase
		self.image = pygame.image.load("assets/laser1.png") #cargamos la imagen 
		self.image.set_colorkey(BLACK) #borramos los bordes negros 
		self.rect = self.image.get_rect() #verificamos la recta
		self.rect.y = y
		self.rect.centerx = x #es el centro del objeto es decir sale en el centro del objeto que dispara
		self.speedy = -10 #la velocidad es negativa porque sale desde abajo hacia arriba
		self.speedx = 5

	def update(self):
		self.rect.y += self.speedy
		self.rect.x += self.speedx
		if self.rect.bottom < 0:
			self.kill() #este metodo elimina todas las instancias de este objeto en cualquier lista 

class Explosion(pygame.sprite.Sprite): #creamos la clase explosion 
	def __init__(self, center): #inciamos la clase 
		super().__init__() #inciamos la superclase 
		self.image = explosion_anim[0] #se empiza con la imagen 0 para despues iterar por toda la lista 
		self.rect = self.image.get_rect()  #agarramos la recta
		self.rect.center = center #centramos la imagen 
		self.frame = 0 #creamos una frame para que vaya aumentando 
		self.last_update = pygame.time.get_ticks() # cuanto tiempo ha trancurrido para hacer la animacion
		self.frame_rate = 50 # VELOCIDAD DE LA EXPLOSION

	def update(self): #creamo una funcion actualizar 
		now = pygame.time.get_ticks() # cuanto tiempo ha trancurrido cuando se crea la explosion
		if now - self.last_update > self.frame_rate: #comparamos 
			self.last_update = now #incicia explosion
			self.frame += 1 #aumentar de 1 en 1
			if self.frame == len(explosion_anim): #verificamos que llega al final de la lista
				self.kill() #si llega al final, eleminar todos los sprites 
			else:
				center = self.rect.center 
				self.image = explosion_anim[self.frame] 
				self.rect = self.image.get_rect()
				self.rect.center = center


def show_go_screen(): #creamo la funcion para game over 
	screen.blit(background, [0,0]) 
	draw_text(screen, "KILL SPACE", 65, WIDTH // 2, HEIGHT // 4)
	draw_text(screen, "instagram: HarryLex", 27, WIDTH // 2, HEIGHT // 2)
	draw_text(screen, "Press Key", 20, WIDTH // 2, HEIGHT * 3/4)
	pygame.display.flip() # para mostrarlo en pantala
	waiting = True 
	while waiting: #mientras estemos esperando 
		clock.tick(60) #frames por segundo 
		for event in pygame.event.get():
			if event.type == pygame.QUIT: 
				pygame.quit() #salir de la pantalla  
			if event.type == pygame.KEYUP: #verificar si alguna tecla se ha presionado
				waiting = False


meteor_images = []
meteor_list = ["assets/Met_01.png", "assets/Met_02.png", "assets/Met_03.png", "assets/Met_04.png",
				"assets/Met_05.png", "assets/Met_06.png", "assets/Met_07.png", "assets/Met_08.png",
				"assets/Met_09.png","assets/Met_10.png","assets/Met_11.png"] #cargamos todas las imagenes de meteoros 
for img in meteor_list:
	meteor_images.append(pygame.image.load(img)) #agregamos a la lsita meteor_images


####----------------EXPLOSTION IMAGENES --------------
explosion_anim = [] #una lista para almacenar las iamgenes 
for i in range(1,7):
	file = "assets/Explo_0{}.png".format(i)
	img = pygame.image.load(file)#cargamos la imagen 
	img.set_colorkey(BLACK)#le quitamos el fondo negro
	img_scale = pygame.transform.scale(img, (70,70)) #escalar la imagen para que no ocupe mucho espacio
	explosion_anim.append(img_scale) #agregamos a la lis	ta explosion_anim

# Cargar imagen de fondo
background = pygame.image.load("assets/background.jpg").convert()

# Cargar sonidos
laser_sound = pygame.mixer.Sound("assets/laser5.ogg")
explosion_sound = pygame.mixer.Sound("assets/explosion.wav")
pygame.mixer.music.load("assets/Hellrider.mp3")
pygame.mixer.music.set_volume(0.2)


pygame.mixer.music.play(loops=-1) #el sonido entra en un bucle, que se repetira infinitamente 

#### ----------GAME OVER
game_over = True
running = True #comenzamos el bucle principal

while running:
	if game_over:

		show_go_screen()

		game_over = False
		all_sprites = pygame.sprite.Group() #creamos el grupo 
		meteor_list = pygame.sprite.Group() #creamos el grupo para almacear los meteoros
		bullets = pygame.sprite.Group() #creamo el grupo para las balas

		player = Player() #instnciamos player 
		all_sprites.add(player) #agregamos player a la lista
		for i in range(12):  #sera 8 meteoros 
			meteor = Meteor() 
			all_sprites.add(meteor) #agrrgamos a la lista de todos los sprites 
			meteor_list.add(meteor) #agregamos a la lista de meteoros 

		score = 0 #puntuacion en 0 


	clock.tick(60) #definimos el reloj, en este caso 60 frames por segundo 
	for event in pygame.event.get(): #evento para salir de la ventana 
		if event.type == pygame.QUIT:
			running = False

		#evento cada vez que se precione espacio dispare
		elif event.type == pygame.KEYDOWN: 
			if event.key == pygame.K_SPACE:
				player.shoot() #el jugador dispara 


	all_sprites.update() #actulizamos 

	#colisiones - meteoro - laser
	hits = pygame.sprite.groupcollide(meteor_list, bullets, True, True) #metodo groupcollide verifica las colisiones de un grupo con otro en este caso metros hy balas 
	for hit in hits:
		score += 10 #el puntaje se subira de 10 en 10 
		explosion_sound.play()
		explosion = Explosion(hit.rect.center) #se agrega una explosion cada vez que el laser colisione 
		all_sprites.add(explosion) #agregamos a toos los sprites 
		meteor = Meteor()
		all_sprites.add(meteor)
		meteor_list.add(meteor)

	# verificar colisiones - jugador - meteoro
	hits = pygame.sprite.spritecollide(player, meteor_list, True)
	for hit in hits: #verificamos si hay algun elemento de esta lista y si me choca salgo del juego
		player.shield -= 25 # disminuimo 25 puntos cada vez que un meteoro me golpee
		meteor = Meteor()
		all_sprites.add(meteor)
		meteor_list.add(meteor)
		if player.shield <= 0:
			game_over = True

	screen.blit(background, [0, 0]) #parametros de ubicacion 0,0 (desde el principio)

	all_sprites.draw(screen)

	#Marcador
	draw_text(screen, str(score), 25, WIDTH // 2, 10)

	#barra de vida 
	draw_shield_bar(screen, 5, 5, player.shield) 

	pygame.display.flip()
pygame.quit()