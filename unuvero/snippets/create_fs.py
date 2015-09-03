'''
Created on Aug 19, 2015

@author: gsilverman
'''
import pprint
import requests
import collections
import json
import urllib
import os

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


    
    
def authenticate(p_email,p_password):
    
    params = collections.OrderedDict()
    
    params['email'] = p_email
    params['password'] = p_password
    params['web_session'] = 'false'
        
    headers = {'Content-Length': '0', 'User-Agent': 'python-requests/2.7.0 CPython/2.7.9 Linux/3.19.0-26-generic', 'Connection': 'keep-alive', 'Accept': '*/*', 'Accept-Encoding': 'gzip, deflate'}

    
    r = requests.post('https://magni-staging.memeo.com/thor/auth/magni',headers=headers,params=params,)

    body = json.JSONDecoder().decode(r.text)
    
    headers['Memeo-Magni-Auth-Token'] = body['magni_token']
    
    return headers
    
def searchMagni(p_headers):
    params = collections.OrderedDict()
    params['include_docs']='false'
    params['limit']='100'
    params['reverse']='false'
    params['sort']='name'   
    #params['is_folder']='true' 
    
    r = requests.get('https://magni-staging.memeo.com/thor/magni/search',headers=p_headers,params=params,)
    
    body = json.JSONDecoder().decode(r.text)
    #pprint.pprint(body)
    body['details'] = {}
    for i in body['rows']:
        r = requests.get(i,headers=headers)  
        dirbody = json.JSONDecoder().decode(r.text)
        path = dirbody['path'].split('/')
        if not path[0]:
            path = path[1:]
        path.append(dirbody['name'])
        if not len(path) in body['details']:
            body['details'][len(path)] =[dirbody]
        else:
            body['details'][len(path)].append(dirbody)
  
     
    if r.status_code != 200:
        raise Exception(r.status_code)   
    else:
        return (r.headers,body)
    


if __name__ == '__main__':
    headers = authenticate('greg.silverman@mailinator.com', 'passw0rd1')
    headers,body = searchMagni(headers)
    #pprint.pprint(body)
    details = body['details']
    pprint.pprint(details)
    for i in xrange(len(details)):
        folders = details[i+1]
        for folder in folders:
            i+1,pprint.pprint(folder)
