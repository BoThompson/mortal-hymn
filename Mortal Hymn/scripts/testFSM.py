import game
state = 0
timer = 0
class testFSM:
	def __init__(self):
		self.state = 1
		self.timer = -1
		print("Initializing")
		self.pointer = 0
		
	def start(self):
		self.timer = 1000
		print(str(self.state) + " is the state")
		print(str(self.timer) + " is the timer")
	
	def translate(self, x, y, z):
		game.translate(self.pointer, x, y, z)
	
	def update(self):
		self.position = game.getposition(self.pointer)
		print(str(game.time()))
		self.timer = 10
		self.setrotation(6.28 / game.time() / , 0, 0)
		
		