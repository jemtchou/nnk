#!/usr/bin/env python

import sys
import rootpy.io
from rootpy.tree import Tree

fname=sys.argv[1]
newf=fname.replace('.root','.csv')
f = rootpy.io.open(fname)
tree = f.get('gm')
tree.csv(stream=open(newf, 'w'))
