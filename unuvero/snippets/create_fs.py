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
from docutils.parsers.rst.directives import path

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

    p_params = collections.OrderedDict()
    p_params['include_docs']='false'
    p_params['limit']='100'
    p_params['reverse']='false'
    p_params['sort']='rawpath'   


    r = requests.get('https://magni-staging.memeo.com/thor/magni/search',headers=p_headers,params=p_params,)
    body = json.JSONDecoder().decode(r.text)


    paths = []
    folders = {'/':{'metadata':{},'items':{}}}
    items = {}
    for i in body['rows']:
        r = requests.get(i,headers=headers)  
        itembody = json.JSONDecoder().decode(r.text)
        name = itembody['name']
        path = '/'.join([itembody['path'],name])
        if not path.startswith('/'):
            path = '/'+path
        paths.append(path)
        if itembody['is_folder']:
            folders[path] = {'metadata':itembody,'items':{}}
        items[path] = itembody

    
    for i in items:
        path = '/'+items[i]['path']
        name = items[i]['name']
        if path:
            folders[path]['items'][name] = items[i]

    
    
    for path in paths:
        if path in folders:
            pprint.pprint((path,{'metdata':folders[path]['metadata'],'items':folders[path]['items']}))
        else:
            pprint.pprint((path,items[path]))
    return r.headers,(folders,items)
    
    
    


if __name__ == '__main__':
    headers = authenticate('greg.silverman@mailinator.com', 'passw0rd1')
    headers,body = searchMagni(headers)

