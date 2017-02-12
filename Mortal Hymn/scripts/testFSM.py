state = 0
timer = 0
class testFSM:
	def __init__(self):
		self.state = 1
		self.timer = -1
	def start(self):
		self.timer = 1000
		print(str(self.state) + " is the state")
		print(str(self.timer) + " is the timer")	
	def update(self):
		self.timer = 1000
		self.state = self.state + 1
		print(str(self.state) + " is the state")
		print(str(self.timer) + " is the timer")	