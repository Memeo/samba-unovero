import sys
import os
import os.path
import collections

dirmap = collections.OrderedDict()

for root, dirs, files in os.walk('.'):
	for f in files:
		if f.startswith('wscript'):
			
			if not root in dirmap:
				dirmap[root] = []
			dirmap[root].append(f)
for d in dirmap:
	olddir = os.getcwd()
	os.chdir(d)
	for f in dirmap[d]:
		if f.startswith('wscript') and not f.endswith('.py') and not f+'.py' in files:
			os.symlink(f,f+'.py')
	os.chdir(olddir)
