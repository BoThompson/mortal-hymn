state = 0
timer = 0
class Actor:
	def __init__(self):
		self.state = 1
		self.timer = -1
	def test(self):
		print(str(self.state) " is the state")
		print(str(self.timer) " is the timer")	
