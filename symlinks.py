import sys
import os
import os.path

cmd_format_string = 'ln -s %s %s.py'

for root, dirs, files in os.walk('.'):

    for f in files:

        if f.startswith('wscript') and not f.endswith('.py') and f+'.py' not in files:
            
            src = os.path.abspath(root+'/'+f)
            try:
                pass
                cmd = cmd_format_string % (src,src)
                #print cmd
                os.system(cmd)
            except OSError as e:
                if e.errno != 17:
                    raise e

