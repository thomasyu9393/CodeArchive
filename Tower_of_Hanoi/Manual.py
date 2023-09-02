"""
Demonstrating Tower of Hanoi (Manual)
Author: 游承曦
"""
from vpython import *

#parameters
re, end = False, False

#initialize
scene = canvas(width=800, height=500, x=0, y=0, center=vec(0, 25, 0))
floor = box(pos=vec(0, -1, 0), size=vec(120, 1, 40), texture=textures.wood)
pos_x = [-40, 0, 40]
for i in range(3):
	rod = cylinder(pos=vec(pos_x[i], 0, 0), axis=vec(0, 30, 0), radius=1, texture=textures.wood)

#color = [red, orange, yellow, green, blue]
color = [vec(1, 0, 0), vec(1, 0.6, 0), vec(1, 1, 0), vec(0, 1, 0), vec(0, 0, 1)]

#animation rate
speed = 200

#three rods
stack = [[], [], []]

#total number of rings
N = 5

#current steps' counter
counter = 0
L1 = label(pos=vec(0, 0, 0), text='Minimum Step: 0', xoffset=0, yoffset=280, height=25, box=False, line=False)
L2 = label(pos=vec(0, 0, 0), text='Step Count: 0', xoffset=0, yoffset=250, height=25, box=False, line=False)

#Tower of Hanoi
def f(n, a, b, c):
	global counter, re, end
	if re or end:
		for i in range(3):
			while len(stack[i]) != 0:
				cur_ring = stack[i].pop()
				cur_ring.visible = False
		L1.text = 'Minimum Step = 0'
		L2.text = 'Step Count = 0'
		return
	if n == 1:
		counter += 1
		L2.text = 'Step Count: {}'.format(counter)
		cur_ring = stack[a].pop()
		while cur_ring.pos.y < 40:
			rate(speed)
			cur_ring.pos.y += 0.5
		if pos_x[a] < pos_x[c]:
			while cur_ring.pos.x < pos_x[c]:
				rate(speed)
				cur_ring.pos.x += 1
		else:
			while cur_ring.pos.x > pos_x[c]:
				rate(speed)
				cur_ring.pos.x -= 1
		if len(stack[c]) != 0:
			top_ring = stack[c][-1]
			while cur_ring.pos.y - top_ring.pos.y > 1.5:
				rate(speed)
				cur_ring.pos.y -= 0.5
		else:
			while cur_ring.pos.y > 1:
				rate(speed)
				cur_ring.pos.y -= 0.5
		stack[c].append(cur_ring)
	else:
		f(n-1, a, c, b)
		f(1, a, b, c)
		f(n-1, b, a, c)

def run(b1):
	global N, re
	L1.text = 'Minimum Step = {}'.format(2**N - 1)
	re = False
	b1.disabled = True

	#create rings
	for i in range(0, N):
		new_ring = ring(pos = vec(pos_x[0], 1 + 1.5*i, 0),
						axis = vec(0, 10, 0),
						radius = (1.5 * (N-i)),
						thickness = 1,
						color = color[4 - i%5])
		stack[0].append(new_ring)

	#run the recursive function
	f(N, 0, 1, 2)

b1 = button(text='Start', pos=scene.title_anchor, bind=run)

def reset(b2):
	global re
	re = True
	b1.disabled = False

b2 = button(text='Reset', pos=scene.title_anchor, bind=reset)

def stop(b3):
	global end
	end = True
	b1.disabled = True
	b2.disabled = True

b3 = button(text='End', pos=scene.title_anchor, bind=stop)

def set_N(b4):
	global N
	N = b4.value
	ntext.text = 'N = {}'.format(b4.value)

b4 = slider(min=1, max=10, value=5, step=1, length=200, bind=set_N, pos=scene.title_anchor)
ntext = wtext(text='N = {}'.format(b4.value), pos=scene.title_anchor)

while not end:
	TEST = 1

print('Finish')