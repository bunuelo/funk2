from physics import *
from vector import *
from globalvars import *

class KnowledgeBase(body):
    
    def __init__(self, name, position):
        self.name = name
        self.position = position
        self.mass = knowMass
        self.radius = knowRadius
        self.velocity = vector(0,0)
        self.acceleration = vector(0,0)

class ResourceBase(body):

    def __init__(self, name, position):
        self.name = name
        self.position = position
        self.mass = resMass
        self.radius = resRadius
        self.velocity = vector(0,0)
        self.acceleration = vector(0,0)

class Connector(spring):
    
    def __init__(self, name, object1, object2):
        self.name = name
        self.object1 = object1
        self.object2 = object2
        self.width = conWidth
        self.strength = conStrength
        self.eqLength = conEqLength
