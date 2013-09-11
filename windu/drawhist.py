#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import math
import sys
import os
import shutil
import itertools

class Histogram:
	def __init__(self,title,info,typ,nbins,variableWidth,ledges,widths,sow,sow2):
		self.title = title
		self.info = info
		self.htype = typ
		self.nbins = nbins
		self.variableWidth = variableWidth
		self.ledges = ledges
		self.widths = widths
		self.sow = sow
		self.sow2 = sow2


def ratio(hista, histb):
	sow = []
	sow2 = []
	for sa,sb in itertools.izip(hista.sow,histb.sow):
		if sb==0:
			sow.append(0)
		else:
			sow.append(sa/sb)
	
	ret = Histogram(hista.title+"_ratio",hista.info,hista.htype,hista.nbins,hista.variableWidth,hista.ledges,hista.width,sow,sow2)

	return ret

def fetch(filename):
	if len(filename)<1:
		print "You did not provide a filename!"
		return 0
	f = open(filename,'r')	

	hist = False
	meta = False
	bins = False
	width = False
	ledge = False

	ret = []
	
	for line in f:
		if line.find("<histogram>")>-1:
			ledges = []
			widths = []
			sow = []
			sow2 = []
			title = ""
			info = ""
			nbins = 0
			variableWidth = False
			htype = ""
			hist = True
		elif line.find("</histogram>")>-1:
			ret.append(Histogram(title,info,htype,nbins,variableWidth,ledges,widths,sow,sow2))
			hist = False
		elif line.find("<meta>")>-1:
			meta = True
		elif line.find("</meta>")>-1:
			meta = False
		elif line.find("<bins>")>-1:
			bins = True
		elif line.find("</bins>")>-1:
			bins = False
		elif hist and meta:
			if line.find("<title=")>-1:
				title = line[line.find("\"")+1:line.rfind("\"")]
			elif line.find("<nbins=")>-1:
				nbins = int(line[line.find("\"")+1:line.rfind("\"")])
			elif line.find("<type=")>-1:
				htype = line[line.find("\"")+1:line.rfind("\"")]
			elif line.find("<info=")>-1:
				info = line[line.find("\"")+1:line.rfind("\"")]
			elif line.find("<variableWidth=")>-1:
				tmp = line[line.find("\"")+1:line.rfind("\"")]
				if tmp == "true":
					variableWidth = True
		elif hist and bins:
			elif line.find("<ledge=")>-1:
				ledges.append(float(line[line.find("\"")+1:line.rfind("\"")]))
			elif line.find("<width=")>-1:
				width.append(float(line[line.find("\"")+1:line.rfind("\"")]))
			elif line.find("<sum_of_weights=")>-1:
				sow.append(float(line[line.find("\"")+1:line.rfind("\"")]))
			elif line.find("<sum_of_weights_squared=")>-1:
				sow2.append(float(line[line.find("\"")+1:line.rfind("\"")]))
	return ret

if len(sys.argv)<2:
	print "Please provide arguments!"


elif sys.argv[1].find("-r")<0:
	name = sys.argv[1]
	histograms = fetch(name+'.xml' if name.find(".xml")<0 else name)

	fig, axs = plt.subplots(sharex=True)
	ax = axs

	for h in histograms:
		if True:
			centers = map(lambda x, y: x+ 0.5*y, h.ledges, h.widths)
			yerr = map(lambda x: math.sqrt(x), h.sow2)
			if h.info.find("log") > -1:
				ax.set_yscale("log")	
			ax.errorbar(centers, h.sow, yerr=yerr, fmt='o')
			ax.set_title("GG")
	
	plt.show()

elif sys.argv[1].find("-r")>-1:
	if(len(sys.argv)<3):
		print "Please provide additional arguments. Usage: drawhist -r <MCHIST1> <MCHIST2>... -d <DATAHIST>"
		sys.exit()
	datahistname = []
	mchistname = []
	collectdata = False
	collectmc = False
	for arg in sys.argv:
		print arg

		if arg == "-r":
			collectdata = False
			collectmc = True
		if arg == "-d":
			collectdata = True
			collectmc = False
		if collectmc and arg != "-r":
			mchistname.append(arg)
		if collectdata and arg != "-d":
			datahistname.append(arg)

	if len(datahistname) == 0:
		print "Only MCHIST provided"
		if os.path.exists('pyplots'):
			shutil.rmtree('pyplots')
		os.mkdir('pyplots')
		
		mchist = []

		for name in mchistname:
			mchist.append(fetch(name+'.xml' if name.find(".xml")<0 else name))

		for i in range(0,len(mchist[0])):
			for mc in mchist:
				h = mc[i]
				fig = plt.figure()
				ax = fig.add_subplot(111)
				centers = map(lambda x, y: x+ 0.5*y, h.ledges, h.widths)
				yerr = map(lambda x: math.sqrt(x), h.sow2)
				if h.info.find("log") > -1:
					ax.set_yscale("log")
				ax.errorbar(centers, h.sow, yerr=yerr, fmt='o')
				ax.set_title(h.title)
				fig.savefig('plots/'+h.title+".pdf")

	else:
		print "MCHIST and DATAHIST provided"
		mchist = fetch(sys.argv[2]+'.xml')
		datahist = fetch(sys.argv[3]+'.xml')
else:
	print "Something rotten happened..."