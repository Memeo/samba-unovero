'''
Created on Aug 19, 2015

@author: gsilverman
'''
import pprint
import requests
import collections
import json

if False:
    try:
        import http.client as http_client
    except ImportError:
        # Python 2
        import httplib as http_client
    http_client.HTTPConnection.debuglevel = 1
    
    import logging
    logging.basicConfig() 
    logging.getLogger().setLevel(logging.DEBUG)
    requests_log = logging.getLogger("requests.packages.urllib3")
    requests_log.setLevel(logging.DEBUG)
    requests_log.propagate = True


payload = collections.OrderedDict()
payload['email'] = 'greg.silverman@memeo-inc.com'
payload['password'] = 'Gbs10301!'
payload['web_session'] = 'false'



r = requests.post('https://c1.memeo.com/thor/auth/magni',params=payload)
j = json.JSONDecoder().decode(r.text)

print j['magni_token']
print j['links']['home']


