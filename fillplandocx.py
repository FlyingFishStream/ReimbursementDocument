import urllib.request
import urllib.parse
import re
import configparser
from datetime import datetime
import win32com
from win32com import  client
import os
import time
import shutil

'''docxFlag = {'Worker':'',
            'Date':'',
            'Thing':'',
            'Place':'',
            'Go':'',
            'Back':'',
            'PlanDate':'',
            'PlanPlace':'',
            'PlanThing':'',
            }'''
headers = {
    # 'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    # 'Accept-Encoding': 'gzip, deflate',
    # 'Accept-Language': 'zh-CN,en-US;q=0.7,en;q=0.3',
    'Host': 'www.variflight.com',
    # 'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:56.0) Gecko/20100101 Firefox/56.0',
    # 'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    # 'Accept-Language': 'zh-CN,en-US;q=0.7,en;q=0.3',
    # 'Accept-Encoding': 'gzip, deflate',
    # 'Referer': 'http://www.variflight.com/flight/CKG-HAK.html?AE71649A58c77&fdate=20180903',
    'Cookie': 'Hm_lvt_d1f759cd744b691c20c25f874cadc061=1535763702,1535769731,1535772001,1535808172; 37cs_user=37cs71365572074; 37cs_show=231; orderRole=1; citiesHistory=%5B%7B%22depCode%22%3A%22PEK%22%2C%22arrCode%22%3A%22SHA%22%2C%22depCity%22%3A%22%5Cu5317%5Cu4eac%5Cu9996%5Cu90fd%22%2C%22arrCity%22%3A%22%5Cu4e0a%5Cu6d77%5Cu8679%5Cu6865%22%7D%2C%7B%22depCode%22%3A%22CKG%22%2C%22arrCode%22%3A%22HAK%22%2C%22depCity%22%3A%22%5Cu91cd%5Cu5e86%5Cu6c5f%5Cu5317%22%2C%22arrCity%22%3A%22%5Cu6d77%5Cu53e3%5Cu7f8e%5Cu5170%22%7D%2C%7B%22depCode%22%3A%22CKG%22%2C%22arrCode%22%3A%22BJS%22%2C%22depCity%22%3A%22%5Cu91cd%5Cu5e86%5Cu6c5f%5Cu5317%22%2C%22arrCity%22%3A%22%5Cu5317%5Cu4eac%22%7D%5D; salt=5b8a938ee417f; 37cs_pidx=1; PHPSESSID=fboq92hiafi3iirrc6evbr0td5; Hm_lpvt_d1f759cd744b691c20c25f874cadc061=1535808401',
    'Connection': 'keep-alive',
    # 'Upgrade-Insecure-Requests': '1',
    # 'Cache-Control': 'max-age=0',
}

def iniToDocx(ini, docxFlag, strID):
    docxFlag['Worker'] = ini['Worker'].replace('"', '');
    docxFlag['Worker'] = docxFlag['Worker'].replace(' ', '\n')
    if ini['DateGo'] ==ini['DateBack']:
        docxFlag['Date'] = ini['DateGo']
    else:
        docxFlag['Date'] = ini['DateGo'] + '-' + ini['DateBack']
    strGo = ini['DateGo']
    strBack = ini['DateBack']
    docxFlag['Thing'] = ini['Thing']
    docxFlag['Place'] = ini['PlaceDec']
    print("Go:",strGo,ini['PlaceSrc'], ini['PlaceDec'], ini['PlaceSrc_3'], ini['PlaceDec_3'], ini['DateGo'], strID)
    docxFlag['Go'] = strGo + ',' + ini['PlaceSrc'] + '-' + ini['PlaceDec'] + ','
    strFightNum = GetFightNum(ini['PlaceSrc_3'], ini['PlaceDec_3'], ini['DateGo'], strID),
    docxFlag['Go'] = docxFlag['Go'] + strFightNum[0]
    # print(strFightNum)
    # if strFightNum != '':
    #     strNote = docxFlag['Go']
    #     docxFlag['Go'] = strNote + strFightNum
    docxFlag['Back'] = strBack + ',' + ini['PlaceDec'] + '-' + ini['PlaceSrc'] + ','
    strFightNum = GetFightNum(ini['PlaceDec_3'], ini['PlaceSrc_3'], ini['DateBack'], strID)
    docxFlag['Back'] = docxFlag['Back'] + strFightNum
    # print(strFightNum)
    # if strFightNum != '':
    #     strNote = docxFlag['Back']
    #     docxFlag['Back'] = strNote + strFightNum
    docxFlag['PlanDate'] = docxFlag['Date']
    docxFlag['PlanPlace'] = docxFlag['Place']
    # docxFlag['PlanThing'] = docxFlag['Thing'].find()
    for key in strKind:
        if docxFlag['Thing'].find(key) > 0:
            docxFlag['PlanThing'] = strKind[key]
    # print("docxFlag:", docxFlag)
    pass

def GetIni(ini):
    cf = configparser.ConfigParser()
    cf.read('Option.ini', encoding='gb18030')
    for key in ini:
        ini[key] = cf.get("FillPlanDocx", key)

def searchFightNum(str2, strHtml):
    print("searchFightNum:", str2)
    str2 = '">' + str2
    # print("reg is :", str2)
    nstrBegin = 0
    nstrEnd = 0
    while True:
        nstrBegin = strHtml.find(str2, nstrBegin, len(strHtml))
        if nstrBegin < 0:
            return ''

        nstrEnd = strHtml.find('</a>', nstrBegin + 1, nstrBegin + 15)
        if nstrEnd < 0:
            return ''
        nstrBegin = nstrBegin + 2
        print("return FightNum:", strHtml[nstrBegin:nstrEnd])
        return strHtml[nstrBegin:nstrEnd]


def GetFightNum(strSrc_3, strDec_3, strDate, strID):
    print("GetFightNum:", strSrc_3, strDec_3, strDate, strID)
    strDate = datetime.strptime(strDate, "%Y.%m.%d").strftime('%Y%m%d')
    url = 'http://www.variflight.com/flight/'
    url = url + strSrc_3 + '-' + strDec_3 + '.html?' + strID + '&fdate=' + strDate
    print('openurl:', url)

    values = {'numDatepicker':strDate,
              # 'byCity/dep_city': strSrc_3,
              'dep_city': strSrc_3,
              # 'changeCity.arr_city': strDec_3}
              'arr_city': strDec_3}
    print("values:", values)
    data = urllib.parse.urlencode(values).encode(encoding='UTF8')
    req = urllib.request.Request(url, data, headers)
    request = urllib.request.urlopen(req)
    html = request.read()
    file = open("html.txt", "wb")
    file.write(html)
    file.close()
    strHtml = html.decode('UTF-8')
    # findFightNum = re.search(r'">()')
    strCompanys = ['HU', 'PN', 'GS', 'JD']
    strFightNum = ''
    for i in range(len(strCompanys)):
        strFightNum = searchFightNum(strCompanys[i], strHtml)
        if strFightNum != '':
            return strFightNum
    return strFightNum

def writeDocx(ini, docxFlag):
    if os.path.exists(ini['docxDes']):
        os.remove(ini['docxDes'])
        time.sleep(1)
    shutil.copyfile(ini['docxSrc'], ini['docxDes'])
	
    if not os.path.exists(ini['docxDes']):
        print(ini['docxDes'], 'not xists')
        exit(-1)
    # print('writeDocx:', ini, docxFlag)
    w = win32com.client.Dispatch('Word.Application')
    # w = win32com.client.DispatchEx('Word.Application')
    # 前台运行，警告，显示
    #w.DisplayAlerts = 1
    w.Visible = 1
    # doc = w.Documents.Open( FileName = ini['docxSrc'] )
    doc = w.Documents.Open(FileName=ini['docxDes'])
    Bookmarks = doc.Bookmarks
    for key in docxFlag:
        if Bookmarks.Exists(key) == True:
            Bookmarks.Item(key).Range.Text = docxFlag[key]
    doc.Save()
    #doc.SaveAs(ini['docxDes'])

ini = {
        'docxSrc': '',
        'docxDes': '',
        'Worker': '',
        # 'departure': '',
        'DateGo': '',
        'DateBack': '',
        'Thing': '',
        'PlaceSrc': '',
        'PlaceSrc_3': '',
        'PlaceDec': '',
        'PlaceDec_3': '',
       }
docxFlag = {
            'Worker':'',
            'Date':'',
            'Thing':'',
            'Place':'',
            'Go':'',
            'Back':'',
            'PlanDate':'',
            'PlanPlace':'',
            'PlanThing':'',
            }
strKind = {
           '会议': '参会',
           '培训': '培训',
           '签证': '签证',
           '面签': '面签',
           '监造': '监造',
           '学习': '学习',
           'AOG': 'AOG',
           '轮换': '轮换',
           }
def startToDocx():
    url = 'http://www.variflight.com/'
    print("openurl:", url)

    request = urllib.request.urlopen(url)
    print("read html")
    html = request.read()

    strHtml = html.decode('UTF-8')
    findID = re.search(r"var SITE_ID  = \'(.+)\';", strHtml)
    if not findID:
        print("Can not find ID, exit(0)")
        exit(0)

    # print("start find id")
    strHtml = findID.group()
    strIndex = "\'"
    nBegin = strHtml.find(strIndex)
    nEnd = strHtml.find(strIndex, nBegin+1)
    strID = strHtml[nBegin+1:nEnd]
    print("strID:", strID)
    GetIni(ini)
    # print("ini:", ini)
    iniToDocx(ini, docxFlag, strID)
    writeDocx(ini, docxFlag)
    print("====================End==========================")

if __name__ == '__main__':
    startToDocx()