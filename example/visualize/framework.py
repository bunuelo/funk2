import pygtk
pygtk.require('2.0')
import gtk, gobject, cairo
import threading
import time
from physics import *
from visualization import *
from globalvars import *

gtk.gdk.threads_init()

class Screen(gtk.DrawingArea):

    world = False

    # sets 'world' to be input world
    def assure_initialized(self):
        if not self.world:
            self.world = myWorld

    # draws in response to an expose-event
    __gsignals__ = { "expose-event": "override" }
    def do_expose_event(self, event):
        self.set_size_request(WIDTH, HEIGHT)
        self.draw()

    # creates cairo context and draws world to it
    def draw(self):
        self.assure_initialized()
        cr = self.window.cairo_create()
        [width, height] = self.window.get_size()
        self.world.draw(cr, width, height)

    def redraw(self):
        self.queue_draw()

# configures the widget to show in a window and quit when it's closed
def runWindow(widget):
    window = gtk.Window()
    window.connect("delete-event", gtk.main_quit)
    widget.show()
    window.add(widget)
    window.present()
    gtk.main()

# runs window widget in separate thread
def threadRunWindow(widget):
    tupWidget = widget,
    threadWidget = threading.Thread(target=runWindow, args=tupWidget)
    threadWidget.start()

# runs simulation for given number of steps
def simulate(widget):
    delay = 0.05
    while not widget.get_window() == None:
        stepWorld(widget, delay)
    else:
        pass

# does an integration/movement step
def stepWorld(widget, delay):
    time.sleep(delay)
    widget.world.step()
    widget.redraw()

# runs simulation in separate thread
def threadSimulate(widget):
    widget.assure_initialized()
    tupWidget = widget,
    threadWorld = threading.Thread(target=simulate, args=tupWidget)
    threadWorld.start()


# example inputs for testing and debugging

#myRadius = 0.02
#myObject1 = body(1, myRadius, vector(0.1,0.2), vector(0,0), vector(0,0))
#myObject2 = body(1, myRadius, vector(0.4,0.2), vector(0,0), vector(0,0))
#myObject3 = body(1, myRadius, vector(0.3,0.7), vector(0,0), vector(0,0))
#myObjects = [myObject1, myObject2, myObject3]
#mySpring1 = spring(1, 0.3, myObject1, myObject2)
#mySpring2 = spring(1, 0.3, myObject1, myObject3)
#mySpring3 = spring(1, 0.3, myObject2, myObject3)
#mySprings = [mySpring1, mySpring2, mySpring3]
#myWorld = world()
#myWorld.objects = myObjects
#myWorld.springs = mySprings

myWorld = world()

#myKnow = KnowledgeBase('know1', vector(0.1,0.1))
#myRes = ResourceBase('res1', vector(0.5,0.5))
#myCon = Connector('con1', myKnow, myRes)
#myWorld.addBody(myKnow)
#myWorld.addBody(myRes)
#myWorld.addSpring(myCon)

def main():
    myScreen = Screen()
    threadRunWindow(myScreen)
    threadSimulate(myScreen)

#main()
