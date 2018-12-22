#!/usr/bin/env python

import requests

eloglist = []
elog = "https://logbooks.jlab.org"
hclog = "/book/hclog"
#elog = "https://logbooks.jlab.org/entry/3640529"
r = requests.get(elog+hclog)
for line in r.text :
    data = line.split('>')
    for i in range(len(data)) :
        if 'entry' in data :
            eloglist = data[i]
#print(r.text)
print(str(data))
print(str(eloglist))
