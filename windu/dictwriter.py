import sys

ch = sys.argv[1]
com = '/scratch/galette/bierlich/tools/windu/windu/'
#com = '../windu/'
if ch=="objs":
	objects = open(com+'objs.h','r')
	for line in objects:
		print com+line.replace('#include \"','').replace('\"','').replace(".h",".o").replace('\n','')

if ch=="templ":
	templates = open(com+'templ.h','r')
	for line in templates:
		if line.find("objs") < -1:	
			print com+line.replace('#include \"','').replace('\"','').replace('\n','')
