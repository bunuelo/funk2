import SimpleXMLRPCServer
import random
from vector import *
from physics import *
from visualization import *
from framework import *

class Universe:

    def __init__(self):
        self.obj = {}
        self.con = {}

    def giveObj(self):
        return self.obj

    def giveCon(self):
        return self.con

class UniverseXML(Universe):

    def run(self):
        main()
        return True

    def clear(self):
        self.obj = {}
        self.con = {}

    def genKey(self):
        key = random.randint(0,2**31)
        if not self.obj.has_key(key):
            return key
        else:
            self.genKey()

    def addObj(self, obj, key):
        myWorld.addBody(obj)
        self.obj[key] = obj
        return True

    def addCon(self, con, key):
        myWorld.addSpring(con)
        self.con[key] = con     
        return True

    def makeKnow(self, name):
        myPosition = vector(random.random(),random.random())
        myKnow = KnowledgeBase(name, myPosition)
        myKey = self.genKey()
        self.addObj(myKnow, myKey)
        return myKey
        
    def makeRes(self, name):
        myPosition = vector(random.random(),random.random())
        myRes = ResourceBase(name, myPosition)
        myKey = self.genKey()
        self.addObj(myRes, myKey)
        return myKey

    def makeCon(self, key1, key2):
        myName = 'test'
        myObj1 = self.obj[key1]
        myObj2 = self.obj[key2]
        myCon = Connector(myName, myObj1, myObj2)
        myKey = self.genKey()
        self.addCon(myCon, myKey)
        return myKey

    def addTwoKnow(self, name1, name2):
        key1 = self.makeKnow(name1)
        key2 = self.makeKnow(name2)
        self.makeCon(key1, key2)
        return True


server = SimpleXMLRPCServer.SimpleXMLRPCServer(('', 8010))
server.register_instance(UniverseXML())
server.serve_forever()
