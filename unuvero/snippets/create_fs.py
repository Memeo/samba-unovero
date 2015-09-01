'''
Created on Aug 19, 2015

@author: gsilverman
'''
import pprint
import requests
import collections
import json
import urllib
#from ubuntu_sso.utils.txsecrets import Item

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



def dump_map(fs):
    pass

def add_to_map(fs,path,value):
    if not path:
        if not 'value' in fs:
            fs['value'] = []
        fs['value'].append(value)
        return
    else:
        fs = fs[path[0]]
        add_to_map(fs,path[1:],value)

def build_map(fs,path):
    if not path:
        return
    else:
        if not path[0] in fs:
            fs[path[0]] = {}
        build_map(fs[path[0]],path[1:])
    
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
    
    
def createFs(p_headers):
    
    params = collections.OrderedDict()
    params['include_docs']='false'
    params['limit']='100'
    params['reverse']='false'
    params['sort']='name'    
    
    r = requests.get('https://magni-staging.memeo.com/thor/magni/admin/search',headers=p_headers,params=params,)
    
    body = json.JSONDecoder().decode(r.text)
    
    if r.status_code != 200:
        raise Exception(r.status_code)
    
    fs = {}
    results = []
    
    for i in body['rows']:
        r = requests.get(i,headers=headers)
        b = json.JSONDecoder().decode(r.text)
        results.append(b)
        crumbs = b['crumbs']
        path = []
        for j,k in enumerate(crumbs):
            for l,m in enumerate(k):
                path.append(m)
        build_map(fs,path)


    for b in results:
        crumbs = b['crumbs']
        path = []
        for j,k in enumerate(crumbs):
            for l,m in enumerate(k):
                path.append(m)                
        add_to_map(fs, path, b)
        
    return fs


if __name__ == '__main__':
    headers = authenticate('greg.silverman@mailinator.com', 'passw0rd1')
    fs = createFs(headers)
    pprint.pprint(fs)
