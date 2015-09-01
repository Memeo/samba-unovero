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


def f():
    payload = collections.OrderedDict()
    payload['email'] = 'greg.silverman@mailinator.com'
    payload['password'] = 'passw0rd1'
    payload['web_session'] = 'false'
    
    
    
    r = requests.post('https://magni-staging.memeo.com/thor/auth/magni',params=payload)
    #pprint.pprint(dir(r))
    pprint.pprint(dir(r.request))
    print r.request.headers
    j = json.JSONDecoder().decode(r.text)
    
    print j['magni_token']
    print j['links']['home']


    
def g():
    params = collections.OrderedDict()
    params['email'] = 'greg.silverman@memeo-inc.com'
    params['password'] = 'Gbs10301!'
    params['web_session'] = 'false'
    
    headers = {'Content-Length': '0', 'User-Agent': 'python-requests/2.7.0 CPython/2.7.9 Linux/3.19.0-26-generic', 'Connection': 'keep-alive', 'Accept': '*/*', 'Accept-Encoding': 'gzip, deflate'}

    
    r = requests.post('https://c1.memeo.com/thor/auth/magni',headers=headers,params=params,)
    
    return r

def h():
    params = collections.OrderedDict()
    params['email'] = 'greg.silverman@mailinator.com'
    params['password'] = 'passw0rd1'
    params['web_session'] = 'false'
    
    headers = {'Content-Length': '0', 'User-Agent': 'python-requests/2.7.0 CPython/2.7.9 Linux/3.19.0-26-generic', 'Connection': 'keep-alive', 'Accept': '*/*', 'Accept-Encoding': 'gzip, deflate'}

    
    r = requests.post('https://magni-staging.memeo.com/thor/auth/magni',headers=headers,params=params,)       
    print json.JSONDecoder().decode(r.text)
    
    
if __name__ == '__main__':
    h()


