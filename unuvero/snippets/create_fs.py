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
        
    headers = {'Content-Length': '0', 'User-Agent': 'python-requests/2.7.0 CPython/2.7.9 Linux/3.19.0-26-generic', 'Connection': 'keep-alive', 'Accept': 'application/vnd.memeo.bifrost.v1.0', 'Accept-Encoding': 'gzip, deflate'}

    r = requests.post('https://magni-staging.memeo.com/thor/auth/magni',headers=headers,params=params,)

    body = json.JSONDecoder().decode(r.text)
    
    magni_token = body['magni_token'].split(';')[0]
    
    return headers,magni_token

def download(p_headers,p_download_link,p_magni_token):
    
    p_headers['Memeo-Magni-Auth-Token'] = magni_token
    
    del p_headers['status']
    del p_headers['content-length']
    p_headers['Accept'] = 'application/vnd.memeo.bifrost.v1.0'
    p_headers['Accept-Encoding'] = 'gzip, deflate'

    pprint.pprint(p_download_link)
    r = requests.get(p_download_link,headers=p_headers,)
    print r.status_code
    print r.headers
    body = json.JSONDecoder().decode(r.text)
    pprint.pprint(body)
    
    p_headers['Memeo-Magni-Auth-Token'] = magni_token
    r = requests.get(body['download'],headers=p_headers,)
    print r.status_code
    print r.headers
    print r.text

    
    
    
def searchMagni(p_headers,p_magni_token):
    
    headers['Memeo-Magni-Auth-Token'] = magni_token

    p_params = collections.OrderedDict()
    p_params['include_docs']='true'
    p_params['limit']='100'
    p_params['reverse']='false'
    p_params['sort']='name'   

    r = requests.get('https://magni-staging.memeo.com/thor/magni/admin/search',headers=p_headers,params=p_params,)
    body = json.JSONDecoder().decode(r.text)

    paths = []
    folders = {'/':{'metadata':{},'items':{}}}
    items = {}
    for i in body['rows']:

        r = requests.get(i['links']['file'],headers=headers)  
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
        folders[path]['items'][name] = items[i]


    
    
    for path in paths:
        if path in folders:
            pass
            #pprint.pprint((path,{'metdata':folders[path]['metadata'],'items':folders[path]['items']}))
        else:
            pass
            #pprint.pprint((path,items[path]))
    return r.headers,(folders,items)

def others(p_headers):
    urls = ['thor','thor/magni','thor/mangi/admin','thor/magni/user','thor/magni/admin']
    for url in urls:
        r = requests.get('https://magni-staging.memeo.com/'+url,headers=p_headers)
        pprint.pprint({'url':url,'status':r.status_code,'headers':r.headers,'body':json.JSONDecoder().decode(r.text, )})

def get_user(p_headers):
    r = requests.get('https://magni-staging.memeo.com/thor/magni/admin',headers=p_headers)
    body = json.JSONDecoder().decode(r.text, )
    return body['links']['user']

if __name__ == '__main__':
    headers,magni_token = authenticate('greg.silverman@mailinator.com', 'passw0rd1')

    headers,data = searchMagni(headers,magni_token)
    dl = data[1]['/a.txt']['links']['download_link']
    download(headers, dl,magni_token)

    

