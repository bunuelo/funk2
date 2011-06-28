import math
import graphics
import cairo
from vector import *
from globalvars import *

class world:

    def __init__(self):
        self.name = ""
        self.objects = []
        self.springs = []

    def addBody(self, body):
        self.objects.append(body)

    def addSpring(self, spring):
        self.springs.append(spring)

    # does one integration and movement step
    def step(self):
        for spr in self.springs:
            sprForce = spr.calcForce()
            spr.object1.acceleration = sprForce[1].div(spr.object1.mass)
            spr.object2.acceleration = sprForce[2].div(spr.object2.mass)
        for obj in self.objects:
            dragForce = obj.calcDrag()
            obj.acceleration = obj.acceleration.add(dragForce).div(obj.mass)
            obj.move()

    # draws world on given context
    def draw(self, cr, width, height):
        middle = vector(0.5,0.5)
        self.centerShift(middle)
        graphics.drawWorld(cr, self.objects, self.springs, width, height)

    # calculates center of mass of system
    def calcCenter(self):
        centerOfMass = vector(0,0)
        totalMass = 0
        for obj in self.objects:
            centerOfMass = centerOfMass.add(obj.position.mult(obj.mass))
            totalMass += obj.mass
        return centerOfMass.div(totalMass)

    # shifts all objects to place center of mass at given coordinates
    def centerShift(self, coords):
        if not len(self.objects) == 0:
            centerOfMass = self.calcCenter()
            shift = coords.sub(centerOfMass)
            for obj in self.objects:
                obj.position = obj.position.add(shift)
        else:
            pass

class body:

    def __init__(self, mass, radius, position=vector(0,0), velocity=vector(0,0), acceleration=vector(0,0)):
        self.mass = mass
        self.radius = radius
        self.position = position
        self.velocity = velocity
        self.acceleration = acceleration

    # moves body one step using Euler's method
    def move(self):
        self.velocity = self.velocity.add((self.acceleration).mult(tStep))
        self.position = self.position.add((self.velocity).mult(tStep))

    def calcDrag(self):
        dragForce = self.velocity.mult(dragC).mult(-1)
        return dragForce

class spring:
    
    def __init__(self, width, strength, eqLength, object1, object2):
        self.width = width
        self.stength = strength
        self.eqLength = eqLength
        self.object1 = object1
        self.object2 = object2

    # calculates force that spring exerts on objects it connects
    # returns dictionary with spring's objects as keywords and force on them as values
    def calcForce(self):
        displacement = self.object2.position.sub(self.object1.position)
        springDisplacement = displacement.unit().mult(displacement.magnitude() - self.eqLength)
        force = springDisplacement.mult(self.strength)
        if self.eqLength == displacement.magnitude():
            force1, force2 = vector(0,0), vector(0,0)
        else:
            force1, force2 = force, force.mult(-1)
        return {1: force1, 2: force2}
