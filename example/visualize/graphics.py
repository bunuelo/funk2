import cairo
from math import pi

# draws given objects and springs on given context
def drawWorld(cr, objects, springs, width, height):
    cr.scale(width, height)
    cr.set_source_rgb(0.5, 0.5, 0.5)
    cr.rectangle(0, 0, width, height)
    cr.fill()
    drawX(cr)

    for spr in springs:
        drawLine(cr, spr.object1.position, spr.object2.position, spr.width)

    for obj in objects:
        drawCircle(cr, obj.position.x, obj.position.y, obj.radius)
        drawName(cr, obj.name, obj.position.x, obj.position.y)

def drawX(cr):
    cr.set_source_rgb(0.3, 0.3, 0.3)
    cr.set_line_width(0.001)
    cr.move_to(0.5, 0.49)
    cr.line_to(0.5, 0.51)
    cr.stroke()
    cr.move_to(0.49, 0.5)
    cr.line_to(0.51, 0.5)
    cr.stroke()

# saves drawing as a .png
def writeToPNG(filename, drawing):
    drawing.write_to_png(filename + '.png')

# draws a circle of given radius centered at (x,y)
def drawCircle(cr, x, y, radius):
    cr.set_source_rgb(0.0, 0.0, 0.0)
    cr.arc(x, y, radius, 0, 2 * pi)
    cr.fill()

# draws a line from point1 to point2
def drawLine(cr, point1, point2, width):
    cr.set_source_rgb(0.0, 0.0, 0.0)
    cr.set_line_width(width)
    cr.move_to(point1.x, point1.y)
    cr.line_to(point2.x, point2.y)
    cr.stroke()

# draws an object's name on it
def drawName(cr, name, x, y):
    cr.set_source_rgb(0.9, 0.9, 0.9)
    cr.select_font_face("Verdana", cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)
    cr.set_font_size(0.02)
    x_bearing, y_bearing, x_span, y_span = cr.text_extents(name)[:4]
    cr.move_to(x - x_span / 2 - x_bearing, y - y_span / 2 - y_bearing)
#    cr.move_to(x,y)
    cr.show_text(name)

