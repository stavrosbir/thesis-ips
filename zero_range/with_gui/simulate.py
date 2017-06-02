# Stavros Birmpilis
# 25/3/17

import Tkinter
import ttk
from time import sleep
import threading
from subprocess import check_output
import sys

class mygui(Tkinter.Tk):

	# canvas size (float)
	width = 500.0
	height = 500.0
	# executable
	executable = './'+sys.argv[1]

	def __init__(self, parent):
		Tkinter.Tk.__init__(self, parent)
		self.parent = parent
		self.initialize()

	def initialize(self):
		# grid layout
		self.grid()

		# title
		label = Tkinter.Label(self, text='Zero range process with decreasing jump rates', fg='purple', font=('Arial', '18'))
		label.grid(column=0, row=0, columnspan=2)

		# input L
		L_label = Tkinter.Label(self, text='L : (torus size)', font=('Arial', '12', 'bold'))
		L_label.grid(column=0, row=3)
		self.L_var = Tkinter.StringVar()
		self.L_var.set('100')
		L_entry = Tkinter.Entry(self, textvariable=self.L_var)
		L_entry.grid(column=0, row=4)

		# input N
		N_label = Tkinter.Label(self, text='N : (#particles)', font=('Arial', '12', 'bold'))
		N_label.grid(column=0, row=5)
		self.N_var = Tkinter.StringVar()
		self.N_var.set('1000')
		N_entry = Tkinter.Entry(self, textvariable=self.N_var)
		N_entry.grid(column=0, row=6)

		# input b
		b_label = Tkinter.Label(self, text='b : (factor > 2)', font=('Arial', '12', 'bold'))
		b_label.grid(column=0, row=7)
		self.b_var = Tkinter.StringVar()
		self.b_var.set('4.0')
		b_entry = Tkinter.Entry(self, textvariable=self.b_var)
		b_entry.grid(column=0, row=8)

		# input moves
		moves_label = Tkinter.Label(self, text='total moves : ', font=('Arial', '12', 'bold'))
		moves_label.grid(column=0, row=9)
		self.moves_var = Tkinter.StringVar()
		self.moves_var.set('1000000')
		moves_entry = Tkinter.Entry(self, textvariable=self.moves_var)
		moves_entry.grid(column=0, row=10)

		# input frames
		frames_label = Tkinter.Label(self, text='skip frames : ', font=('Arial', '12', 'bold'))
		frames_label.grid(column=0, row=11)
		self.frames_var = Tkinter.StringVar()
		self.frames_var.set('100')
		frames_entry = Tkinter.Entry(self, textvariable=self.frames_var)
		frames_entry.grid(column=0, row=12)

		# button
		button = Tkinter.Button(self, text='Start', command=self.onStart)
		button.grid(column=0, row=13)

		# status
		self.status_var = Tkinter.StringVar()
		self.status_var.set('Ready!')
		status_label = Tkinter.Label(self, textvariable=self.status_var, fg='white', bg='red', font=('Arial', '12', 'italic'))
		status_label.grid(column=0, row=17)

		# canvas
		self.canvas = Tkinter.Canvas(self, width=self.width, height=self.height)
		self.canvas.grid(column=1, row=1, rowspan=15)

		# progress bar
		self.bar = ttk.Progressbar(self, length=self.width, mode='determinate', orient=Tkinter.HORIZONTAL)
		self.bar.grid(column=1, row=17)


	def onStart(self):
		# clear canvas
		self.canvas.delete('all')

		self.status_var.set('Processing...(blocks)')
		self.update()

		# get input
		L = int(self.L_var.get())
		N = int(self.N_var.get())
		b = float(self.b_var.get())
		moves = int(self.moves_var.get())
		frames = int(self.frames_var.get())

		# canvas units
		width_unit = self.width/L
		height_unit = self.height/N

		#initialize lines
		lines = [0]*L
		positions = [0.0]*L
		for i in xrange(L):
			positions[i] = i*width_unit + width_unit/2
			lines[i] = self.canvas.create_line(positions[i], self.height, positions[i], self.height, width=width_unit, fill='red')

		# run program
		output = check_output([self.executable, str(L), str(N), str(b), str(moves), str(frames)])
		out_lines = output.split('\n')[:-1]

		self.status_var.set('Presenting...')

		# play results
		for line in out_lines:
			space = map(int, line.split()[:L])
			for i in xrange(L):
				self.canvas.coords(lines[i], positions[i], self.height, positions[i], (self.height-space[i]*height_unit))
			self.canvas.update()
			self.bar.step(100.0*frames/moves)


		self.status_var.set('Ready!')



def main():
	app = mygui(None)
	app.title('Simulator')
	app.mainloop()


main()
